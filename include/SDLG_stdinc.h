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
 * @brief Contains the emulation for SDL_stdinc.h.
 *
 * Also contains some standard includes for the SDLG library.
 */

#ifndef SDLG_STDINC_H_INCLUDED
#define SDLG_STDINC_H_INCLUDED

#include <SDL_version.h>

#if SDL_VERSION_ATLEAST(2,0,0)

#include "begin_code.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Emulation for SDL_putenv.
 *
 * A call to this function like
 * @code SDL_putenv("foo=bar"); @endcode
 * can be replaced with
 * @code  SDL_setenv("foo", "bar", 1); @endcode.
 * This avoids using this fall-back function.
 */
extern DECLSPEC int SDLCALL SDL_putenv(const char *variable);

#ifdef __cplusplus
}
#endif
#include "close_code.h"

#endif
#endif
