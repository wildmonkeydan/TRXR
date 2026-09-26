#pragma once
#include "SDL_keycode.h"

typedef struct SDL_Keysym
{
    SDL_Scancode scancode;      /**< SDL physical key code - see SDL_Scancode for details */
    SDL_Keycode sym;            /**< SDL virtual key code - see SDL_Keycode for details */
    Uint16 mod;                 /**< current key modifiers - see SDL_Keymod for details */
    Uint32 unused;
} SDL_Keysym;


SDL_Keycode SDL_GetKeyFromScancode(SDL_Scancode scancode);
SDL_Keycode SDL_GetKeyFromName(const char *name);
SDL_Scancode SDL_GetScancodeFromName(const char *name);
const char* SDL_GetKeyName(SDL_Keycode key);
const char* SDL_GetScancodeName(SDL_Scancode scancode);
SDL_Scancode SDL_GetScancodeFromKey(SDL_Keycode key);