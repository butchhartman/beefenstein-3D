// GPbase.cpp : Defines the entry point for the application.
//

#include "../include/GPbase.h"

//TODO : Define custom error codes.

#define OPENGL_VERSION_MAJOR 4
#define OPENGL_VERSION_MINOR 6

//Simple glfw error callback.
//Taken from : https://www.glfw.org/docs/latest/quick_guide.html
void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

//Input callback
// Taken from : https://www.glfw.org/docs/latest/quick_guide.html
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
	printf("Hello, CMake!");
	// Initalizing glfw :
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (!glfwInit()) {
		fprintf(stderr, "\nWARNING : glfw initialization failed.");
		return 1; // TODO : Replace with a custom error code that means something.
	}
	
	printf("\nSuccessfully initialized glfw.");
	
	// Sets the error callback AKA the function to run when there is an error.
	glfwSetErrorCallback(error_callback);


	// Specify the version and profile of OpenGL to target before window creation.
	// LATEST OPENGL VERSION : 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Window creation.
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello, glfw!", NULL, NULL);
	if (!window) {
		fprintf(stderr, "\nWARNING : glfw window creation failed.");
		return 1; // TODO : Replace with a custom error code that means something.
	}

	// Sets the key press callback.
	glfwSetKeyCallback(window, key_callback);

	// Make the window context current.
	glfwMakeContextCurrent(window);

	// End glfw initialization.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	// Initialize gl3w.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	// Would be nice to have this check but unfortunately it is not functioning correctly
	//if (gl3wIsSupported(4, 6) == 1) {
	//	fprintf(stderr, "\nWARNING : OpenGl version not supported");
	//	return 1;
	//}*/

	// Load OpenGL extensions via gl3w
	// Excerpt from : https://github.com/skaslev/gl3w
	// Returns 0 when gl3w was initialized successfully, non-zero if there was an error.
	if (gl3wInit()) {
		fprintf(stderr, "\nWARNING : OpenGL extension loading failed.");
		return 1; // TODO : Replace with a custom error code that means something.
	}

	//End gl3w initialization
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	


	// Run window loop
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	while (!glfwWindowShouldClose(window)) {
		// Processes events. Needed or else the window will be shown as not responding.
		glfwPollEvents();
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	glfwTerminate();
	printf("\nTerminated glfw.");
	return 0;
}
