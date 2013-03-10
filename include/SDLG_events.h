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
 * @brief Contains the emulation for SDL_events.h.
 *
 * A few events no longer exist in SDL 2.0, they're emulated here. It also
 * contains a function to be used with SDL_SetEventFilter.
 */

#ifndef SDLG_EVENTS_H_INCLUDED
#define SDLG_EVENTS_H_INCLUDED

#include <SDL_version.h>

#if SDL_VERSION_ATLEAST(2,0,0)

#include <SDLG_stdinc.h>

#include <SDL_events.h>

#include "begin_code.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * A function which can be used as event filter.
 *
 * The function is intended to be used in combination with SDL_SetEventFilter.
 * When called it transforms some of the SDL 2.0 style events to their SDL 1.2
 * version.
 *
 * @param userdata                Unused.
 * @param event                   The SDL 2.0 event.
 *
 * @returns                       Fixed at @c 1.
 */
extern DECLSPEC int SDLCALL SDLG_EventFilter(void *userdata, SDL_Event * event);

#define SDL_EVENTMASK(event) event, event

#define SDL_ACTIVEEVENT      1
#define SDL_VIDEORESIZE      16
#define SDL_VIDEOEXPOSE      17

#define SDL_APPMOUSEFOCUS    0x01
#define SDL_APPINPUTFOCUS    0x02
#define SDL_APPACTIVE        0x04

typedef struct SDL_ActiveEvent {
	Uint32 type;        /**< SDL_ACTIVEEVENT */
	Uint8 gain;         /**< Whether given states were gained or lost (1/0) */
	Uint8 state;        /**< A mask of the focus states */
} SDL_ActiveEvent;

typedef struct SDL_ResizeEvent {
	Uint32 type;        /**< SDL_VIDEORESIZE */
	int w;              /**< New width */
	int h;              /**< New height */
} SDL_ResizeEvent;

#define SDL_BUTTON_WHEELUP   4
#define SDL_BUTTON_WHEELDOWN 5

#ifdef __cplusplus
}
#endif
#include "close_code.h"

#endif
#endif
