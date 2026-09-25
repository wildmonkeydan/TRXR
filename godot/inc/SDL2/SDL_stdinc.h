#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdalign.h>

// Partially lifted from the original SDL_stdinc.h, as such the original hear is provided
/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2019 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifdef __CC_ARM
/* ARM's compiler throws warnings if we use an enum: like "SDL_bool x = a < b;" */
#define SDL_FALSE 0
#define SDL_TRUE 1
typedef int SDL_bool;
#else
typedef enum
{
    SDL_FALSE = 0,
    SDL_TRUE = 1
} SDL_bool;
#endif

/**
 * \brief A signed 8-bit integer type.
 */
#define SDL_MAX_SINT8   ((Sint8)0x7F)           /* 127 */
#define SDL_MIN_SINT8   ((Sint8)(~0x7F))        /* -128 */
typedef int8_t Sint8;
/**
 * \brief An unsigned 8-bit integer type.
 */
#define SDL_MAX_UINT8   ((Uint8)0xFF)           /* 255 */
#define SDL_MIN_UINT8   ((Uint8)0x00)           /* 0 */
typedef uint8_t Uint8;
/**
 * \brief A signed 16-bit integer type.
 */
#define SDL_MAX_SINT16  ((Sint16)0x7FFF)        /* 32767 */
#define SDL_MIN_SINT16  ((Sint16)(~0x7FFF))     /* -32768 */
typedef int16_t Sint16;
/**
 * \brief An unsigned 16-bit integer type.
 */
#define SDL_MAX_UINT16  ((Uint16)0xFFFF)        /* 65535 */
#define SDL_MIN_UINT16  ((Uint16)0x0000)        /* 0 */
typedef uint16_t Uint16;
/**
 * \brief A signed 32-bit integer type.
 */
#define SDL_MAX_SINT32  ((Sint32)0x7FFFFFFF)    /* 2147483647 */
#define SDL_MIN_SINT32  ((Sint32)(~0x7FFFFFFF)) /* -2147483648 */
typedef int32_t Sint32;
/**
 * \brief An unsigned 32-bit integer type.
 */
#define SDL_MAX_UINT32  ((Uint32)0xFFFFFFFFu)   /* 4294967295 */
#define SDL_MIN_UINT32  ((Uint32)0x00000000)    /* 0 */
typedef uint32_t Uint32;

/**
 * \brief A signed 64-bit integer type.
 */
#define SDL_MAX_SINT64  ((Sint64)0x7FFFFFFFFFFFFFFFll)      /* 9223372036854775807 */
#define SDL_MIN_SINT64  ((Sint64)(~0x7FFFFFFFFFFFFFFFll))   /* -9223372036854775808 */
typedef int64_t Sint64;
/**
 * \brief An unsigned 64-bit integer type.
 */
#define SDL_MAX_UINT64  ((Uint64)0xFFFFFFFFFFFFFFFFull)     /* 18446744073709551615 */
#define SDL_MIN_UINT64  ((Uint64)(0x0000000000000000ull))   /* 0 */
typedef uint64_t Uint64;

/* @} *//* Basic data types */

/* Make sure we have macros for printing 64 bit values.
 * <stdint.h> should define these but this is not true all platforms.
 * (for example win32) */
#ifndef SDL_PRIs64
#ifdef PRIs64
#define SDL_PRIs64 PRIs64
#elif defined(__WIN32__)
#define SDL_PRIs64 "I64d"
#elif defined(__LINUX__) && defined(__LP64__)
#define SDL_PRIs64 "ld"
#else
#define SDL_PRIs64 "lld"
#endif
#endif
#ifndef SDL_PRIu64
#ifdef PRIu64
#define SDL_PRIu64 PRIu64
#elif defined(__WIN32__)
#define SDL_PRIu64 "I64u"
#elif defined(__LINUX__) && defined(__LP64__)
#define SDL_PRIu64 "lu"
#else
#define SDL_PRIu64 "llu"
#endif
#endif
#ifndef SDL_PRIx64
#ifdef PRIx64
#define SDL_PRIx64 PRIx64
#elif defined(__WIN32__)
#define SDL_PRIx64 "I64x"
#elif defined(__LINUX__) && defined(__LP64__)
#define SDL_PRIx64 "lx"
#else
#define SDL_PRIx64 "llx"
#endif
#endif
#ifndef SDL_PRIX64
#ifdef PRIX64
#define SDL_PRIX64 PRIX64
#elif defined(__WIN32__)
#define SDL_PRIX64 "I64X"
#elif defined(__LINUX__) && defined(__LP64__)
#define SDL_PRIX64 "lX"
#else
#define SDL_PRIX64 "llX"
#endif
#endif

/**
 *  \name The two types of endianness
 */
/* @{ */


/**
 * A value to represent littleendian byteorder.
 *
 * This is used with the preprocessor macro SDL_BYTEORDER, to determine a
 * platform's byte ordering:
 *
 * ```c
 * #if SDL_BYTEORDER == SDL_LIL_ENDIAN
 * SDL_Log("This system is littleendian.");
 * #endif
 * ```
 *
 * \since This macro is available since SDL 3.2.0.
 *
 * \sa SDL_BYTEORDER
 * \sa SDL_BIG_ENDIAN
 */
#define SDL_LIL_ENDIAN  1234

/**
 * A value to represent bigendian byteorder.
 *
 * This is used with the preprocessor macro SDL_BYTEORDER, to determine a
 * platform's byte ordering:
 *
 * ```c
 * #if SDL_BYTEORDER == SDL_BIG_ENDIAN
 * SDL_Log("This system is bigendian.");
 * #endif
 * ```
 *
 * \since This macro is available since SDL 3.2.0.
 *
 * \sa SDL_BYTEORDER
 * \sa SDL_LIL_ENDIAN
 */
#define SDL_BIG_ENDIAN  4321

/* @} */

#ifndef SDL_BYTEORDER
#ifdef SDL_WIKI_DOCUMENTATION_SECTION

/**
 * A macro that reports the target system's byte order.
 *
 * This is set to either SDL_LIL_ENDIAN or SDL_BIG_ENDIAN (and maybe other
 * values in the future, if something else becomes popular). This can be
 * tested with the preprocessor, so decisions can be made at compile time.
 *
 * ```c
 * #if SDL_BYTEORDER == SDL_BIG_ENDIAN
 * SDL_Log("This system is bigendian.");
 * #endif
 * ```
 *
 * \since This macro is available since SDL 3.2.0.
 *
 * \sa SDL_LIL_ENDIAN
 * \sa SDL_BIG_ENDIAN
 */
#define SDL_BYTEORDER   SDL_LIL_ENDIAN___or_maybe___SDL_BIG_ENDIAN
#elif defined(SDL_PLATFORM_LINUX) || defined(__GLIBC__)
#include <endian.h>
#define SDL_BYTEORDER  __BYTE_ORDER
#elif defined(SDL_PLATFORM_SOLARIS)
#include <sys/byteorder.h>
#if defined(_LITTLE_ENDIAN)
#define SDL_BYTEORDER   SDL_LIL_ENDIAN
#elif defined(_BIG_ENDIAN)
#define SDL_BYTEORDER   SDL_BIG_ENDIAN
#else
#error Unsupported endianness
#endif
#elif defined(SDL_PLATFORM_OPENBSD) || defined(__DragonFly__)
#include <endian.h>
#define SDL_BYTEORDER  BYTE_ORDER
#elif defined(SDL_PLATFORM_FREEBSD) || defined(SDL_PLATFORM_NETBSD)
#include <sys/endian.h>
#define SDL_BYTEORDER  BYTE_ORDER
/* predefs from newer gcc and clang versions: */
#elif defined(__ORDER_LITTLE_ENDIAN__) && defined(__ORDER_BIG_ENDIAN__) && defined(__BYTE_ORDER__)
#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define SDL_BYTEORDER   SDL_LIL_ENDIAN
#elif (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define SDL_BYTEORDER   SDL_BIG_ENDIAN
#else
#error Unsupported endianness
#endif /**/
#else
#if defined(__hppa__) || \
    defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || \
    (defined(__MIPS__) && defined(__MIPSEB__)) || \
    defined(__ppc__) || defined(__POWERPC__) || defined(__powerpc__) || defined(__PPC__) || \
    defined(__sparc__) || defined(__sparc)
#define SDL_BYTEORDER   SDL_BIG_ENDIAN
#else
#define SDL_BYTEORDER   SDL_LIL_ENDIAN
#endif
#endif /* SDL_PLATFORM_LINUX */
#endif /* !SDL_BYTEORDER */

void* SDL_memset(void *dst, int c, size_t len);

const char * SDL_getenv(const char *name);
