/*
 *  Odyssey Task Manager
 *
 *  perfpage.c
 *
 *  Copyright (C) 1999 - 2001  Brian Palmer  <brianp@odyssey.org>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <precomp.h>

TGraphCtrl PerformancePageCpuUsageHistoryGraph;
TGraphCtrl PerformancePageMemUsageHistoryGraph;

HWND  hPerformancePage;                               /*  Performance Property Page */
HWND  hPerformancePageCpuUsageGraph;                  /*  CPU Usage Graph */
HWND  hPerformancePageMemUsageGraph;                  /*  MEM Usage Graph */
HWND  hPerformancePageCpuUsageHistoryGraph;           /*  CPU Usage History Graph */
HWND  hPerformancePageMemUsageHistoryGraph;           /*  Memory Usage History Graph */
HWND  hPerformancePageTotalsFrame;                    /*  Totals Frame */
HWND  hPerformancePageCommitChargeFrame;              /*  Commit Charge Frame */
HWND  hPerformancePageKernelMemoryFrame;              /*  Kernel Memory Frame */
HWND  hPerformancePagePhysicalMemoryFrame;            /*  Physical Memory Frame */
HWND  hPerformancePageCpuUsageFrame;
HWND  hPerformancePageMemUsageFrame;
HWND  hPerformancePageCpuUsageHistoryFrame;
HWND  hPerformancePageMemUsageHistoryFrame;
HWND  hPerformancePageCommitChargeTotalEdit;          /*  Commit Charge Total Edit Control */
HWND  hPerformancePageCommitChargeLimitEdit;          /*  Commit Charge Limit Edit Control */
HWND  hPerformancePageCommitChargePeakEdit;           /*  Commit Charge Peak Edit Control */
HWND  hPerformancePageKernelMemoryTotalEdit;          /*  Kernel Memory Total Edit Control */
HWND  hPerformancePageKernelMemoryPagedEdit;          /*  Kernel Memory Paged Edit Control */
HWND  hPerformancePageKernelMemoryNonPagedEdit;       /*  Kernel Memory NonPaged Edit Control */
HWND  hPerformancePagePhysicalMemoryTotalEdit;        /*  Physical Memory Total Edit Control */
HWND  hPerformancePagePhysicalMemoryAvailableEdit;    /*  Physical Memory Available Edit Control */
HWND  hPerformancePagePhysicalMemorySystemCacheEdit;  /*  Physical Memory System Cache Edit Control */
HWND  hPerformancePageTotalsHandleCountEdit;          /*  Total Handles Edit Control */
HWND  hPerformancePageTotalsProcessCountEdit;         /*  Total Processes Edit Control */
HWND  hPerformancePageTotalsThreadCountEdit;          /*  Total Threads Edit Control */

#ifdef RUN_PERF_PAGE
static HANDLE hPerformanceThread = NULL;
static DWORD  dwPerformanceThread;
#endif

static int     nPerformancePageWidth;
static int     nPerformancePageHeight;
static int     lastX, lastY;
DWORD WINAPI   PerformancePageRefreshThread(void *lpParameter);

void AdjustFrameSize(HWND hCntrl, HWND hDlg, int nXDifference, int nYDifference, int pos)
{
    RECT  rc;
    int   cx, cy, sx, sy;

    GetClientRect(hCntrl, &rc);
    MapWindowPoints(hCntrl, hDlg, (LPPOINT)(PRECT)(&rc), (sizeof(RECT)/sizeof(POINT)));
    if (pos) {
        cx = rc.left;
        cy = rc.top;
        sx = rc.right - rc.left;
        switch (pos) {
        case 1:
            break;
        case 2:
            cy += nYDifference / 2;
            break;
        case 3:
            sx += nXDifference;
            break;
        case 4:
            cy += nYDifference / 2;
            sx += nXDifference;
            break;
        }
        sy = rc.bottom - rc.top + nYDifference / 2;
        SetWindowPos(hCntrl, NULL, cx, cy, sx, sy, SWP_NOACTIVATE|SWP_NOOWNERZORDER|SWP_NOZORDER);
    } else {
        cx = rc.left + nXDifference;
        cy = rc.top + nYDifference;
        sx = sy = 0;
        SetWindowPos(hCntrl, NULL, cx, cy, 0, 0, SWP_NOACTIVATE|SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER);
    }
    InvalidateRect(hCntrl, NULL, TRUE);
}

static void AdjustControlPostion(HWND hCntrl, HWND hDlg, int nXDifference, int nYDifference)
{
    AdjustFrameSize(hCntrl, hDlg, nXDifference, nYDifference, 0);
}

static void AdjustCntrlPos(int ctrl_id, HWND hDlg, int nXDifference, int nYDifference)
{
    AdjustFrameSize(GetDlgItem(hDlg, ctrl_id), hDlg, nXDifference, nYDifference, 0);
}

INT_PTR CALLBACK
PerformancePageWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT  rc;
    int   nXDifference;
    int   nYDifference;
/*     HDC hdc; */
/*     PAINTSTRUCT ps; */

    switch (message) {
    case WM_DESTROY:
        GraphCtrl_Dispose(&PerformancePageCpuUsageHistoryGraph);
        GraphCtrl_Dispose(&PerformancePageMemUsageHistoryGraph);
#ifdef RUN_PERF_PAGE
        EndLocalThread(&hPerformanceThread, dwPerformanceThread);
#endif
        break;

    case WM_INITDIALOG:

        /*  Save the width and height */
        GetClientRect(hDlg, &rc);
        nPerformancePageWidth = rc.right;
        nPerformancePageHeight = rc.bottom;

        /*  Update window position */
        SetWindowPos(hDlg, NULL, 15, 30, 0, 0, SWP_NOACTIVATE|SWP_NOOWNERZORDER|SWP_NOSIZE|SWP_NOZORDER);

        /*
         *  Get handles to all the controls
         */
        hPerformancePageTotalsFrame = GetDlgItem(hDlg, IDC_TOTALS_FRAME);
        hPerformancePageCommitChargeFrame = GetDlgItem(hDlg, IDC_COMMIT_CHARGE_FRAME);
        hPerformancePageKernelMemoryFrame = GetDlgItem(hDlg, IDC_KERNEL_MEMORY_FRAME);
        hPerformancePagePhysicalMemoryFrame = GetDlgItem(hDlg, IDC_PHYSICAL_MEMORY_FRAME);

        hPerformancePageCpuUsageFrame = GetDlgItem(hDlg, IDC_CPU_USAGE_FRAME);
        hPerformancePageMemUsageFrame = GetDlgItem(hDlg, IDC_MEM_USAGE_FRAME);
        hPerformancePageCpuUsageHistoryFrame = GetDlgItem(hDlg, IDC_CPU_USAGE_HISTORY_FRAME);
        hPerformancePageMemUsageHistoryFrame = GetDlgItem(hDlg, IDC_MEMORY_USAGE_HISTORY_FRAME);

        hPerformancePageCommitChargeTotalEdit = GetDlgItem(hDlg, IDC_COMMIT_CHARGE_TOTAL);
        hPerformancePageCommitChargeLimitEdit = GetDlgItem(hDlg, IDC_COMMIT_CHARGE_LIMIT);
        hPerformancePageCommitChargePeakEdit = GetDlgItem(hDlg, IDC_COMMIT_CHARGE_PEAK);
        hPerformancePageKernelMemoryTotalEdit = GetDlgItem(hDlg, IDC_KERNEL_MEMORY_TOTAL);
        hPerformancePageKernelMemoryPagedEdit = GetDlgItem(hDlg, IDC_KERNEL_MEMORY_PAGED);
        hPerformancePageKernelMemoryNonPagedEdit = GetDlgItem(hDlg, IDC_KERNEL_MEMORY_NONPAGED);
        hPerformancePagePhysicalMemoryTotalEdit = GetDlgItem(hDlg, IDC_PHYSICAL_MEMORY_TOTAL);
        hPerformancePagePhysicalMemoryAvailableEdit = GetDlgItem(hDlg, IDC_PHYSICAL_MEMORY_AVAILABLE);
        hPerformancePagePhysicalMemorySystemCacheEdit = GetDlgItem(hDlg, IDC_PHYSICAL_MEMORY_SYSTEM_CACHE);
        hPerformancePageTotalsHandleCountEdit = GetDlgItem(hDlg, IDC_TOTALS_HANDLE_COUNT);
        hPerformancePageTotalsProcessCountEdit = GetDlgItem(hDlg, IDC_TOTALS_PROCESS_COUNT);
        hPerformancePageTotalsThreadCountEdit = GetDlgItem(hDlg, IDC_TOTALS_THREAD_COUNT);

        hPerformancePageCpuUsageGraph = GetDlgItem(hDlg, IDC_CPU_USAGE_GRAPH);
        hPerformancePageMemUsageGraph = GetDlgItem(hDlg, IDC_MEM_USAGE_GRAPH);
        hPerformancePageMemUsageHistoryGraph = GetDlgItem(hDlg, IDC_MEM_USAGE_HISTORY_GRAPH);
        hPerformancePageCpuUsageHistoryGraph = GetDlgItem(hDlg, IDC_CPU_USAGE_HISTORY_GRAPH);

        GetClientRect(hPerformancePageCpuUsageHistoryGraph, &rc);
        /*  create the control */
        /* PerformancePageCpuUsageHistoryGraph.Create(0, rc, hDlg, IDC_CPU_USAGE_HISTORY_GRAPH); */
        GraphCtrl_Create(&PerformancePageCpuUsageHistoryGraph, hPerformancePageCpuUsageHistoryGraph, hDlg, IDC_CPU_USAGE_HISTORY_GRAPH);
        /*  customize the control */
        GraphCtrl_SetRange(&PerformancePageCpuUsageHistoryGraph, 0.0, 100.0, 10);
/*         PerformancePageCpuUsageHistoryGraph.SetYUnits("Current") ; */
/*         PerformancePageCpuUsageHistoryGraph.SetXUnits("Samples (Windows Timer: 100 msec)") ; */
/*         PerformancePageCpuUsageHistoryGraph.SetBackgroundColor(RGB(0, 0, 64)) ; */
/*         PerformancePageCpuUsageHistoryGraph.SetGridColor(RGB(192, 192, 255)) ; */
/*         PerformancePageCpuUsageHistoryGraph.SetPlotColor(RGB(255, 255, 255)) ; */
        GraphCtrl_SetBackgroundColor(&PerformancePageCpuUsageHistoryGraph, RGB(0, 0, 0)) ;
        GraphCtrl_SetGridColor(&PerformancePageCpuUsageHistoryGraph, RGB(0, 128, 64));

        GraphCtrl_SetPlotColor(&PerformancePageCpuUsageHistoryGraph, 0, RGB(0, 255, 0)) ;
        GraphCtrl_SetPlotColor(&PerformancePageCpuUsageHistoryGraph, 1, RGB(255, 0, 0)) ;


        GetClientRect(hPerformancePageMemUsageHistoryGraph, &rc);
        GraphCtrl_Create(&PerformancePageMemUsageHistoryGraph, hPerformancePageMemUsageHistoryGraph, hDlg, IDC_MEM_USAGE_HISTORY_GRAPH);
        GraphCtrl_SetRange(&PerformancePageMemUsageHistoryGraph, 0.0, 100.0, 10) ;
        GraphCtrl_SetBackgroundColor(&PerformancePageMemUsageHistoryGraph, RGB(0, 0, 0)) ;
        GraphCtrl_SetGridColor(&PerformancePageMemUsageHistoryGraph, RGB(0, 128, 64)) ;
        GraphCtrl_SetPlotColor(&PerformancePageMemUsageHistoryGraph, 0, RGB(255, 255, 0)) ;
        /*  Start our refresh thread */
#ifdef RUN_PERF_PAGE
        hPerformanceThread = CreateThread(NULL, 0, PerformancePageRefreshThread, NULL, 0, &dwPerformanceThread);
#endif

        /*
         *  Subclass graph buttons
         */
        OldGraphWndProc = (WNDPROC)(LONG_PTR) SetWindowLongPtrW(hPerformancePageCpuUsageGraph, GWL_WNDPROC, (LONG_PTR)Graph_WndProc);
        SetWindowLongPtrW(hPerformancePageMemUsageGraph, GWL_WNDPROC, (LONG_PTR)Graph_WndProc);
        OldGraphCtrlWndProc = (WNDPROC)(LONG_PTR) SetWindowLongPtrW(hPerformancePageMemUsageHistoryGraph, GWL_WNDPROC, (LONG_PTR)GraphCtrl_WndProc);
        SetWindowLongPtrW(hPerformancePageCpuUsageHistoryGraph, GWL_WNDPROC, (LONG_PTR)GraphCtrl_WndProc);
        return TRUE;

    case WM_COMMAND:
        break;
#if 0
    case WM_NCPAINT:
        hdc = GetDC(hDlg);
        GetClientRect(hDlg, &rc);
        Draw3dRect(hdc, rc.left, rc.top, rc.right, rc.top + 2, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
        ReleaseDC(hDlg, hdc);
        break;

    case WM_PAINT:
        hdc = BeginPaint(hDlg, &ps);
        GetClientRect(hDlg, &rc);
        Draw3dRect(hdc, rc.left, rc.top, rc.right, rc.top + 2, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
        EndPaint(hDlg, &ps);
        break;
#endif
    case WM_SIZE:
        do {
        int  cx, cy;

        if (wParam == SIZE_MINIMIZED)
            return 0;

        cx = LOWORD(lParam);
        cy = HIWORD(lParam);
        nXDifference = cx - nPerformancePageWidth;
        nYDifference = cy - nPerformancePageHeight;
        nPerformancePageWidth = cx;
        nPerformancePageHeight = cy;
        } while (0);

        /*  Reposition the performance page's controls */
        AdjustFrameSize(hPerformancePageTotalsFrame, hDlg, 0, nYDifference, 0);
        AdjustFrameSize(hPerformancePageCommitChargeFrame, hDlg, 0, nYDifference, 0);
        AdjustFrameSize(hPerformancePageKernelMemoryFrame, hDlg, 0, nYDifference, 0);
        AdjustFrameSize(hPerformancePagePhysicalMemoryFrame, hDlg, 0, nYDifference, 0);
        AdjustCntrlPos(IDS_COMMIT_CHARGE_TOTAL, hDlg, 0, nYDifference);
        AdjustCntrlPos(IDS_COMMIT_CHARGE_LIMIT, hDlg, 0, nYDifference);
        AdjustCntrlPos(IDS_COMMIT_CHARGE_PEAK, hDlg, 0, nYDifference);
        AdjustCntrlPos(IDS_KERNEL_MEMORY_TOTAL, hDlg, 0, nYDifference);
        AdjustCntrlPos(IDS_KERNEL_MEMORY_PAGED, hDlg, 0, nYDifference);
        AdjustCntrlPos(IDS_KERNEL_MEMORY_NONPAGED, hDlg, 0, nYDifference);
        AdjustCntrlPos(IDS_PHYSICAL_MEMORY_TOTAL, hDlg, 0, nYDifference);
        AdjustCntrlPos(IDS_PHYSICAL_MEMORY_AVAILABLE, hDlg, 0, nYDifference);
        AdjustCntrlPos(IDS_PHYSICAL_MEMORY_SYSTEM_CACHE, hDlg, 0, nYDifference);
        AdjustCntrlPos(IDS_TOTALS_HANDLE_COUNT, hDlg, 0, nYDifference);
        AdjustCntrlPos(IDS_TOTALS_PROCESS_COUNT, hDlg, 0, nYDifference);
        AdjustCntrlPos(IDS_TOTALS_THREAD_COUNT, hDlg, 0, nYDifference);

        AdjustControlPostion(hPerformancePageCommitChargeTotalEdit, hDlg, 0, nYDifference);
        AdjustControlPostion(hPerformancePageCommitChargeLimitEdit, hDlg, 0, nYDifference);
        AdjustControlPostion(hPerformancePageCommitChargePeakEdit, hDlg, 0, nYDifference);
        AdjustControlPostion(hPerformancePageKernelMemoryTotalEdit, hDlg, 0, nYDifference);
        AdjustControlPostion(hPerformancePageKernelMemoryPagedEdit, hDlg, 0, nYDifference);
        AdjustControlPostion(hPerformancePageKernelMemoryNonPagedEdit, hDlg, 0, nYDifference);
        AdjustControlPostion(hPerformancePagePhysicalMemoryTotalEdit, hDlg, 0, nYDifference);
        AdjustControlPostion(hPerformancePagePhysicalMemoryAvailableEdit, hDlg, 0, nYDifference);
        AdjustControlPostion(hPerformancePagePhysicalMemorySystemCacheEdit, hDlg, 0, nYDifference);
        AdjustControlPostion(hPerformancePageTotalsHandleCountEdit, hDlg, 0, nYDifference);
        AdjustControlPostion(hPerformancePageTotalsProcessCountEdit, hDlg, 0, nYDifference);
        AdjustControlPostion(hPerformancePageTotalsThreadCountEdit, hDlg, 0, nYDifference);

        nXDifference += lastX;
        nYDifference += lastY;
        lastX = lastY = 0;
        if (nXDifference % 2) {
            if (nXDifference > 0) {
                nXDifference--;
                lastX++;
            } else {
                nXDifference++;
                lastX--;
            }
        }
        if (nYDifference % 2) {
            if (nYDifference > 0) {
                nYDifference--;
                lastY++;
            } else {
                nYDifference++;
                lastY--;
            }
        }
        AdjustFrameSize(hPerformancePageCpuUsageFrame, hDlg, nXDifference, nYDifference, 1);
        AdjustFrameSize(hPerformancePageMemUsageFrame, hDlg, nXDifference, nYDifference, 2);
        AdjustFrameSize(hPerformancePageCpuUsageHistoryFrame, hDlg, nXDifference, nYDifference, 3);
        AdjustFrameSize(hPerformancePageMemUsageHistoryFrame, hDlg, nXDifference, nYDifference, 4);
        AdjustFrameSize(hPerformancePageCpuUsageGraph, hDlg, nXDifference, nYDifference, 1);
        AdjustFrameSize(hPerformancePageMemUsageGraph, hDlg, nXDifference, nYDifference, 2);
        AdjustFrameSize(hPerformancePageCpuUsageHistoryGraph, hDlg, nXDifference, nYDifference, 3);
        AdjustFrameSize(hPerformancePageMemUsageHistoryGraph, hDlg, nXDifference, nYDifference, 4);
        break;
    }
    return 0;
}

void RefreshPerformancePage(void)
{
#ifdef RUN_PERF_PAGE
    /*  Signal the event so that our refresh thread */
    /*  will wake up and refresh the performance page */
    PostThreadMessage(dwPerformanceThread, WM_TIMER, 0, 0);
#endif
}

DWORD WINAPI PerformancePageRefreshThread(void *lpParameter)
{
    ULONG  CommitChargeTotal;
    ULONG  CommitChargeLimit;
    ULONG  CommitChargePeak;

    ULONG  CpuUsage;
    ULONG  CpuKernelUsage;

    ULONG  KernelMemoryTotal;
    ULONG  KernelMemoryPaged;
    ULONG  KernelMemoryNonPaged;

    ULONG  PhysicalMemoryTotal;
    ULONG  PhysicalMemoryAvailable;
    ULONG  PhysicalMemorySystemCache;

    ULONG  TotalHandles;
    ULONG  TotalThreads;
    ULONG  TotalProcesses;

    WCHAR  Text[260];
    WCHAR  szMemUsage[256];

    MSG    msg;

    LoadStringW(hInst, IDS_STATUS_MEMUSAGE, szMemUsage, 256);

    while (1)
    {
        int nBarsUsed1;
        int nBarsUsed2;

        /*  Wait for an the event or application close */
        if (GetMessage(&msg, NULL, 0, 0) <= 0)
            return 0;

        if (msg.message == WM_TIMER)
        {
            /*
             *  Update the commit charge info
             */
            CommitChargeTotal = PerfDataGetCommitChargeTotalK();
            CommitChargeLimit = PerfDataGetCommitChargeLimitK();
            CommitChargePeak = PerfDataGetCommitChargePeakK();
            _ultow(CommitChargeTotal, Text, 10);
            SetWindowTextW(hPerformancePageCommitChargeTotalEdit, Text);
            _ultow(CommitChargeLimit, Text, 10);
            SetWindowTextW(hPerformancePageCommitChargeLimitEdit, Text);
            _ultow(CommitChargePeak, Text, 10);
            SetWindowTextW(hPerformancePageCommitChargePeakEdit, Text);
            wsprintfW(Text, szMemUsage, CommitChargeTotal, CommitChargeLimit);
            SendMessageW(hStatusWnd, SB_SETTEXT, 2, (LPARAM)Text);

            /*
             *  Update the kernel memory info
             */
            KernelMemoryTotal = PerfDataGetKernelMemoryTotalK();
            KernelMemoryPaged = PerfDataGetKernelMemoryPagedK();
            KernelMemoryNonPaged = PerfDataGetKernelMemoryNonPagedK();
            _ultow(KernelMemoryTotal, Text, 10);
            SetWindowTextW(hPerformancePageKernelMemoryTotalEdit, Text);
            _ultow(KernelMemoryPaged, Text, 10);
            SetWindowTextW(hPerformancePageKernelMemoryPagedEdit, Text);
            _ultow(KernelMemoryNonPaged, Text, 10);
            SetWindowTextW(hPerformancePageKernelMemoryNonPagedEdit, Text);

            /*
             *  Update the physical memory info
             */
            PhysicalMemoryTotal = PerfDataGetPhysicalMemoryTotalK();
            PhysicalMemoryAvailable = PerfDataGetPhysicalMemoryAvailableK();
            PhysicalMemorySystemCache = PerfDataGetPhysicalMemorySystemCacheK();
            _ultow(PhysicalMemoryTotal, Text, 10);
            SetWindowTextW(hPerformancePagePhysicalMemoryTotalEdit, Text);
            _ultow(PhysicalMemoryAvailable, Text, 10);
            SetWindowTextW(hPerformancePagePhysicalMemoryAvailableEdit, Text);
            _ultow(PhysicalMemorySystemCache, Text, 10);
            SetWindowTextW(hPerformancePagePhysicalMemorySystemCacheEdit, Text);

            /*
             *  Update the totals info
             */
            TotalHandles = PerfDataGetSystemHandleCount();
            TotalThreads = PerfDataGetTotalThreadCount();
            TotalProcesses = PerfDataGetProcessCount();
            _ultow(TotalHandles, Text, 10);
            SetWindowTextW(hPerformancePageTotalsHandleCountEdit, Text);
            _ultow(TotalThreads, Text, 10);
            SetWindowTextW(hPerformancePageTotalsThreadCountEdit, Text);
            _ultow(TotalProcesses, Text, 10);
            SetWindowTextW(hPerformancePageTotalsProcessCountEdit, Text);

            /*
             *  Redraw the graphs
             */
            InvalidateRect(hPerformancePageCpuUsageGraph, NULL, FALSE);
            InvalidateRect(hPerformancePageMemUsageGraph, NULL, FALSE);

            /*
             *  Get the CPU usage
             */
            CpuUsage = PerfDataGetProcessorUsage();
            if (CpuUsage <= 0 )       CpuUsage = 0;
            if (CpuUsage > 100)       CpuUsage = 100;

            if (TaskManagerSettings.ShowKernelTimes)
            {
                CpuKernelUsage = PerfDataGetProcessorSystemUsage();
                if (CpuKernelUsage <= 0)   CpuKernelUsage = 0;
                if (CpuKernelUsage > 100) CpuKernelUsage = 100;
            }
            else
            {
                CpuKernelUsage = 0;
            }
            /*
             *  Get the memory usage
             */
            CommitChargeTotal = PerfDataGetCommitChargeTotalK();
            CommitChargeLimit = PerfDataGetCommitChargeLimitK();
            nBarsUsed1 = CommitChargeLimit ? ((CommitChargeTotal * 100) / CommitChargeLimit) : 0;

            PhysicalMemoryTotal = PerfDataGetPhysicalMemoryTotalK();
            PhysicalMemoryAvailable = PerfDataGetPhysicalMemoryAvailableK();
            nBarsUsed2 = PhysicalMemoryTotal ? ((PhysicalMemoryAvailable * 100) / PhysicalMemoryTotal) : 0;

            GraphCtrl_AppendPoint(&PerformancePageCpuUsageHistoryGraph, CpuUsage, CpuKernelUsage, 0.0, 0.0);
            GraphCtrl_AppendPoint(&PerformancePageMemUsageHistoryGraph, nBarsUsed1, nBarsUsed2, 0.0, 0.0);
            /* PerformancePageMemUsageHistoryGraph.SetRange(0.0, 100.0, 10) ; */
            InvalidateRect(hPerformancePageMemUsageHistoryGraph, NULL, FALSE);
            InvalidateRect(hPerformancePageCpuUsageHistoryGraph, NULL, FALSE);
        }
    }
    return 0;
}

void PerformancePage_OnViewShowKernelTimes(void)
{
    HMENU  hMenu;
    HMENU  hViewMenu;

    hMenu = GetMenu(hMainWnd);
    hViewMenu = GetSubMenu(hMenu, 2);

    /*  Check or uncheck the show 16-bit tasks menu item */
    if (GetMenuState(hViewMenu, ID_VIEW_SHOWKERNELTIMES, MF_BYCOMMAND) & MF_CHECKED)
    {
        CheckMenuItem(hViewMenu, ID_VIEW_SHOWKERNELTIMES, MF_BYCOMMAND|MF_UNCHECKED);
        TaskManagerSettings.ShowKernelTimes = FALSE;
    }
    else
    {
        CheckMenuItem(hViewMenu, ID_VIEW_SHOWKERNELTIMES, MF_BYCOMMAND|MF_CHECKED);
        TaskManagerSettings.ShowKernelTimes = TRUE;
    }

    RefreshPerformancePage();
}

void PerformancePage_OnViewCPUHistoryOneGraphAll(void)
{
    HMENU  hMenu;
    HMENU  hViewMenu;
    HMENU  hCPUHistoryMenu;

    hMenu = GetMenu(hMainWnd);
    hViewMenu = GetSubMenu(hMenu, 2);
    hCPUHistoryMenu = GetSubMenu(hViewMenu, 3);

    TaskManagerSettings.CPUHistory_OneGraphPerCPU = FALSE;
    CheckMenuRadioItem(hCPUHistoryMenu, ID_VIEW_CPUHISTORY_ONEGRAPHALL, ID_VIEW_CPUHISTORY_ONEGRAPHPERCPU, ID_VIEW_CPUHISTORY_ONEGRAPHALL, MF_BYCOMMAND);
}

void PerformancePage_OnViewCPUHistoryOneGraphPerCPU(void)
{
    HMENU  hMenu;
    HMENU  hViewMenu;
    HMENU  hCPUHistoryMenu;

    hMenu = GetMenu(hMainWnd);
    hViewMenu = GetSubMenu(hMenu, 2);
    hCPUHistoryMenu = GetSubMenu(hViewMenu, 3);

    TaskManagerSettings.CPUHistory_OneGraphPerCPU = TRUE;
    CheckMenuRadioItem(hCPUHistoryMenu, ID_VIEW_CPUHISTORY_ONEGRAPHALL, ID_VIEW_CPUHISTORY_ONEGRAPHPERCPU, ID_VIEW_CPUHISTORY_ONEGRAPHPERCPU, MF_BYCOMMAND);
}

