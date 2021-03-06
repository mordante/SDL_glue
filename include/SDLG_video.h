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

/*
 * SDL 1.2 compatibility flags
 *
 * Note they are not mapped to the SDL 2.0 flags directly, but use their own
 * values. This due to the face that SDL_SetVideoMode can take both flags for
 * SDL_CreateWindow and SDL_CreateRenderer.
 */
#define SDL_HWSURFACE      0x00000001 /**< Mapped to SDL_RENDERER_ACCELERATED */
#define SDL_ANYFORMAT      SDLG_UNUSED_FLAG
#define SDL_HWPALETTE      SDLG_UNUSED_FLAG
#define SDL_DOUBLEBUF      SDLG_UNUSED_FLAG
#define SDL_FULLSCREEN     0x00000010 /**< Mapped to SDL_WINDOW_FULLSCREEN */
#define SDL_OPENGL         0x00000020 /**< Mapped to SDL_WINDOW_OPENGL */
#define SDL_OPENGLBLIT     0x00000040 /**< Mapped to SDL_WINDOW_OPENGL */
#define SDL_RESIZABLE      0x00000080 /**< Mapped to SDL_WINDOW_RESIZABLE */
#define SDL_NOFRAME        0x00000100 /**< Mapped to SDL_WINDOW_BORDERLESS */

/**
 * This flag disables the registration of the event filter.
 *
 * By default when no event filter is set, @ref SDL_SetVideoMode sets @ref
 * SDLG_EventFilter as filter. This flag suppresses that behaviour.
 *
 * Since setting the compatibility filter is probably wanted, that has been
 * made the default, allowing to use the SDL 1.2 flags to get the wanted
 * behaviour in SDL 2.0.
 */
#define SDLG_NOEVENT       0x00001000

/**
 * Emulation for SDL_VideoModeOK.
 *
 * @param width                   The wanted width.
 * @param height                  The wanted height.
 * @param bpp                     The wanted bits per pixel.
 * @param flags                   The flags for the video mode to test. The
 *                                flags that are used by the function are:
 *                                - @ref SDL_FULLSCREEN
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
 * @param flags                   The flags for the video mode. The
 *                                flags that are used by the function are to
 *                                create the window are:
 *                                - @ref SDL_FULLSCREEN
 *                                - @ref SDL_OPENGL
 *                                - @ref SDL_OPENGLBLIT
 *                                - @ref SDL_RESIZABLE
 *                                - @ref SDL_NOFRAME
 *                                The flags that are used by the function are
 *                                to create the renderer are:
 *                                - @ref SDL_HWSURFACE
 *                                The SDLG flags that are used by the function
 *                                are:
 *                                - @ref SDLG_NOEVENT
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
 * @param [out] icon              Unused, set to @c NULL.
 */
extern DECLSPEC void SDLCALL SDL_WM_GetCaption(char **title, char **icon);

/**
 * Emulation for SDL_WM_SetIcon.
 *
 * @param icon                    The icon to use as window icon.
 * @param mask                    Unused.
 */
extern DECLSPEC void SDLCALL SDL_WM_SetIcon(SDL_Surface *icon, Uint8 *mask);

/**
 * Emulation for SDL_Flip.
 *
 * @note Instead of selecting the screen buffer to swap the one provided by
 * @ref SDL_GetVideoSurface is flipped. Proper flipping might be implemented
 * later.
 *
 * @param screen                  Unused.
 *
 * @returns                       Fixed at @c 0.
 */
extern DECLSPEC int SDLCALL SDL_Flip(SDL_Surface * screen);

/**
 * Emulation for SDL_UpdateRect.
 *
 * @note Instead of selecting the screen buffer to update the one provided by
 * @ref SDL_GetVideoSurface is updated. Proper updating might be implemented
 * later.
 *
 * @param screen                  Unused.
 * @param x                       The x-coordinate of the area to update.
 * @param y                       The y-coordinate of the area to update.
 * @param w                       The width of the area to update.
 * @param h                       The height of the area to update.
 */
extern DECLSPEC void SDLCALL SDL_UpdateRect(SDL_Surface * screen,
                                            Sint32 x,
                                            Sint32 y, Uint32 w, Uint32 h);

/**
 * Emulation for SDL_UpdateRects.
 *
 * @note Instead of selecting the screen buffer to update the one provided by
 * @ref SDL_GetVideoSurface is updated. Proper updating might be implemented
 * later.
 *
 * @param screen                  Unused.
 * @param numrects                The number of areas to update.
 * @param rects                   Pointer to array of @p numrects rectangles
 *                                containing the area to update.
 */
extern DECLSPEC void SDLCALL SDL_UpdateRects(SDL_Surface * screen,
                                             int numrects, SDL_Rect * rects);

/**
 * Emulation for SDL_GetAppState.
 *
 * @note In SDL 1.2 this was in the SDL_active.h header. In SDL 2.0 the code
 * used is in SDL_video.h. So added to the existing header instead of adding a
 * new one.
 *
 * @returns                       The application state flags. Any of the
 *                                following flags might be set:
 *                                - SDL_APPACTIVE
 *                                - SDL_APPINPUTFOCUS
 *                                - SDL_APPMOUSEFOCUS
 */
extern DECLSPEC Uint8 SDLCALL SDL_GetAppState(void);

/* SDL 1.2 compatibility flags */
#define SDL_LOGPAL SDLG_UNUSED_FLAG
#define SDL_PHYSPAL SDLG_UNUSED_FLAG

/**
 * Emulation for SDL_SetPalette.
 *
 * @param surface                 The surface whose palette to modify.
 * @param flags                   Unused.
 * @param colors                  An array with new colors to use.
 * @param firstcolor              The first color to change.
 * @param ncolors                 The number of colors to modify.
 *
 * @returns                       Status; 0 upon success a negative value when
 *                                an error occurred.
 */
extern DECLSPEC int SDLCALL SDL_SetPalette(SDL_Surface * surface,
                                           int flags,
                                           const SDL_Color * colors,
                                           int firstcolor, int ncolors);

/**
 * Emulation for SDL_SetColors.
 *
 * @param surface                 The surface whose color palette to modify.
 * @param colors                  An array with new colors to use.
 * @param firstcolor              The first color to change.
 * @param ncolors                 The number of colors to modify.
 *
 * @returns                       Status; 0 upon success a negative value when
 *                                an error occurred.
 */
extern DECLSPEC int SDLCALL SDL_SetColors(SDL_Surface * surface,
                                          const SDL_Color * colors,
                                          int firstcolor, int ncolors);
#ifdef __cplusplus
}
#endif
#include "close_code.h"

#endif
#endif
