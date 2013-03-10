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
 * @brief Implementation of @ref SDLG_events.h.
 */

#include <SDLG_events.h>

#include <SDLG_video.h>

int SDLG_EventFilter(void *userdata, SDL_Event * event)
{
    SDL_Event fake;
	SDL_ActiveEvent active;
	SDL_ResizeEvent resize;

	SDLG_UNUSED_PARAMETER(userdata);

    switch (event->type) {
    case SDL_WINDOWEVENT:
        switch (event->window.event) {
        case SDL_WINDOWEVENT_EXPOSED:
            if (!SDL_HasEvent(SDL_VIDEOEXPOSE)) {
                fake.type = SDL_VIDEOEXPOSE;
                SDL_PushEvent(&fake);
            }
            break;
        case SDL_WINDOWEVENT_RESIZED:
            SDL_FlushEvent(SDL_VIDEORESIZE);
            /* We don't want to expose that the window width and height will
               be different if we don't get the desired fullscreen mode.
            */
            if (SDLG_GetVideoWindow()
					&& !(SDL_GetWindowFlags(SDLG_GetVideoWindow())
						& SDL_WINDOW_FULLSCREEN)) {

                resize.type = SDL_VIDEORESIZE;
                resize.w = event->window.data1;
                resize.h = event->window.data2;
                SDL_PushEvent((SDL_Event*)&resize);
            }
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            active.type = SDL_ACTIVEEVENT;
            active.gain = 0;
            active.state = SDL_APPACTIVE;
            SDL_PushEvent((SDL_Event*)&active);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            active.type = SDL_ACTIVEEVENT;
            active.gain = 1;
            active.state = SDL_APPACTIVE;
            SDL_PushEvent((SDL_Event*)&active);
            break;
        case SDL_WINDOWEVENT_ENTER:
            active.type = SDL_ACTIVEEVENT;
          active.gain = 1;
            active.state = SDL_APPMOUSEFOCUS;
            SDL_PushEvent((SDL_Event*)&active);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            active.type = SDL_ACTIVEEVENT;
            active.gain = 0;
            active.state = SDL_APPMOUSEFOCUS;
            SDL_PushEvent((SDL_Event*)&active);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            active.type = SDL_ACTIVEEVENT;
            active.gain = 1;
            active.state = SDL_APPINPUTFOCUS;
            SDL_PushEvent((SDL_Event*)&active);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            active.type = SDL_ACTIVEEVENT;
            active.gain = 0;
            active.state = SDL_APPINPUTFOCUS;
            SDL_PushEvent((SDL_Event*)&active);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            fake.type = SDL_QUIT;
            SDL_PushEvent(&fake);
            break;
        }
    case SDL_KEYDOWN:
    case SDL_KEYUP:
        {
            Uint32 unicode = 0;
            if (event->key.type == SDL_KEYDOWN && event->key.keysym.sym < 256) {
                unicode = event->key.keysym.sym;
                if (unicode >= 'a' && unicode <= 'z') {
                    int shifted = !!(event->key.keysym.mod & KMOD_SHIFT);
                    int capslock = !!(event->key.keysym.mod & KMOD_CAPS);
                    if ((shifted ^ capslock) != 0) {
                        unicode = SDL_toupper(unicode);
                    }
                }
            }
            if (unicode) {
                event->key.keysym.unicode = unicode;
            }
            break;
        }
    case SDL_TEXTINPUT:
        {
            /* FIXME: Generate an old style key repeat event if needed */
            //printf("TEXTINPUT: '%s'\n", event->text.text);
            break;
        }
    case SDL_MOUSEMOTION:
        {
//            event->motion.x -= SDL_VideoViewport.x;
//            event->motion.y -= SDL_VideoViewport.y;
            break;
        }
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        {
//            event->button.x -= SDL_VideoViewport.x;
//            event->button.y -= SDL_VideoViewport.y;
            break;
        }
    case SDL_MOUSEWHEEL:
        {
            Uint8 button;
            int x, y;

            if (event->wheel.y == 0) {
                break;
            }

            SDL_GetMouseState(&x, &y);

            if (event->wheel.y > 0) {
                button = SDL_BUTTON_WHEELUP;
            } else {
                button = SDL_BUTTON_WHEELDOWN;
            }

            fake.button.button = button;
            fake.button.x = x;
            fake.button.y = y;
            fake.button.windowID = event->wheel.windowID;

            fake.type = SDL_MOUSEBUTTONDOWN;
            fake.button.state = SDL_PRESSED;
            SDL_PushEvent(&fake);

            fake.type = SDL_MOUSEBUTTONUP;
            fake.button.state = SDL_RELEASED;
            SDL_PushEvent(&fake);
            break;
        }

    }
    return 1;
}
