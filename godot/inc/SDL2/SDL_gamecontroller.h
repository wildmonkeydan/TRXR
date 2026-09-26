#pragma once
#include "SDL_events.h"
#include "SDL_error.h"

/**
 * The gamecontroller structure used to identify an SDL game controller
 */
struct _SDL_GameController;
typedef struct _SDL_GameController SDL_GameController;

typedef enum SDL_GameControllerType
{
    SDL_CONTROLLER_TYPE_UNKNOWN = 0,
    SDL_CONTROLLER_TYPE_XBOX360,
    SDL_CONTROLLER_TYPE_XBOXONE,
    SDL_CONTROLLER_TYPE_PS3,
    SDL_CONTROLLER_TYPE_PS4,
    SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO,
    SDL_CONTROLLER_TYPE_VIRTUAL,
    SDL_CONTROLLER_TYPE_PS5,
    SDL_CONTROLLER_TYPE_AMAZON_LUNA,
    SDL_CONTROLLER_TYPE_GOOGLE_STADIA,
    SDL_CONTROLLER_TYPE_NVIDIA_SHIELD,
    SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_LEFT,
    SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_RIGHT,
    SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_PAIR,
    SDL_CONTROLLER_TYPE_MAX
} SDL_GameControllerType;

typedef enum SDL_GameControllerButton
{
    SDL_CONTROLLER_BUTTON_INVALID = -1,
    SDL_CONTROLLER_BUTTON_A,
    SDL_CONTROLLER_BUTTON_B,
    SDL_CONTROLLER_BUTTON_X,
    SDL_CONTROLLER_BUTTON_Y,
    SDL_CONTROLLER_BUTTON_BACK,
    SDL_CONTROLLER_BUTTON_GUIDE,
    SDL_CONTROLLER_BUTTON_START,
    SDL_CONTROLLER_BUTTON_LEFTSTICK,
    SDL_CONTROLLER_BUTTON_RIGHTSTICK,
    SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
    SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
    SDL_CONTROLLER_BUTTON_DPAD_UP,
    SDL_CONTROLLER_BUTTON_DPAD_DOWN,
    SDL_CONTROLLER_BUTTON_DPAD_LEFT,
    SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
    SDL_CONTROLLER_BUTTON_MISC1,    /* Xbox Series X share button, PS5 microphone button, Nintendo Switch Pro capture button, Amazon Luna microphone button */
    SDL_CONTROLLER_BUTTON_PADDLE1,  /* Xbox Elite paddle P1 (upper left, facing the back) */
    SDL_CONTROLLER_BUTTON_PADDLE2,  /* Xbox Elite paddle P3 (upper right, facing the back) */
    SDL_CONTROLLER_BUTTON_PADDLE3,  /* Xbox Elite paddle P2 (lower left, facing the back) */
    SDL_CONTROLLER_BUTTON_PADDLE4,  /* Xbox Elite paddle P4 (lower right, facing the back) */
    SDL_CONTROLLER_BUTTON_TOUCHPAD, /* PS4/PS5 touchpad button */
    SDL_CONTROLLER_BUTTON_MAX
} SDL_GameControllerButton;

typedef enum SDL_GameControllerAxis
{
    SDL_CONTROLLER_AXIS_INVALID = -1,
    SDL_CONTROLLER_AXIS_LEFTX,
    SDL_CONTROLLER_AXIS_LEFTY,
    SDL_CONTROLLER_AXIS_RIGHTX,
    SDL_CONTROLLER_AXIS_RIGHTY,
    SDL_CONTROLLER_AXIS_TRIGGERLEFT,
    SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
    SDL_CONTROLLER_AXIS_MAX
} SDL_GameControllerAxis;

/**
 * The largest value an SDL_Joystick's axis can report.
 *
 * \since This macro is available since SDL 3.2.0.
 *
 * \sa SDL_JOYSTICK_AXIS_MIN
 */
#define SDL_JOYSTICK_AXIS_MAX   32767

/**
 * The smallest value an SDL_Joystick's axis can report.
 *
 * This is a negative number!
 *
 * \since This macro is available since SDL 3.2.0.
 *
 * \sa SDL_JOYSTICK_AXIS_MAX
 */
#define SDL_JOYSTICK_AXIS_MIN   -32768


int SDL_NumJoysticks(void);
const char* SDL_GameControllerNameForIndex(int joystick_index);
SDL_GameControllerType SDL_GameControllerTypeForIndex(int joystick_index);
SDL_bool SDL_IsGameController(int joystick_index);
SDL_GameController* SDL_GameControllerOpen(int joystick_index);
void SDL_GameControllerClose(SDL_GameController* gamecontroller);
SDL_GameControllerButton SDL_GameControllerGetButtonFromString(const char *str);
SDL_GameControllerAxis SDL_GameControllerGetAxisFromString(const char *str);
const char* SDL_GameControllerGetStringForAxis(SDL_GameControllerAxis axis);
const char* SDL_GameControllerGetStringForButton(SDL_GameControllerButton button);