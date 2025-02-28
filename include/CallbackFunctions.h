#pragma once

#include <stdio.h>
#include "GL3W/GL/gl3w.h"
#include "GLFW/glfw3.h"

// Simple glfw error callback.
// Taken from : https://www.glfw.org/docs/latest/quick_guide.html
void error_callback(int error, const char* description);

// Input callback
// Taken from : https://www.glfw.org/docs/latest/quick_guide.html
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// Function called when the window is resized
// Taken from : https://www.glfw.org/docs/3.3/window_guide.html
void framebuffer_size_callback(GLFWwindow* window, int width, int height);