﻿// GPbase.h : Include file for standard system include files,
// or project specific include files.

#pragma once
// Ensures GLFW won't include the development environment header. This prevents conflicts upon inclusion of gl3w .
#define SDL_MAIN_USE_CALLBACKS 1 // uses callbacks instead of the main as an entry point
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>
// Window creation library. Also handles other things like input and audio.
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"

#include "FrameRate.h"
#include "BeefPlayer.h"
#include "Raycast.h"

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

extern int worldMap[24][24];


 