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
 * @brief Implementation of @ref SDLG_video.h.
 */

#include <SDLG_video.h>

static SDL_Surface* SDLG_surface = NULL;
static SDL_Window* SDLG_window = NULL;
static SDL_Renderer* SDLG_renderer = NULL;

SDL_Surface *
SDL_GetVideoSurface(void)
{
    return SDLG_surface;
}

SDL_Window *
SDLG_GetVideoWindow(void)
{
    return SDLG_window;
}

SDL_Renderer *
SDLG_GetVideoRenderer(void)
{
    return SDLG_renderer;
}
