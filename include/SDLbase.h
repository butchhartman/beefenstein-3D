// GPbase.h : Include file for standard system include files,
// or project specific include files.

#pragma once
// Ensures GLFW won't include the development environment header. This prevents conflicts upon inclusion of gl3w .
#define SDL_MAIN_USE_CALLBACKS 1 // uses callbacks instead of the main as an entry point

#include <stdio.h>

// Window creation library. Also handles other things like input and audio.
#include "../vendored/SDL3/include/SDL3/SDL.h"
#include "../vendored/SDL3/include/SDL3/SDL_main.h"



#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

 