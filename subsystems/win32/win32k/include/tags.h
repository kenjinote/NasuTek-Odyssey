#pragma once

#define TAG_STRING      ' RTS' /* string */
#define TAG_HOOK        'ohsU' /* hook */
#define TAG_MENUITEM    'emsU' /* menu item */
#define TAG_MSG         'GSEM' /* message */
#define TAG_USRMSG      'GSMU' /* user message */
#define TAG_SBARINFO    'NIBS' /* scrollbar info */
#define TAG_TIMERBMP    'BMIT' /* timers bitmap */
#define TAG_WINSTA      'ATSW' /* window station */
#define TAG_FONT        'ETNF' /* font entry */
#define TAG_BEZIER      'RZEB' /* bezier */
#define TAG_SHAPE       'phSG' /* shape */
#define TAG_COLORMAP    'MLOC' /* color map */
#define TAG_GDIHNDTBLE  'bthG' /* gdi handle table */
#define TAG_DIB         ' BID' /* dib */

/* gdi objects from the handle table */
#define TAG_DC          GDITAG_HMGR_LOOKASIDE_DC_TYPE
#define TAG_REGION      GDITAG_HMGR_LOOKASIDE_RGN_TYPE
#define TAG_SURFACE     GDITAG_HMGR_LOOKASIDE_SURF_TYPE
#define TAG_CLIENTOBJ   '60hG'
#define TAG_PATH        '70hG'
#define TAG_PALETTE     GDITAG_HMGR_LOOKASIDE_PAL_TYPE
#define TAG_ICMLCS      '90hG'
#define TAG_LFONT       GDITAG_HMGR_LOOKASIDE_LFONT_TYPE
#define TAG_RFONT       ';0gG' /* correct? */
#define TAG_PFE         '<0hG'
#define TAG_PFT         '=0hG' /* correct? */
#define TAG_ICMCXF      '>0hG' /* correct? */
#define TAG_SPRITE      '?0hG' /* correct? */
#define TAG_BRUSH       GDITAG_HMGR_LOOKASIDE_BRUSH_TYPE
#define TAG_UMPD        'A0hG' /* correct? */
#define TAG_SPACE       'c0hG' /* correct? */
#define TAG_META        'E0hG' /* correct? */
#define TAG_EFSTATE     'F0hG' /* correct? */
#define TAG_BMFD        'G0hG' /* correct? */
#define TAG_VTFD        'H0hG' /* correct? */
#define TAG_TTFD        'I0hG' /* correct? */
#define TAG_RC          'J0hG' /* correct? */
#define TAG_TEMP        'K0hG' /* correct? */
#define TAG_DRVOBJ      'L0hG' /* correct? */
#define TAG_DCIOBJ      'M0hG' /* correct? */
#define TAG_SPOOL       'N0hG' /* correct? */

/* Dx internal tags rember I do not known if it right namees */
#define TAG_DXPVMLIST   'LPXD' /* pmvlist for the driver */
#define TAG_DXFOURCC    'OFXD' /* pdwFourCC for the driver */
#define TAG_DDRAW       '1 hD'
#define TAG_DDSURF      '2 hD'
#define TAG_EDDGBL      'GDDE' /* ? edd_directdraw_global ??*/

/* Official tags */
#define GDITAG_ATM_FONT                  'ebdA'
#define GDITAG_BMP_FONT                  'dfmB'
#define GDITAG_ENG_EVENT                 'msfD'
#define GDITAG_DWM_HWND_LOOKUP           'LmwD'
#define GDITAG_DWM_VALIDATION            'vMWD'
#define GDITAG_LOCKED_PRIMARY            'ddxD'
#define GDITAG_DC_COLOR_TRANSFORM        'bdaG'
#define GDITAG_DC_FONT                   'ddaG'
#define GDITAG_ALPHABLEND                'plaG'
#define GDITAG_BRUSH_FREELIST            'fabG'
#define GDITAG_ICM_DIB_LIST              'ldbG'
#define GDITAG_FONTCACHE                 'cacG'
#define GDITAG_SCRIPTS                   'lscG'
#define GDITAG_CHAR_TO_WIDE_CHAR         'cwcG'
#define GDITAG_RBRUSH                    'rbdG'
#define GDITAG_DC_FREELIST               'fcdG'
#define GDITAG_DWMSTATE                  'scDG'
#define GDITAG_DEVMODE                   'vedG'
#define GDITAG_PDEV                      'veDG'
#define GDITAG_HGLYPH_ARRAY              'mfdG'
#define GDITAG_DRVSUP                    'srdG'
#define GDITAG_CLIPOBJ                   'vrdG'
#define GDITAG_SEMAPHORE_VALIDATE        'dtdG'
#define GDITAG_WATCHDOG                  'dwdG'
#define GDITAG_ENGBRUSH                  'rbeG'
#define GDITAG_ENUM_DISPLAY_DEVICES      'ddeG'
#define GDITAG_EDGE                      'gdeG'
#define GDITAG_TRIANGLEDATA              'gdEg'
#define GDITAG_TEXTOUT                   'oteG'
#define GDITAG_FONT_DEFAULT_FAMILY       'fdfG'
#define GDITAG_FONTFILEVIEW              'vffG'
#define GDITAG_UNIVERSAL_FONT_ID         'difG'
#define GDITAG_FILEPATH                  'liFG'
#define GDITAG_MAPFILE                   'lifG'
#define GDITAG_FLOODFILL                 'dlFG'
#define GDITAG_RFONT                     'tnfG'
#define GDITAG_FONT_SUB                  'bsfG'
#define GDITAG_FONT_STOCKFONT            'fsfG'
#define GDITAG_FAST_MUTEX                'msfG'
#define GDITAG_FULLSCREEN                'lufG'
#define GDITAG_FONTVICTIM                'ivfG'
#define GDITAG_GLYPHBLOCK                ' bgG'
#define GDITAG_GDEVICE                   'vdgG'
#define GDITAG_GLYPHSET                  'slgG'
#define GDITAG_HGLYPH                    'ylgG'
#define GDITAG_HMGR_LFONT_TYPE           ':?hG'
#define GDITAG_HMGR_RFONT_TYPE           ';?hG'
#define GDITAG_HMGR_BRUSH_TYPE           '@?hG'
#define GDITAG_HMGR_ICMCXF_TYPE          '>?hG'
#define GDITAG_HMGR_DEF_TYPE             '0?hG'
#define GDITAG_HMGR_DC_TYPE              '1?hG'
#define GDITAG_HMGR_RGN_TYPE             '4?hG'
#define GDITAG_HMGR_SURF_TYPE            '5?hG'
#define GDITAG_HMGR_CLIENTOBJ_TYPE       '6?hG'
#define GDITAG_HMGR_PATH_TYPE            '7?hG'
#define GDITAG_HMGR_PAL_TYPE             '8?hG'
#define GDITAG_HMGR_ICMLCS_TYPE          '9?hG'
#define GDITAG_HMGR_UMPD_TYPE            'A?hG'
#define GDITAG_HMGR_HLSURF_TYPE          'B?hG'
#define GDITAG_HMGR_META_TYPE            'E?hG'
#define GDITAG_HMGR_DRVOBJ_TYPE          'L?hG'
#define GDITAG_HMGR_SPRITE_TYPE          '??hG'
#define GDITAG_HMGR_START                '00hG'
#define GDITAG_PFE_HASHBUCKET            'bahG'
#define GDITAG_PFE_HASHTABLE             'sahG'
#define GDITAG_HMGR_LOCK                 'lmhG'
#define GDITAG_HALFTONE_COLORTRIAD       'cthG'
#define GDITAG_HMGR_TEMP                 'mthG'
#define GDITAG_DDCCI                     'c2iG'
#define GDITAG_ICM                       'mciG'
#define GDITAG_KMODE_BITMAP              'mbkG'
#define GDITAG_HMGR_LOOKASIDE_LFONT_TYPE ':alG'
#define GDITAG_HMGR_LOOKASIDE_RFONT_TYPE ';alG'
#define GDITAG_HMGR_LOOKASIDE_BRUSH_TYPE '@alG'
#define GDITAG_HMGR_LOOKASIDE_START      '0alG'
#define GDITAG_HMGR_LOOKASIDE_DC_TYPE    '1alG'
#define GDITAG_HMGR_LOOKASIDE_RGN_TYPE   '4alG'
#define GDITAG_HMGR_LOOKASIDE_SURF_TYPE  '5alG'
#define GDITAG_HMGR_LOOKASIDE_PAL_TYPE   '8alG'
#define GDITAG_LDEV                      'vdlG'
#define GDITAG_LOCALEINFO                'dilG'
#define GDITAG_PFE_LINK                  'knlG'
#define GDITAG_FONT_MAPPER               'pamG'
#define GDITAG_DISPURF_SORT              'osmG'
#define GDITAG_MULTIFONT                 'lumG'
#define GDITAG_NLS                       'slnG'
#define GDITAG_OPENGL                    'lgoG'
#define GDITAG_OPM                       'MPOG'
#define GDITAG_PALETTE                   'laPG'
#define GDITAG_PANNING_PDEV              'napG'
#define GDITAG_PATHOBJ                   'tapG'
#define GDITAG_PFF_INDEXES               'efpG'
#define GDITAG_PFF                       'ffpG'
#define GDITAG_PFT                       'tfpG'
#define GDITAG_PLGBLT_DATA               'bgpG'
#define GDITAG_PRINTCLIENTID             'dipG'
#define GDITAG_CLIP_PATHOBJ              'oppG'
#define GDITAG_PROXYPORT                 'tppG'
#define GDITAG_PRESENT                   'erpG'
#define GDITAG_LFONT_QUICKLOOKUP         'knqG'
#define GDITAG_PALETTE_RGB_XLATE         'bgrG'
#define GDITAG_REGION                    'ngrG'
#define GDITAG_SEMAPHORE                 'mesG'
#define GDITAG_SPRITE                    ' psG'
#define GDITAG_METASPRITE                'mpsG'
#define GDITAG_SPRITESCAN                'rpsG'
#define GDITAG_STACKTRACE                'atsG'
#define GDITAG_STRETCHBLT                'htsG'
#define GDITAG_PENSTYLE                  'ytsG'
#define GDITAG_SFM                       'xusG'
#define GDITAG_TEMP                      'pmtG'
#define GDITAG_TEMP_THREADLOCK           'pmTG'
#define GDITAG_TEXTMETRICS               'wmtG'
#define GDITAG_PFF_DATA                  'pvtG'
#define GDITAG_TRIANGLE_MESH             'tvtG'
#define GDITAG_TEXT                      'txtG'
#define GDITAG_UMODE_BITMAP              'mbuG'
#define GDITAG_ENG_USER_MEM_ALLOC_TABLE  'amUG'
#define GDITAG_UMPD                      'pmuG'
#define GDITAG_HDEV                      'sdvG'
#define GDITAG_VDEV                      'vdVG'
#define GDITAG_MULTISAVEBITS             'smVG'
#define GDITAG_MDSURF                    'fsVG'
#define GDITAG_WNDOBJ                    'dnwG'
#define GDITAG_PXLATE                    'tlxG'
#define GDITAG_UMPDOBJ                   'dpxG'
#define GDITAG_FONT_LINK                 'flnk'
#define GDITAG_PANNING_SURFACE           'fSAP'
#define GDITAG_PANNING_SHADOWLOCK        'olSP'
#define GDITAG_SINGLEREADERLOCK          'lrsS'
#define GDITAG_TT_FONT_CACHE             'CFTT'
#define GDITAG_TT_FONT                   'dftT'
#define GDITAG_VF_FONT                   'dftV'
#define GDITAG_W32PIDLOCK                'l23W'
#define GDITAG_HANDLEPUSHLOCK            'lpHG'

#define USERTAG_SERVICE_TABLE            'lacU'
#define USERTAG_MONITOR_MARGIN           'mamU'
#define USERTAG_REDIRECT                 'rdrU'
#define USERTAG_ACCEL                    'casU'
#define USERTAG_ATTACHINFO               'iasU'
#define USERTAG_ALTTAB                   'lasU'
#define USERTAG_DEBUG                    'gbsU'
#define USERTAG_CLIPBOARD                'bcsU'
#define USERTAG_CALLBACK                 'ccsU'
#define USERTAG_COMPOSITIONPROP          'dcsU'
#define USERTAG_CLIENTTHREADINFO         'icsU'
#define USERTAG_CLASS                    'lcsU'
#define USERTAG_SCANCODEMAP              'mcsU'
#define USERTAG_CLIPBOARDPALETTE         'pcsU'
#define USERTAG_COLORS                   'rcsU'
#define USERTAG_CHECKPT                  'tcsU'
#define USERTAG_CURSOR                   'ucsU'
#define USERTAG_COLORVALUES              'vcsU'
#define USERTAG_DDE1                     '1dsU'
#define USERTAG_DDE2                     '2dsU'
#define USERTAG_DDE4                     '4dsU'
#define USERTAG_DDE5                     '5dsU'
#define USERTAG_DDE6                     '6dsU'
#define USERTAG_DDE7                     '7dsU'
#define USERTAG_DDE8                     '8dsU'
#define USERTAG_DDE9                     '9dsU'
#define USERTAG_DDEa                     'AdsU'
#define USERTAG_DDEb                     'BdsU'
#define USERTAG_DCE                      'cdsU'
#define USERTAG_DDEd                     'DdsU'
#define USERTAG_DDE                      'EdsU'
#define USERTAG_DEVICEINFO               'IDsU'
#define USERTAG_DISPLAYINFO              'idsU'
#define USERTAG_DRAGDROP                 'sdsU'
#define USERTAG_DEVICECHANGE             'vdsU'
#define USERTAG_WSEXCOMPINVALID          'CEsU'
#define USERTAG_ERESOURCE                'resU'
#define USERTAG_EVENT                    'vesU'
#define USERTAG_FORWARDTOUCHMESSAGE      'tfsU'
#define USERTAG_GRANTEDHANDLES           'hgsU'
#define USERTAG_GESTUREINFO              'igsU'
#define USERTAG_GLOBALTHREADLOCK         'lgsU'
#define USERTAG_GHOST                    'tgsU'
#define USERTAG_HIDDATA                  'ahsU'
#define USERTAG_HIDDESC                  'DhsU'
#define USERTAG_HOTKEY                   'khsU'
#define USERTAG_IMEHOTKEY                'hisU'
#define USERTAG_IME                      'misU'
#define USERTAG_W32JOB                   'bjsU'
#define USERTAG_W32JOBEXTRA              'xjsU'
#define USERTAG_KBDLAYOUT                'bksU'
#define USERTAG_KBDEXID                  'eksU'
#define USERTAG_KBDFILE                  'fksU'
#define USERTAG_KBDSTATE                 'sksU'
#define USERTAG_KBDTABLE                 'tksU'
#define USERTAG_LOOKASIDE                'alsU'
#define USERTAG_LOGDESKTOP               'dlsU'
#define USERTAG_LOCKRECORD               'rlsU'
#define USERTAG_MAGNIFICATION            'gmsU'
#define USERTAG_MIRROR                   'imsU'
#define USERTAG_MESSAGE_FILTER           'lmsU'
#define USERTAG_MONITORRECTS             'rmsU'
#define USERTAG_MOVESIZE                 'smsU'
#define USERTAG_MENUSTATE                'tmsU'
#define USERTAG_NKAPC                    'ansU'
#define USERTAG_NOTIFY                   'ynsU'
#define USERTAG_POWERBROADCAST           'bpsU'
#define USERTAG_PROCESSINFO              'ipsU'
#define USERTAG_POPUPMENU                'mpsU'
#define USERTAG_PROFILEUSERNAME          'npsU'
#define USERTAG_POWER                    'opsU'
#define USERTAG_PNP                      'ppsU'
#define USERTAG_PROFILE                  'rpsU'
#define USERTAG_WINDOWARRAY              'wpsU'
#define USERTAG_SQM                      'mqsU'
#define USERTAG_QMSG                     'mqsU'
#define USERTAG_Q                        'uqsU'
#define USERTAG_RTL                      'trsU'
#define USERTAG_SMS_ASYNC                'assU'
#define USERTAG_SPB                      'bssU'
#define USERTAG_SMS_CAPTURE              'cssU'
#define USERTAG_SHADOW                   'dssU'
#define USERTAG_SECURITY                 'essU'
#define USERTAG_SENDINPUT                'issU'
#define USERTAG_SENDTOUCHINPUT           'jssU'
#define USERTAG_SMS                      'mssU'
#define USERTAG_SMS_STRING               'sssU'
#define USERTAG_SCROLLTRACK              'tssU'
#define USERTAG_SWP                      'wssU'
#define USERTAG_SYSTEM                   'yssU'
#define USERTAG_TRACKDESKTOP             'dtsU'
#define USERTAG_THREADINFO               'itsU'
#define USERTAG_STACK                    'ktsU'
#define USERTAG_TIMER                    'mtsU'
#define USERTAG_TOKEN                    'otsU'
#define USERTAG_SECTION                  'stsU'
#define USERTAG_TEXT                     'xtsU'
#define USERTAG_TEXT2                    'ytsU'
#define USERTAG_TOUCHINPUTINFO           'ztsU'
#define USERTAG_UNICODEBUFFER            'busU'
#define USERTAG_UIPI_SQM                 'susU'
#define USERTAG_VISRGN                   'ivsU'
#define USERTAG_VWPL                     'lvsU'
#define USERTAG_WINDOW                   'dwsU'
#define USERTAG_WINEVENT                 'ewsU'
#define USERTAG_WINDOWLIST               'lwsU'
#define USERTAG_WOWTDB                   'owsU'
#define USERTAG_WOWPROCESSINFO           'pwsU'
#define USERTAG_WOWTHREADINFO            'twsU'
