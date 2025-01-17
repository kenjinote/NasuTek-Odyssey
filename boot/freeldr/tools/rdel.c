/*  $Id: rdel.c 29690 2007-10-19 23:21:45Z dreimer $
 * COPYRIGHT:             See COPYING in the top level directory
 * PROGRAMMER:            Rex Jolliff (rex@lvcablemodem.com)
 * PURPOSE:               Platform independant delete command
 */

#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
convertPath (char * pathToConvert)
{
  while (*pathToConvert != 0)
  {
    if (*pathToConvert == '\\')
    {
      *pathToConvert = '/';
    }
    pathToConvert++;
  }
}

void
getDirectory (const char *filename, char * directorySpec)
{
  int  lengthOfDirectory;

  if (strrchr (filename, '/') != 0)
  {
    lengthOfDirectory = strrchr (filename, '/') - filename;
    strncpy (directorySpec, filename, lengthOfDirectory);
    directorySpec [lengthOfDirectory] = '\0';
  }
  else
  {
    strcpy (directorySpec, ".");
  }
}

void
getFilename (const char *filename, char * fileSpec)
{
  if (strrchr (filename, '/') != 0)
  {
    strcpy (fileSpec, strrchr (filename, '/') + 1);
  }
  else
  {
    strcpy (fileSpec, filename);
  }
}

int
main (int argc, char* argv[])
{
  int  justPrint = 0;
  int  idx;
  int  returnCode;

  for (idx = 1; idx < argc; idx++)
  {
    convertPath (argv [idx]);

    if (justPrint)
    {
      printf ("delete %s\n", argv [idx]);
    }
    else
    {
      returnCode = remove (argv [idx]);
      if (returnCode != 0 && errno != ENOENT)
      {
      /* Continue even if there is errors */
#if 0
        printf ("Unlink of %s failed.  Unlink returned %d.\n",
                argv [idx],
                returnCode);
        return  returnCode;
#endif
      }
    }
  }

  return  0;
}


