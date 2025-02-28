#include "../include/CallbackFunctions.h"


void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		printf("\nUser requesting closure of application.");
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}