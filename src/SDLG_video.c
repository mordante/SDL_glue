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
static char* SDLG_window_title = NULL;
static SDL_Surface* SDLG_window_icon = NULL;

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

static int
GetVideoDisplay()
{
	return 0;
}

int
SDL_VideoModeOK(int width, int height, int bpp, Uint32 flags)
{
	int i, actual_bpp = 0;

	if (!(flags & SDL_FULLSCREEN)) {
		SDL_DisplayMode mode;
		SDL_GetDesktopDisplayMode(GetVideoDisplay(), &mode);
		return SDL_BITSPERPIXEL(mode.format);
	}

	for (i = 0; i < SDL_GetNumDisplayModes(GetVideoDisplay()); ++i) {
		SDL_DisplayMode mode;
		SDL_GetDisplayMode(GetVideoDisplay(), i, &mode);
		if (!mode.w || !mode.h || (width == mode.w && height == mode.h)) {
			if (!mode.format) {
				return bpp;
			}
			if (SDL_BITSPERPIXEL(mode.format) >= (Uint32) bpp) {
				actual_bpp = SDL_BITSPERPIXEL(mode.format);
			}
		}
	}
	return actual_bpp;
}

SDL_Surface *
SDL_SetVideoMode(int width, int height, int bpp, Uint32 flags)
{
	const char* title = SDLG_window_title;

	SDLG_UNUSED_PARAMETER(bpp);

	if(SDLG_window) {
		SDL_DestroyWindow(SDLG_window);
		SDLG_surface = NULL;
		SDLG_window = NULL;
	}

	if(SDLG_renderer) {
		SDL_DestroyRenderer(SDLG_renderer);
		SDLG_renderer = NULL;
	}

	if(!title) {
		title = "";
	}

	SDLG_window = SDL_CreateWindow(
			  title
			, SDL_WINDOWPOS_UNDEFINED
			, SDL_WINDOWPOS_UNDEFINED
			, width
			, height
			, SDL_WINDOW_SHOWN | flags);

	if(!SDLG_window) {
		return NULL;
	}

	if(SDLG_window_icon) {
		SDL_SetWindowIcon(SDLG_window, SDLG_window_icon);
	}

	SDLG_renderer = SDL_CreateRenderer(SDLG_window, -1 , 0);
	SDLG_surface = SDL_GetWindowSurface(SDLG_window);

	return SDLG_surface;
}

DECLSPEC void SDLCALL SDL_WM_SetCaption(const char *title, const char *icon)
{
	SDLG_UNUSED_PARAMETER(icon);

	if(SDLG_window_title) {
		SDL_free(SDLG_window_title);
		SDLG_window_title = NULL;
	}

	if(title) {
		SDLG_window_title = SDL_strdup(title);
	}

	if(title) {
		SDL_SetWindowTitle(SDLG_window, title);
	} else {
		SDL_SetWindowTitle(SDLG_window, "");
	}
}

DECLSPEC void SDLCALL SDL_WM_GetCaption(char **title, char **icon)
{
	*title = SDLG_window_title;
	*icon = NULL;
}

DECLSPEC void SDLCALL SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask)
{
	SDLG_UNUSED_PARAMETER(mask);

	if(SDLG_window_icon) {
		SDL_FreeSurface(SDLG_window_icon);
		SDLG_window_icon = NULL;
	}

	if(icon) {
		SDLG_window_icon = SDL_ConvertSurface(icon, icon->format, icon->flags);
	}

	if(SDLG_window && icon) {
		SDL_SetWindowIcon(SDLG_window, icon);
	}
}
