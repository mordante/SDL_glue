### Include directories

include_directories(${SDL_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/include/)


### Targets

add_library(SDLG SHARED
	SDLG_stdinc.c
	SDLG_events.c
	SDLG_keyboard.c
	SDLG_video.c
)

set_target_properties(SDLG
	PROPERTIES
		VERSION "0.0.1"
		SOVERSION "0"
		DEFINE_SYMBOL BUILD_SDL
)

target_link_libraries(SDLG
	${SDL_LIBRARY}
)
