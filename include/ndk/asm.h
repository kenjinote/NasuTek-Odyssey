/*++ NDK Version: 0095

Copyright (c) Alex Ionescu.  All rights reserved.

Header Name:

    asm.h

Abstract:

    Portability header to choose the correct Architecture-specific header.

Author:

    Alex Ionescu (alex.ionescu@odyssey.com)   06-Oct-2004

--*/

#if defined(_M_IX86)
#include <i386/asm.h>
#elif defined(_M_AMD64)
#include <amd64/asm.h>
#elif defined(_M_ARM) || defined(_M_PPC)
//
// ARM and PPC ports don't use asm.h
//
#else
#error Unsupported Architecture
#endif
