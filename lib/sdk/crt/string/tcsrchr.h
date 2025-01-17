/* $Id: tcsrchr.h 41916 2009-07-12 10:40:39Z ros-arm-bringup $
 */

#include <tchar.h>

_TCHAR * _tcsrchr(const _TCHAR * s, _XINT c)
{
 _TCHAR cc = c;
 const _TCHAR * sp = (_TCHAR *)0;

 while(*s)
 {
  if(*s == cc) sp = s;
  s ++;
 }

 if(cc == 0) sp = s;

 return (_TCHAR *)sp;
}

/* EOF */
