### Header
cmake_minimum_required(VERSION 2.6.0)
project(SDL_glue C)


### Dependencies

# Note the version check doesn't seem to work.
find_package(SDL 2.0.0 REQUIRED)

# Based in cmake/FindSDL.cmake from CMake 2.8.10
if(SDL_INCLUDE_DIR AND EXISTS "${SDL_INCLUDE_DIR}/SDL_version.h")
	file(STRINGS "${SDL_INCLUDE_DIR}/SDL_version.h" SDL_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SDL_MAJOR_VERSION[ \t]+[0-9]+$")
	string(REGEX REPLACE "^#define[ \t]+SDL_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SDL_VERSION_MAJOR "${SDL_VERSION_MAJOR_LINE}")
	if("${SDL_VERSION_MAJOR}" LESS "2")
		message(FATAL_ERROR "SDL version 2.0.0 is required.")
	endif()
	unset(SDL_VERSION_MAJOR_LINE)
	unset(SDL_MAJOR_VERSION)
else()
	message("Can't verify SDL version number, make sure it is at least version 2.0.0.")
endif()

