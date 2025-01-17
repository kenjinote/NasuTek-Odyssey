#ifndef __INCLUDE_USER32_CALLBACK_H
#define __INCLUDE_USER32_CALLBACK_H

#define USER32_CALLBACK_WINDOWPROC            (0)
#define USER32_CALLBACK_SENDASYNCPROC         (1)
#define USER32_CALLBACK_LOADSYSMENUTEMPLATE   (2)
#define USER32_CALLBACK_LOADDEFAULTCURSORS    (3)
#define USER32_CALLBACK_HOOKPROC              (4)
#define USER32_CALLBACK_EVENTPROC             (5)
#define USER32_CALLBACK_LOADMENU              (6)
#define USER32_CALLBACK_CLIENTTHREADSTARTUP   (7)
#define USER32_CALLBACK_MAXIMUM               (7)

typedef struct _WINDOWPROC_CALLBACK_ARGUMENTS
{
  WNDPROC Proc;
  BOOL IsAnsiProc;
  HWND Wnd;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  INT lParamBufferSize;
  LRESULT Result;
  /* char Buffer[]; */
} WINDOWPROC_CALLBACK_ARGUMENTS, *PWINDOWPROC_CALLBACK_ARGUMENTS;

typedef struct _SENDASYNCPROC_CALLBACK_ARGUMENTS
{
  SENDASYNCPROC Callback;
  HWND Wnd;
  UINT Msg;
  ULONG_PTR Context;
  LRESULT Result;
} SENDASYNCPROC_CALLBACK_ARGUMENTS, *PSENDASYNCPROC_CALLBACK_ARGUMENTS;

typedef struct _CALL_BACK_INFO
{
   SENDASYNCPROC CallBack;
   ULONG_PTR Context;
} CALL_BACK_INFO, * PCALL_BACK_INFO;


typedef struct _HOOKPROC_CALLBACK_ARGUMENTS
{
  INT HookId;
  INT Code;
  WPARAM wParam;
  LPARAM lParam;
  HOOKPROC Proc;
  BOOLEAN Ansi;
} HOOKPROC_CALLBACK_ARGUMENTS, *PHOOKPROC_CALLBACK_ARGUMENTS;

typedef struct _HOOKPROC_CBT_CREATEWND_EXTRA_ARGUMENTS
{
  CREATESTRUCTW Cs; /* lpszName and lpszClass replaced by offsets */
  HWND WndInsertAfter;
  /* WCHAR szName[] */
  /* WCHAR szClass[] */
} HOOKPROC_CBT_CREATEWND_EXTRA_ARGUMENTS, *PHOOKPROC_CBT_CREATEWND_EXTRA_ARGUMENTS;

typedef struct _EVENTPROC_CALLBACK_ARGUMENTS
{
  HWINEVENTHOOK hook;
  DWORD event;
  HWND hwnd; 
  LONG idObject;
  LONG idChild;
  DWORD dwEventThread;
  DWORD dwmsEventTime;
  WINEVENTPROC Proc;
} EVENTPROC_CALLBACK_ARGUMENTS, *PEVENTPROC_CALLBACK_ARGUMENTS;

typedef struct _LOADMENU_CALLBACK_ARGUMENTS
{
  HINSTANCE hModule;
  WCHAR MenuName[1];
} LOADMENU_CALLBACK_ARGUMENTS, *PLOADMENU_CALLBACK_ARGUMENTS;

NTSTATUS WINAPI
User32CallWindowProcFromKernel(PVOID Arguments, ULONG ArgumentLength);
NTSTATUS WINAPI
User32CallSendAsyncProcForKernel(PVOID Arguments, ULONG ArgumentLength);
NTSTATUS WINAPI
User32LoadSysMenuTemplateForKernel(PVOID Arguments, ULONG ArgumentLength);
NTSTATUS WINAPI
User32SetupDefaultCursors(PVOID Arguments, ULONG ArgumentLength);
NTSTATUS WINAPI
User32CallHookProcFromKernel(PVOID Arguments, ULONG ArgumentLength);
NTSTATUS WINAPI
User32CallEventProcFromKernel(PVOID Arguments, ULONG ArgumentLength);
NTSTATUS WINAPI
User32CallLoadMenuFromKernel(PVOID Arguments, ULONG ArgumentLength);
NTSTATUS WINAPI
User32CallClientThreadSetupFromKernel(PVOID Arguments, ULONG ArgumentLength);

#endif /* __INCLUDE_USER32_CALLBACK_H */
