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
 * @brief Implementation of @ref SDLG_keyboard.h.
 */

#include <SDLG_keyboard.h>

static int SDLG_enabled_UNICODE = 0;

int
SDL_EnableKeyRepeat(int delay, int interval)
{
	SDLG_UNUSED_PARAMETER(delay);
	SDLG_UNUSED_PARAMETER(interval);

    return 0;
}

void
SDL_GetKeyRepeat(int *delay, int *interval)
{
    if (delay) {
        *delay = SDL_DEFAULT_REPEAT_DELAY;
    }
    if (interval) {
        *interval = SDL_DEFAULT_REPEAT_INTERVAL;
    }
}

int
SDL_EnableUNICODE(int enable)
{
    int previous = SDLG_enabled_UNICODE;

    switch (enable) {
    case 1:
        SDLG_enabled_UNICODE = 1;
        SDL_StartTextInput();
        break;
    case 0:
        SDLG_enabled_UNICODE = 0;
        SDL_StopTextInput();
        break;
    }
    return previous;
}
