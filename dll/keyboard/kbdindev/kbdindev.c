/*
 * Odyssey Devanagari - INSCRIPT Keyboard layout
 * Copyright (C) 2008 Odyssey
 * Author: Dmitry Chapyshev
 * License: LGPL, see: LGPL.txt
 *
 * Thanks to: http://www.barcodeman.com/altek/mule/scandoc.php
 * and http://win.tue.nl/~aeb/linux/kbd/scancodes-1.html
 */

#include <windows.h>
#include <internal/kbd.h>

#ifdef _M_IA64
#define ROSDATA static __declspec(allocate(".data"))
#else
#ifdef _MSC_VER
#pragma data_seg(".data")
#define ROSDATA static
#else
#define ROSDATA static __attribute__((section(".data")))
#endif
#endif

#define VK_EMPTY 0xff   /* The non-existent VK */
#define KSHIFT   0x001  /* Shift modifier */
#define KCTRL    0x002  /* Ctrl modifier */
#define KALT     0x004  /* Alt modifier */
#define KEXT     0x100  /* Extended key code */
#define KMULTI   0x200  /* Multi-key */
#define KSPEC    0x400  /* Special key */
#define KNUMP    0x800  /* Number-pad */
#define KNUMS    0xc00  /* Special + number pad */
#define KMEXT    0x300  /* Multi + ext */

#define SHFT_INVALID 0x0F

ROSDATA USHORT scancode_to_vk[] = {
  /* Numbers Row */
  /* - 00 - */
  /* 1 ...         2 ...         3 ...         4 ... */
  VK_EMPTY,     VK_ESCAPE,    '1',          '2',
  '3',          '4',          '5',          '6',
  '7',          '8',          '9',          '0',
  VK_OEM_MINUS, VK_OEM_PLUS,  VK_BACK,
  /* - 0f - */
  /* First Letters Row */
  VK_TAB,       'Q',          'W',          'E',
  'R',          'T',          'Y',          'U',
  'I',          'O',          'P',
  VK_OEM_4,     VK_OEM_6,     VK_RETURN,
  /* - 1d - */
  /* Second Letters Row */
  VK_LCONTROL,
  'A',          'S',          'D',          'F',
  'G',          'H',          'J',          'K',
  'L',          VK_OEM_1,     VK_OEM_7,     VK_OEM_3,
  VK_LSHIFT,    VK_OEM_5,
  /* - 2c - */
  /* Third letters row */
  'Z',          'X',          'C',          'V',
  'B',          'N',          'M',          VK_OEM_COMMA,
  VK_OEM_PERIOD,VK_OEM_2,     VK_RSHIFT | KEXT,
  /* - 37 - */
  /* Bottom Row */
  0x26a,  VK_LMENU,     VK_SPACE,     VK_CAPITAL,

  /* - 3b - */
  /* F-Keys */
  VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6,
  VK_F7, VK_F8, VK_F9, VK_F10,
  /* - 45 - */
  /* Locks */
  VK_NUMLOCK | KMEXT,
  VK_SCROLL | KMULTI,
  /* - 47 - */
  /* Number-Pad */
  VK_HOME | KNUMS,      VK_UP | KNUMS,         VK_PRIOR | KNUMS, VK_SUBTRACT,
  VK_LEFT | KNUMS,      VK_CLEAR | KNUMS,      VK_RIGHT | KNUMS, VK_ADD,
  VK_END | KNUMS,       VK_DOWN | KNUMS,       VK_NEXT | KNUMS,
  VK_INSERT | KNUMS,    VK_DELETE | KNUMS,
  /* - 54 - */
  /* Presumably PrtSc */
  VK_SNAPSHOT,
  /* - 55 - */
  /* Oddities, and the remaining standard F-Keys */
  VK_EMPTY,     VK_OEM_102,     VK_F11,       VK_F12,
  /* - 59 - */
  VK_CLEAR,     VK_OEM_WSCTRL,VK_OEM_FINISH,VK_OEM_JUMP,  VK_EREOF, /* EREOF */
  VK_OEM_BACKTAB,    VK_OEM_AUTO,  VK_EMPTY,    VK_ZOOM,            /* ZOOM */
  VK_HELP,
  /* - 64 - */
  /* Even more F-Keys (for example, NCR keyboards from the early 90's) */
  VK_F13, VK_F14, VK_F15, VK_F16, VK_F17, VK_F18, VK_F19, VK_F20,
  VK_F21, VK_F22, VK_F23,
  /* - 6f - */
  /* Not sure who uses these codes */
  VK_OEM_PA3, VK_EMPTY, VK_OEM_RESET,
  /* - 72 - */
  VK_EMPTY, 0xc1, VK_EMPTY, VK_EMPTY,
  /* - 76 - */
  /* One more f-key */
  VK_F24,
  /* - 77 - */
  VK_EMPTY, VK_EMPTY, VK_EMPTY, VK_EMPTY,
  VK_OEM_PA1, VK_TAB, 0xc2, 0, /* PA1 */
  0,
  /* - 80 - */
  0
};

ROSDATA VSC_VK extcode0_to_vk[] = {
  { 0x10, VK_MEDIA_PREV_TRACK | KEXT },
  { 0x19, VK_MEDIA_NEXT_TRACK | KEXT },
  { 0x1D, VK_RCONTROL | KEXT },
  { 0x20, VK_VOLUME_MUTE | KEXT },
  { 0x21, VK_LAUNCH_APP2 | KEXT },
  { 0x22, VK_MEDIA_PLAY_PAUSE | KEXT },
  { 0x24, VK_MEDIA_STOP | KEXT },
  { 0x2E, VK_VOLUME_DOWN | KEXT },
  { 0x30, VK_VOLUME_UP | KEXT },
  { 0x32, VK_BROWSER_HOME | KEXT },
  { 0x35, VK_DIVIDE | KEXT },
  { 0x37, VK_SNAPSHOT | KEXT },
  { 0x38, VK_RMENU | KEXT },
  { 0x47, VK_HOME | KEXT },
  { 0x48, VK_UP | KEXT },
  { 0x49, VK_PRIOR | KEXT },
  { 0x4B, VK_LEFT | KEXT },
  { 0x4D, VK_RIGHT | KEXT },
  { 0x4F, VK_END | KEXT },
  { 0x50, VK_DOWN | KEXT },
  { 0x51, VK_NEXT | KEXT },
  { 0x52, VK_INSERT | KEXT },
  { 0x53, VK_DELETE | KEXT },
  { 0x5B, VK_LWIN | KEXT },
  { 0x5C, VK_RWIN | KEXT },
  { 0x5D, VK_APPS | KEXT },
  { 0x5F, VK_SLEEP | KEXT },
  { 0x65, VK_BROWSER_SEARCH | KEXT },
  { 0x66, VK_BROWSER_FAVORITES | KEXT },
  { 0x67, VK_BROWSER_REFRESH | KEXT },
  { 0x68, VK_BROWSER_STOP | KEXT },
  { 0x69, VK_BROWSER_FORWARD | KEXT },
  { 0x6A, VK_BROWSER_BACK | KEXT },
  { 0x6B, VK_LAUNCH_APP1 | KEXT },
  { 0x6C, VK_LAUNCH_MAIL | KEXT },
  { 0x6D, VK_LAUNCH_MEDIA_SELECT | KEXT },
  { 0x1C, VK_RETURN | KEXT },
  { 0x46, VK_CANCEL | KEXT },
  { 0, 0 },
};

ROSDATA VSC_VK extcode1_to_vk[] = {
  { 0x1d, VK_PAUSE},
  { 0, 0 },
};

ROSDATA VK_TO_BIT modifier_keys[] = {
  { VK_SHIFT,   KSHIFT },
  { VK_CONTROL, KCTRL },
  { VK_MENU,    KALT },
  { 0,          0 }
};

ROSDATA MODIFIERS modifier_bits = {
  modifier_keys,
  7,
  { 0, 1, 2, 3, SHFT_INVALID, SHFT_INVALID, 4, 5 }
};

#define NOCAPS 0
#define CAPS   KSHIFT /* Caps -> shift */

ROSDATA VK_TO_WCHARS2 key_to_chars_2mod[] = {
  {VK_OEM_3,    NOCAPS, {0x094a, 0x0912} },
  {'Q',         NOCAPS, {0x094c, 0x0914} },
  {'W',         NOCAPS, {0x0948, 0x0910} },
  {'E',         NOCAPS, {0x093e, 0x0906} },
  {'T',         NOCAPS, {0x0942, 0x090a} },
  {'Y',         NOCAPS, {0x092c, 0x092d} },
  {'U',         NOCAPS, {0x0939, 0x0919} },
  {'O',         NOCAPS, {0x0926, 0x0927} },
  {'A',         NOCAPS, {0x094b, 0x0913} },
  {'S',         NOCAPS, {0x0947, 0x090f} },
  {'D',         NOCAPS, {0x094d, 0x0905} },
  {'G',         NOCAPS, {0x0941, 0x0909} },
  {'J',         NOCAPS, {0x0930, 0x0931} },
  {'L',         NOCAPS, {0x0924, 0x0925} },
  {'V',         NOCAPS, {0x0928, 0x0929} },
  {'B',         NOCAPS, {0x0935, 0x0934} },
  {'N',         NOCAPS, {0x0932, 0x0933} },
  {'M',         NOCAPS, {0x0938, 0x0936} },
  {VK_DECIMAL,  NOCAPS, {'.',    '.'   } },
  {VK_TAB,      NOCAPS, {'\t',   '\t'  } },
  {VK_ADD,      NOCAPS, {'+',    '+'   } },
  {VK_DIVIDE,   NOCAPS, {'/',    '/'   } },
  {VK_MULTIPLY, NOCAPS, {'*',    '*'   } },
  {VK_SUBTRACT, NOCAPS, {'-',    '-'   } },
  { 0, 0 }
};

ROSDATA VK_TO_WCHARS3 key_to_chars_3mod[] = {
  { VK_OEM_6,   NOCAPS, {0x093c   ,0x091e   ,0x001d} },
  { VK_OEM_5,   NOCAPS, {0x0949   ,0x0911   ,0x001c} },
  { VK_OEM_102, NOCAPS, {0x0949   ,0x0911   ,0x001c} },
  { VK_BACK,    NOCAPS, {'\b'     ,'\b'     ,0x007f} },
  { VK_ESCAPE,  NOCAPS, {0x001b   ,0x001b   ,0x001b} },
  { VK_RETURN,  NOCAPS, {'\r'     ,'\r'     ,'\n'  } },
  { VK_SPACE,   NOCAPS, {' '      ,' '      ,' '   } },
  { VK_CANCEL,  NOCAPS, {0x0003   ,0x0003   ,0x0003} },
  { 0, 0 }
};

ROSDATA VK_TO_WCHARS4 key_to_chars_4mod[] = {
  { VK_OEM_MINUS, NOCAPS, {'-', 0x0903, WCH_NONE, 0x001f} },
  { 0, 0 }
};

ROSDATA VK_TO_WCHARS5 key_to_chars_5mod[] = {
  { '1',          NOCAPS, {'1',    0x090d,   WCH_NONE, 0x200d,   0x0967  } },
  { '2',          NOCAPS, {'2',    0x0945,   WCH_NONE, 0x200c,   0x0968  } },
  { '3',          NOCAPS, {'3',    WCH_LGTR, WCH_NONE, WCH_NONE, 0x0969  } },
  { '4',          NOCAPS, {'4',    WCH_LGTR, WCH_NONE, WCH_NONE, 0x096a  } },
  { '5',          NOCAPS, {'5',    WCH_LGTR, WCH_NONE, WCH_NONE, 0x096b  } },
  { '6',          NOCAPS, {'6',    WCH_LGTR, WCH_NONE, 0x001e,   0x096c  } },
  { '7',          NOCAPS, {'7',    WCH_LGTR, WCH_NONE, WCH_NONE, 0x096d  } },
  { '8',          NOCAPS, {'8',    WCH_LGTR, WCH_NONE, WCH_NONE, 0x096e  } },
  { '9',          NOCAPS, {'9',    '(',      WCH_NONE, WCH_NONE, 0x096f  } },
  { '0',          NOCAPS, {'0',    ')',      WCH_NONE, WCH_NONE, 0x0966  } },
  { 'I',          NOCAPS, {0x0917, 0x0918,   WCH_NONE, WCH_NONE, 0x095a  } },
  { 'P',          NOCAPS, {0x091c, 0x091d,   WCH_NONE, WCH_NONE, 0x095b  } },
  { VK_OEM_1,     NOCAPS, {0x091a, 0x091b,   WCH_NONE, WCH_NONE, 0x0952  } },
  { 'Z',          NOCAPS, {0x0946, 0x090e,   WCH_NONE, WCH_NONE, 0x0953  } },
  { 'C',          NOCAPS, {0x092e, 0x0923,   WCH_NONE, WCH_NONE, 0x0954  } },
  { VK_OEM_COMMA, NOCAPS, {',',    0x0937,   WCH_NONE, WCH_NONE, 0x0970  } },
  { VK_OEM_2,     NOCAPS, {0x092f, 0x095f,   WCH_NONE, WCH_NONE, WCH_NONE} },
  { 0, 0 }
};

ROSDATA VK_TO_WCHARS6 key_to_chars_6mod[] = {
  { VK_OEM_PLUS,  NOCAPS, {0x0943, 0x090b, WCH_NONE, WCH_NONE, 0x0944,   0x0960} },
  { 'R',          NOCAPS, {0x0940, 0x0908, WCH_NONE, WCH_NONE, 0x0963,   0x0961} },
  { VK_OEM_4,     NOCAPS, {0x0921, 0x0922, 0x001b,   WCH_NONE, 0x095c,   0x095d} },
  { 'F',          NOCAPS, {0x093f, 0x0907, WCH_NONE, WCH_NONE, 0x0962,   0x090c} },
  { 'H',          NOCAPS, {0x092a, 0x092b, WCH_NONE, WCH_NONE, WCH_NONE, 0x095e} },
  { 'K',          NOCAPS, {0x0915, 0x0916, WCH_NONE, WCH_NONE, 0x0958,   0x0959} },
  { VK_OEM_7,     NOCAPS, {0x091f, 0x0920, WCH_NONE, WCH_NONE, WCH_NONE, 0x0951} },
  { 'X',          NOCAPS, {0x0902, 0x0901, WCH_NONE, WCH_NONE, WCH_NONE, 0x0950} },
  { VK_OEM_PERIOD,NOCAPS, {'.',    0x0964, WCH_NONE, WCH_NONE, 0x0965,   0x093d} },
  { 0, 0 }
};

ROSDATA VK_TO_WCHARS1 keypad_numbers[] = {
  { VK_NUMPAD0, 0, {'0'} },
  { VK_NUMPAD1, 0, {'1'} },
  { VK_NUMPAD2, 0, {'2'} },
  { VK_NUMPAD3, 0, {'3'} },
  { VK_NUMPAD4, 0, {'4'} },
  { VK_NUMPAD5, 0, {'5'} },
  { VK_NUMPAD6, 0, {'6'} },
  { VK_NUMPAD7, 0, {'7'} },
  { VK_NUMPAD8, 0, {'8'} },
  { VK_NUMPAD9, 0, {'9'} },
  { 0, 0 }
};

#define vk_master(n,x) { (PVK_TO_WCHARS1)x, n, sizeof(x[0]) }

ROSDATA VK_TO_WCHAR_TABLE vk_to_wchar_master_table[] = {
  vk_master(3,key_to_chars_3mod),
  vk_master(4,key_to_chars_4mod),
  vk_master(5,key_to_chars_5mod),
  vk_master(6,key_to_chars_6mod),
  vk_master(2,key_to_chars_2mod),
  vk_master(1,keypad_numbers),
  { 0,0,0 }
};

ROSDATA VSC_LPWSTR key_names[] = {
  { 0x01, L"Esc" },
  { 0x0e, L"Backspace" },
  { 0x0f, L"Tab" },
  { 0x1c, L"Enter" },
  { 0x1d, L"Ctrl" },
  { 0x2a, L"Shift" },
  { 0x36, L"Right Shift" },
  { 0x37, L"Num *" },
  { 0x38, L"Alt" },
  { 0x39, L"Space" },
  { 0x3a, L"Caps Lock" },
  { 0x3b, L"F1" },
  { 0x3c, L"F2" },
  { 0x3d, L"F3" },
  { 0x3e, L"F4" },
  { 0x3f, L"F5" },
  { 0x40, L"F6" },
  { 0x41, L"F7" },
  { 0x42, L"F8" },
  { 0x43, L"F9" },
  { 0x44, L"F10" },
  { 0x45, L"Pause" },
  { 0x46, L"Scroll Lock" },
  { 0x47, L"Num 7" },
  { 0x48, L"Num 8" },
  { 0x49, L"Num 9" },
  { 0x4a, L"Num -" },
  { 0x4b, L"Num 4" },
  { 0x4c, L"Num 5" },
  { 0x4d, L"Num 6" },
  { 0x4e, L"Num +" },
  { 0x4f, L"Num 1" },
  { 0x50, L"Num 2" },
  { 0x51, L"Num 3" },
  { 0x52, L"Num 0" },
  { 0x53, L"Num Del" },
  { 0x54, L"Sys Req" },
  { 0x57, L"F11" },
  { 0x58, L"F12" },
  { 0x7c, L"F13" },
  { 0x7d, L"F14" },
  { 0x7e, L"F15" },
  { 0x7f, L"F16" },
  { 0x80, L"F17" },
  { 0x81, L"F18" },
  { 0x82, L"F19" },
  { 0x83, L"F20" },
  { 0x84, L"F21" },
  { 0x85, L"F22" },
  { 0x86, L"F23" },
  { 0x87, L"F24" },
  { 0, NULL }
};

ROSDATA VSC_LPWSTR extended_key_names[] = {
  { 0x1c, L"Num Enter" },
  { 0x1d, L"Right Control" },
  { 0x35, L"Num /" },
  { 0x37, L"Prnt Scrn" },
  { 0x38, L"Right Alt" },
  { 0x45, L"Num Lock" },
  { 0x46, L"Break" },
  { 0x47, L"Home" },
  { 0x48, L"Up" },
  { 0x49, L"Page Up" },
  { 0x4b, L"Left" },
//{ 0x4c, L"Center" },
  { 0x4d, L"Right" },
  { 0x4f, L"End" },
  { 0x50, L"Down" },
  { 0x51, L"Page Down" },
  { 0x52, L"Insert" },
  { 0x53, L"Delete" },
  { 0x54, L"<Odyssey>" },
  { 0x56, L"Help" },
  { 0x5b, L"Left <Odyssey>" },
  { 0x5c, L"Right <Odyssey>" },
  { 0x5d, L"Application" },
  { 0, NULL }
};

ROSDATA LIGATURE3 Ligature[] = {
  { '3', 1, {0x094d, 0x0930, WCH_NONE} },
  { '4', 1, {0x0930, 0x094d, WCH_NONE} },
  { '5', 1, {0x091c, 0x094d, 0x091e  } },
  { '6', 1, {0x0924, 0x094d, 0x0930  } },
  { '7', 1, {0x0915, 0x094d, 0x0937  } },
  { '8', 1, {0x0936, 0x094d, 0x0930  } },
  {0, 0}
};

/* Finally, the master table */
ROSDATA KBDTABLES keyboard_layout_table = {
  /* modifier assignments */
  &modifier_bits,

  /* character from vk tables */
  vk_to_wchar_master_table,

  /* diacritical marks */
  NULL,

  /* Key names */
  (VSC_LPWSTR *)key_names,
  (VSC_LPWSTR *)extended_key_names,
  NULL, /* Dead key names */

  /* scan code to virtual key maps */
  scancode_to_vk,
  sizeof(scancode_to_vk) / sizeof(scancode_to_vk[0]),
  extcode0_to_vk,
  extcode1_to_vk,

  MAKELONG(1,1), /* Version 1.0 */

  /* Ligatures */
  3,
  sizeof(Ligature[0]),
  (PLIGATURE1)Ligature
};

PKBDTABLES WINAPI KbdLayerDescriptor(VOID) {
  return &keyboard_layout_table;
}

INT WINAPI
DllMain(
  PVOID hinstDll,
  ULONG dwReason,
  PVOID reserved)
{
  return 1;
}

