#pragma once
#include "SDL_stdinc.h"
#include "SDL_keyboard.h"
#include "SDL_error.h"

/**
 * Information about the version of SDL in use.
 *
 * Represents the library's version as three levels: major revision
 * (increments with massive changes, additions, and enhancements), minor
 * revision (increments with backwards-compatible changes to the major
 * revision), and patchlevel (increments with fixes to the minor revision).
 *
 * \sa SDL_VERSION
 * \sa SDL_GetVersion
 */
typedef struct SDL_version
{
    Uint8 major;        /**< major version */
    Uint8 minor;        /**< minor version */
    Uint8 patch;        /**< update version */
} SDL_version;

/* Printable format: "%d.%d.%d", MAJOR, MINOR, PATCHLEVEL
*/
#define SDL_MAJOR_VERSION   2
#define SDL_MINOR_VERSION   33
#define SDL_PATCHLEVEL      0

/**
 * Macro to determine SDL version program was compiled against.
 *
 * This macro fills in a SDL_version structure with the version of the library
 * you compiled against. This is determined by what header the compiler uses.
 * Note that if you dynamically linked the library, you might have a slightly
 * newer or older version at runtime. That version can be determined with
 * SDL_GetVersion(), which, unlike SDL_VERSION(), is not a macro.
 *
 * \param x A pointer to a SDL_version struct to initialize.
 *
 * \sa SDL_version
 * \sa SDL_GetVersion
 */
#define SDL_VERSION(x)                          \
{                                   \
    (x)->major = SDL_MAJOR_VERSION;                 \
    (x)->minor = SDL_MINOR_VERSION;                 \
    (x)->patch = SDL_PATCHLEVEL;                    \
}

typedef Uint32 SDL_InitFlags;

#define SDL_INIT_TIMER      0x00000001u
#define SDL_INIT_AUDIO      0x00000010u /**< `SDL_INIT_AUDIO` implies `SDL_INIT_EVENTS` */
#define SDL_INIT_VIDEO      0x00000020u /**< `SDL_INIT_VIDEO` implies `SDL_INIT_EVENTS`, should be initialized on the main thread */
#define SDL_INIT_JOYSTICK   0x00000200u /**< `SDL_INIT_JOYSTICK` implies `SDL_INIT_EVENTS` */
#define SDL_INIT_HAPTIC     0x00001000u
#define SDL_INIT_GAMECONTROLLER    0x00002000u /**< `SDL_INIT_GAMEPAD` implies `SDL_INIT_JOYSTICK` */
#define SDL_INIT_EVENTS     0x00004000u
#define SDL_INIT_SENSOR     0x00008000u /**< `SDL_INIT_SENSOR` implies `SDL_INIT_EVENTS` */
#define SDL_INIT_CAMERA     0x00010000u /**< `SDL_INIT_CAMERA` implies `SDL_INIT_EVENTS` */

int SDL_Init(SDL_InitFlags flags);
void SDL_Quit(void);

Uint32 SDL_WasInit(Uint32 flags);
int SDL_InitSubSystem(SDL_InitFlags flags);
void SDL_QuitSubSystem(SDL_InitFlags flags);

char* SDL_GetBasePath(void);
