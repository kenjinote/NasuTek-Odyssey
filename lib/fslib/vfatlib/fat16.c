/*
 * COPYRIGHT:   See COPYING in the top level directory
 * PROJECT:     Odyssey VFAT filesystem library
 * FILE:        fat16.c
 * PURPOSE:     Fat16 support
 * PROGRAMMERS: Casper S. Hornstrup (chorns@users.sourceforge.net)
 *              Eric Kohl
 * REVISIONS:
 *   EK 05/04-2003 Created
 */
#include "vfatlib.h"

#define NDEBUG
#include <debug.h>

static ULONG
GetShiftCount(IN ULONG Value)
{
    ULONG i = 1;

    while (Value > 0)
    {
        i++;
        Value /= 2;
    }

    return i - 2;
}


static ULONG
CalcVolumeSerialNumber(VOID)
{
    LARGE_INTEGER SystemTime;
    TIME_FIELDS TimeFields;
    ULONG Serial;
    PUCHAR Buffer;

    NtQuerySystemTime (&SystemTime);
    RtlTimeToTimeFields (&SystemTime, &TimeFields);

    Buffer = (PUCHAR)&Serial;
    Buffer[0] = (UCHAR)(TimeFields.Year & 0xFF) + (UCHAR)(TimeFields.Hour & 0xFF);
    Buffer[1] = (UCHAR)(TimeFields.Year >> 8) + (UCHAR)(TimeFields.Minute & 0xFF);
    Buffer[2] = (UCHAR)(TimeFields.Month & 0xFF) + (UCHAR)(TimeFields.Second & 0xFF);
    Buffer[3] = (UCHAR)(TimeFields.Day & 0xFF) + (UCHAR)(TimeFields.Milliseconds & 0xFF);

    return Serial;
}


static NTSTATUS
Fat16WriteBootSector(IN HANDLE FileHandle,
                     IN PFAT16_BOOT_SECTOR BootSector,
                     IN OUT PFORMAT_CONTEXT Context)
{
    IO_STATUS_BLOCK IoStatusBlock;
    NTSTATUS Status;
    PFAT16_BOOT_SECTOR NewBootSector;
    LARGE_INTEGER FileOffset;

    /* Allocate buffer for new bootsector */
    NewBootSector = (PFAT16_BOOT_SECTOR)RtlAllocateHeap(RtlGetProcessHeap(),
                                            0,
                                            BootSector->BytesPerSector);
    if (NewBootSector == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

    /* Zero the new bootsector */
    memset(NewBootSector, 0, BootSector->BytesPerSector);

    /* Copy FAT16 BPB to new bootsector */
    memcpy(&NewBootSector->OEMName[0],
           &BootSector->OEMName[0],
           59); /* FAT16 BPB length (up to (not including) Res2) */

    /* Write the boot sector signature */
    NewBootSector->Signature1 = 0xAA550000;

    /* Write sector 0 */
    FileOffset.QuadPart = 0ULL;
    Status = NtWriteFile(FileHandle,
                         NULL,
                         NULL,
                         NULL,
                         &IoStatusBlock,
                         NewBootSector,
                         BootSector->BytesPerSector,
                         &FileOffset,
                         NULL);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("NtWriteFile() failed (Status %lx)\n", Status);
        RtlFreeHeap(RtlGetProcessHeap(), 0, NewBootSector);
        return Status;
    }

    UpdateProgress(Context, 1);

    /* Free the new boot sector */
    RtlFreeHeap(RtlGetProcessHeap(), 0, NewBootSector);

    return Status;
}


static NTSTATUS
Fat16WriteFAT(IN HANDLE FileHandle,
              IN ULONG SectorOffset,
              IN PFAT16_BOOT_SECTOR BootSector,
              IN OUT PFORMAT_CONTEXT Context)
{
    IO_STATUS_BLOCK IoStatusBlock;
    NTSTATUS Status;
    PUCHAR Buffer;
    LARGE_INTEGER FileOffset;
    ULONG i;
    ULONG Sectors;

    /* Allocate buffer */
    Buffer = (PUCHAR)RtlAllocateHeap(RtlGetProcessHeap(),
                                     0,
                                     32 * 1024);
    if (Buffer == NULL)
      return STATUS_INSUFFICIENT_RESOURCES;

    /* Zero the buffer */
    memset(Buffer, 0, 32 * 1024);

    /* FAT cluster 0 */
    Buffer[0] = 0xf8; /* Media type */
    Buffer[1] = 0xff;

    /* FAT cluster 1 */
    Buffer[2] = 0xff; /* Clean shutdown, no disk read/write errors, end-of-cluster (EOC) mark */
    Buffer[3] = 0xff;

    /* Write first sector of the FAT */
    FileOffset.QuadPart = (SectorOffset + BootSector->ReservedSectors) * BootSector->BytesPerSector;
    Status = NtWriteFile(FileHandle,
                         NULL,
                         NULL,
                         NULL,
                         &IoStatusBlock,
                         Buffer,
                         BootSector->BytesPerSector,
                         &FileOffset,
                         NULL);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("NtWriteFile() failed (Status %lx)\n", Status);
        RtlFreeHeap(RtlGetProcessHeap(), 0, Buffer);
        return Status;
    }

    UpdateProgress(Context, 1);

    /* Zero the begin of the buffer */
    memset(Buffer, 0, 4);

    /* Zero the rest of the FAT */
    Sectors = 32 * 1024 / BootSector->BytesPerSector;
    for (i = 1; i < (ULONG)BootSector->FATSectors; i += Sectors)
    {
        /* Zero some sectors of the FAT */
        FileOffset.QuadPart = (SectorOffset + BootSector->ReservedSectors + i) * BootSector->BytesPerSector;

        if (((ULONG)BootSector->FATSectors - i) <= Sectors)
        {
            Sectors = (ULONG)BootSector->FATSectors - i;
        }

        Status = NtWriteFile(FileHandle,
                             NULL,
                             NULL,
                             NULL,
                             &IoStatusBlock,
                             Buffer,
                             Sectors * BootSector->BytesPerSector,
                             &FileOffset,
                             NULL);
        if (!NT_SUCCESS(Status))
        {
            DPRINT("NtWriteFile() failed (Status %lx)\n", Status);
            RtlFreeHeap(RtlGetProcessHeap(), 0, Buffer);
            return Status;
        }

        UpdateProgress(Context, Sectors);
    }

    /* Free the buffer */
    RtlFreeHeap(RtlGetProcessHeap(), 0, Buffer);

    return Status;
}


static NTSTATUS
Fat16WriteRootDirectory(IN HANDLE FileHandle,
                        IN PFAT16_BOOT_SECTOR BootSector,
                        IN OUT PFORMAT_CONTEXT Context)
{
    IO_STATUS_BLOCK IoStatusBlock;
    NTSTATUS Status = STATUS_SUCCESS;
    PUCHAR Buffer;
    LARGE_INTEGER FileOffset;
    ULONG FirstRootDirSector;
    ULONG RootDirSectors;
    ULONG Sectors;
    ULONG i;

    DPRINT("BootSector->ReservedSectors = %hu\n", BootSector->ReservedSectors);
    DPRINT("BootSector->FATSectors = %hu\n", BootSector->FATSectors);
    DPRINT("BootSector->SectorsPerCluster = %u\n", BootSector->SectorsPerCluster);

    /* Write cluster */
    RootDirSectors = ((BootSector->RootEntries * 32) +
        (BootSector->BytesPerSector - 1)) / BootSector->BytesPerSector;
    FirstRootDirSector =
        BootSector->ReservedSectors + (BootSector->FATCount * BootSector->FATSectors);

    DPRINT("RootDirSectors = %lu\n", RootDirSectors);
    DPRINT("FirstRootDirSector = %lu\n", FirstRootDirSector);

    /* Allocate buffer for the cluster */
    Buffer = (PUCHAR)RtlAllocateHeap(RtlGetProcessHeap(),
                                     0,
                                     32 * 1024);
    if (Buffer == NULL)
        return STATUS_INSUFFICIENT_RESOURCES;

    /* Zero the buffer */
    memset(Buffer, 0, 32 * 1024);

    Sectors = 32 * 1024 / BootSector->BytesPerSector;
    for (i = 0; i < RootDirSectors; i += Sectors)
    {
        /* Zero some sectors of the root directory */
        FileOffset.QuadPart = (FirstRootDirSector + i) * BootSector->BytesPerSector;

        if ((RootDirSectors - i) <= Sectors)
        {
            Sectors = RootDirSectors - i;
        }

        Status = NtWriteFile(FileHandle,
                             NULL,
                             NULL,
                             NULL,
                             &IoStatusBlock,
                             Buffer,
                             Sectors * BootSector->BytesPerSector,
                             &FileOffset,
                             NULL);
        if (!NT_SUCCESS(Status))
        {
            DPRINT("NtWriteFile() failed (Status %lx)\n", Status);
            RtlFreeHeap(RtlGetProcessHeap(), 0, Buffer);
            return Status;
        }

        UpdateProgress(Context, Sectors);
    }

    /* Free the buffer */
    RtlFreeHeap(RtlGetProcessHeap(), 0, Buffer);

    return Status;
}


NTSTATUS
Fat16Format(IN HANDLE FileHandle,
            IN PPARTITION_INFORMATION PartitionInfo,
            IN PDISK_GEOMETRY DiskGeometry,
            IN PUNICODE_STRING Label,
            IN BOOLEAN QuickFormat,
            IN ULONG ClusterSize,
            IN OUT PFORMAT_CONTEXT Context)
{
    FAT16_BOOT_SECTOR BootSector;
    OEM_STRING VolumeLabel;
    ULONG SectorCount;
    ULONG RootDirSectors;
    ULONG TmpVal1;
    ULONG TmpVal2;
    ULONG TmpVal3;
    NTSTATUS Status;

    /* Calculate cluster size */
    if (ClusterSize == 0)
    {
        if (PartitionInfo->PartitionLength.QuadPart < 16LL * 1024LL * 1024LL)
        {
            /* Partition < 16MB ==> 1KB Cluster */
            ClusterSize = 1024;
        }
        else if (PartitionInfo->PartitionLength.QuadPart < 128LL * 1024LL * 1024LL)
        {
            /* Partition < 128MB ==> 2KB Cluster */
            ClusterSize = 2048;
        }
        else if (PartitionInfo->PartitionLength.QuadPart < 256LL * 1024LL * 1024LL)
        {
            /* Partition < 256MB ==> 4KB Cluster */
            ClusterSize = 4096;
        }
        else
        {
            /* Partition >= 256MB (< 512MB) ==> 8KB Cluster */
            ClusterSize = 8192;
        }
    }

    SectorCount = PartitionInfo->PartitionLength.QuadPart >>
        GetShiftCount(DiskGeometry->BytesPerSector); /* Use shifting to avoid 64-bit division */

    memset(&BootSector, 0, sizeof(FAT16_BOOT_SECTOR));
    memcpy(&BootSector.OEMName[0], "MSWIN4.1", 8);
    BootSector.BytesPerSector = DiskGeometry->BytesPerSector;
    BootSector.SectorsPerCluster = ClusterSize / BootSector.BytesPerSector;
    BootSector.ReservedSectors = 1;
    BootSector.FATCount = 2;
    BootSector.RootEntries = 512;
    BootSector.Sectors = (SectorCount < 0x10000) ? (unsigned short)SectorCount : 0;
    BootSector.Media = 0xf8;
    BootSector.FATSectors = 0;  /* Set later. See below. */
    BootSector.SectorsPerTrack = DiskGeometry->SectorsPerTrack;
    BootSector.Heads = DiskGeometry->TracksPerCylinder;
    BootSector.HiddenSectors = PartitionInfo->HiddenSectors;
    BootSector.SectorsHuge = (SectorCount >= 0x10000) ? (unsigned long)SectorCount : 0;
    BootSector.Drive = DiskGeometry->MediaType == FixedMedia ? 0x80 : 0x00;
    BootSector.ExtBootSignature = 0x29;
    BootSector.VolumeID = CalcVolumeSerialNumber();
    if ((Label == NULL) || (Label->Buffer == NULL))
    {
        memcpy(&BootSector.VolumeLabel[0], "NO NAME    ", 11);
    }
    else
    {
        RtlUnicodeStringToOemString(&VolumeLabel, Label, TRUE);
        memset(&BootSector.VolumeLabel[0], ' ', 11);
        memcpy(&BootSector.VolumeLabel[0], VolumeLabel.Buffer,
               VolumeLabel.Length < 11 ? VolumeLabel.Length : 11);
        RtlFreeOemString(&VolumeLabel);
    }

    memcpy(&BootSector.SysType[0], "FAT16   ", 8);

    DPRINT("BootSector.SectorsHuge = %lx\n", BootSector.SectorsHuge);

    RootDirSectors = ((BootSector.RootEntries * 32) +
        (BootSector.BytesPerSector - 1)) / BootSector.BytesPerSector;

    /* Calculate number of FAT sectors */
    /* (BootSector.BytesPerSector / 2) FAT entries (16bit) fit into one sector */
    TmpVal1 = SectorCount - (BootSector.ReservedSectors + RootDirSectors);
    TmpVal2 = ((BootSector.BytesPerSector / 2) * BootSector.SectorsPerCluster) + BootSector.FATCount;
    TmpVal3 = (TmpVal1 + (TmpVal2 - 1)) / TmpVal2;
    BootSector.FATSectors = (unsigned short)(TmpVal3 & 0xffff);
    DPRINT("BootSector.FATSectors = %hu\n", BootSector.FATSectors);

    /* Init context data */
    Context->TotalSectorCount =
        1 + (BootSector.FATSectors * 2) + RootDirSectors;

    Status = Fat16WriteBootSector(FileHandle,
                                  &BootSector,
                                  Context);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Fat16WriteBootSector() failed with status 0x%.08x\n", Status);
        return Status;
    }

    /* Write first FAT copy */
    Status = Fat16WriteFAT(FileHandle,
                           0,
                           &BootSector,
                           Context);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Fat16WriteFAT() failed with status 0x%.08x\n", Status);
        return Status;
    }

    /* Write second FAT copy */
    Status = Fat16WriteFAT(FileHandle,
                           (ULONG)BootSector.FATSectors,
                           &BootSector,
                           Context);
    if (!NT_SUCCESS(Status))
    {
       DPRINT("Fat16WriteFAT() failed with status 0x%.08x.\n", Status);
        return Status;
    }

    Status = Fat16WriteRootDirectory(FileHandle,
                                     &BootSector,
                                     Context);
    if (!NT_SUCCESS(Status))
    {
        DPRINT("Fat16WriteRootDirectory() failed with status 0x%.08x\n", Status);
    }

    if (!QuickFormat)
    {
        /* FIXME: Fill remaining sectors */
    }

    return Status;
}
