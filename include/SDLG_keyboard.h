/*
	Copyright (C) 2013 by Mark de Wever <koraq@xs4all.nl>
	Part of the SDL glue library

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

	Parts of the sofware are based on the Simple DirectMedia Layer.
	Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>

	See the COPYING file for more details.
*/

/**
 * @file
 * @brief Contains the emulation for SDL_keyboard.h.
 */

#ifndef SDLG_KEYBOARD_H_INCLUDED
#define SDLG_KEYBOARD_H_INCLUDED

#include <SDL_version.h>

#if SDL_VERSION_ATLEAST(2,0,0)

#include <SDLG_stdinc.h>

#include <SDL_keyboard.h>

#include "begin_code.h"
#ifdef __cplusplus
extern "C" {
#endif

/** Emulate the renaming of the struct SDLKey. */
#define SDLKey SDL_Keycode

/** Emulate the renaming of the struct SDLMod. */
#define SDLMod SDL_Keymod


/**
 * Emulate the renaming of the function SDL_GetKeyState.
 *
 * @warning The returned array is indexed by SDL_Scancode in SDL 2.0 and by
 * SDLKey in SDL 1.2. SDL_GetScancodeFromKey can be used to convert the SDLKey
 * to a SDL_Scancode.
 */
#define SDL_GetKeyState SDL_GetKeyboardState


/**
 *  \name Obsolete or renamed key codes
 */
/*@{*/

#define SDL_keysym		SDL_Keysym
#define SDL_KeySym		SDL_Keysym
#define SDL_scancode	SDL_Scancode
#define SDL_ScanCode	SDL_Scancode
#define SDLKey          SDL_Keycode
#define SDLMod          SDL_Keymod

/**
 *  \name Renamed keys
 *
 *  These key constants were renamed for clarity or consistency.
 */
/*@{*/
#define SDLK_KP0 SDLK_KP_0
#define SDLK_KP1 SDLK_KP_1
#define SDLK_KP2 SDLK_KP_2
#define SDLK_KP3 SDLK_KP_3
#define SDLK_KP4 SDLK_KP_4
#define SDLK_KP5 SDLK_KP_5
#define SDLK_KP6 SDLK_KP_6
#define SDLK_KP7 SDLK_KP_7
#define SDLK_KP8 SDLK_KP_8
#define SDLK_KP9 SDLK_KP_9
#define SDLK_NUMLOCK SDLK_NUMLOCKCLEAR
#define SDLK_SCROLLOCK SDLK_SCROLLLOCK
#define SDLK_PRINT SDLK_PRINTSCREEN
#define SDLK_LMETA SDLK_LGUI
#define SDLK_RMETA SDLK_RGUI
/*@}*//*Renamed keys*/

/**
 *  \name META modifier
 *
 *  The META modifier is equivalent to the GUI modifier from the USB standard.
 */
/*@{*/
#define KMOD_LMETA KMOD_LGUI
#define KMOD_RMETA KMOD_RGUI
#define KMOD_META KMOD_GUI
/*@}*//*META modifier*/

/**
 *  \name Not in USB
 *
 *  These keys don't appear in the USB specification (or at least not under
 *  those names). I'm unsure if the following assignments make sense or if these
 *  codes should be defined as actual additional SDLK_ constants.
 */
/*@{*/
#define SDLK_LSUPER SDLK_LMETA
#define SDLK_RSUPER SDLK_RMETA
#define SDLK_COMPOSE SDLK_APPLICATION
#define SDLK_BREAK SDLK_STOP
#define SDLK_EURO SDLK_2
/*@}*//*Not in USB*/


/** The SDL_DEFAULT_REPEAT_DELAY value from SDL 1.2. */
#define SDL_DEFAULT_REPEAT_DELAY	500

/** The SDL_DEFAULT_REPEAT_INTERVAL value from SDL 1.2. */
#define SDL_DEFAULT_REPEAT_INTERVAL	30

/**
 * Dummy function for SDL_EnableKeyRepeat.
 *
 * The function is a NOP.
 *
 * @param delay                   Unused.
 * @param interval                Unused.
 */
extern DECLSPEC int SDLCALL SDL_EnableKeyRepeat(int delay, int interval);

/**
 * Dummy function for SDL_GetKeyRepeat.
 *
 * The function is a NOP.
 *
 * @param delay                   Unused, set to @ref SDL_DEFAULT_REPEAT_DELAY.
 * @param interval                Unused, set to
 *                                @ref SDL_DEFAULT_REPEAT_INTERVAL.
 */
extern DECLSPEC void SDLCALL SDL_GetKeyRepeat(int *delay, int *interval);

/**
 * Emulation for SDL_EnableUNICODE.
 *
 * @param enable                 Whether or not to enable the unicode handling.
 *                               - @c 0 disable the handling.
 *                               - @c 1 enable the handling.
 *                               - other values are ingored.
 *
 * @returns                      The enabled state before calling this function.
 */
extern DECLSPEC int SDLCALL SDL_EnableUNICODE(int enable);

#ifdef __cplusplus
}
#endif
#include "close_code.h"

#endif
#endif
