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
 * @brief Contains the emulation for SDL_video.h.
 *
 * Where SDL 1.2 just had one display surface SDL 2.0 can have multiple. The
 * emulation uses one static surface, which can be retrieved with the SDL 1.2
 * emulation function @ref SDL_GetVideoSurface. Since SDL 2.0 also has windows
 * and renderers a static one is provided as well. These can be retrieved with
 * @ref SDLG_GetVideoWindow and @ref SDLG_GetVideoRenderer respectively.
 */

#ifndef SDLG_VIDEO_H_INCLUDED
#define SDLG_VIDEO_H_INCLUDED

#include <SDL_version.h>

#if SDL_VERSION_ATLEAST(2,0,0)

#include <SDLG_stdinc.h>

#include <SDL_render.h>
#include <SDL_video.h>

#include "begin_code.h"
#ifdef __cplusplus
extern "C" {
#endif

/** Emulation for SDL_GetVideoSurface. */
extern DECLSPEC SDL_Surface *SDLCALL SDL_GetVideoSurface(void);

/**
 * Returns the current display window.
 *
 * @returns                       The current display window.
 */
extern DECLSPEC SDL_Window *SDLCALL SDLG_GetVideoWindow(void);

/**
 * Returns the current display window's renderer.
 *
 * @returns                       The current display window's renderer.
 */
extern DECLSPEC SDL_Renderer *SDLCALL SDLG_GetVideoRenderer(void);

/* SDL 1.2 compatibility flags */
#define SDL_HWSURFACE       SDLG_UNUSED_FLAG
#define SDL_ANYFORMAT       SDLG_UNUSED_FLAG
#define SDL_HWPALETTE       SDLG_UNUSED_FLAG
#define SDL_DOUBLEBUF       SDLG_UNUSED_FLAG
#define SDL_FULLSCREEN      SDL_WINDOW_FULLSCREEN
#define SDL_OPENGL          SDL_WINDOW_OPENGL
#define SDL_OPENGLBLIT      SDL_WINDOW_OPENGL
#define SDL_RESIZABLE       SDL_WINDOW_RESIZABLE
#define SDL_NOFRAME         SDL_WINDOW_BORDERLESS

/**
 * Emulation for SDL_VideoModeOK.
 *
 * @param width                   The wanted width.
 * @param height                  The wanted height.
 * @param bpp                     The wanted bits per pixel.
 * @param flags                   The flags for the video mode to test.
 *
 * @returns                       The bits per pixel in which the wanted mode
 *                                is available.
 * @retval 0                      The wanted mode is not available.
 */
extern DECLSPEC int SDLCALL SDL_VideoModeOK(int width,
                                            int height,
                                            int bpp, Uint32 flags);

/**
 * Emulation for SDL_SetVideoMode.
 *
 * This function initialises the display surface, like in SDL 1.2, and also the
 * window and the renderer.
 *
 * @param width                   The width for the video mode.
 * @param height                  The height for the video mode.
 * @param bpp                     Unused.
 * @param flags                   The flags for the video mode.
 *
 * @returns                       The created video surface. The pointer can
 *                                later also be retrieved with
 *                                @ref SDL_GetVideoSurface.
 * @retval NULL                   Upon error.
 */
extern DECLSPEC SDL_Surface *SDLCALL SDL_SetVideoMode(int width, int height,
                                                      int bpp, Uint32 flags);

/**
 * Emulation for SDL_WM_SetCaption.
 *
 * @param title                   The title of the window.
 * @param icon                    Unused.
 */
extern DECLSPEC void SDLCALL SDL_WM_SetCaption(
		  const char *title
		, const char *icon);

/**
 * Emulation for SDL_WM_GetCaption.
 *
 * @param [out] title             The title of the window.
 * @param [out] icon              Unused, @c NULL.
 */
extern DECLSPEC void SDLCALL SDL_WM_GetCaption(char **title, char **icon);

/**
 * Emulation for SDL_WM_SetIcon.
 *
 * @param icon                    The icon to use as window icon.
 * @param mask                    Unused.
 */
extern DECLSPEC void SDLCALL SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask);

#ifdef __cplusplus
}
#endif
#include "close_code.h"

#endif
#endif
