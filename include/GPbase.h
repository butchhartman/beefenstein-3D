// GPbase.h : Include file for standard system include files,
// or project specific include files.

#pragma once
// Ensures GLFW won't include the development environment header. This prevents conflicts upon inclusion of gl3w .
#define GLFW_INCLUDE_NONE

#include <stdio.h>

// OpenGL Extension loading library. 
#include "GL3W/GL/gl3w.h"

// Window creation library. Also handles other things like input.
#include "GLFW/glfw3.h"

