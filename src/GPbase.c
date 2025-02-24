// GPbase.cpp : Defines the entry point for the application.
//

// Much of the following code was directly taken and/or modified from the following sources:
// https://books.google.com/books?id=vUK1DAAAQBAJ
// https://www.glfw.org/docs/latest/quick_guide.html
// https://github.com/skaslev/gl3w

// TODO : Read & comprehend explanation of code from red book. Also comment so I don't lose my understanding

#include "../include/GPbase.h"

//TODO : Define custom error codes?
//TODO : Make functions less of a clusterfuck.


// TODO : Replace these
enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDS { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

GLdouble lastTime;

// Simple glfw error callback.
// Taken from : https://www.glfw.org/docs/latest/quick_guide.html
void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}

// Input callback
// Taken from : https://www.glfw.org/docs/latest/quick_guide.html
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		printf("\nUser requesting closure of application.");
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

// Function called when the window is resized
// Taken from : https://www.glfw.org/docs/3.3/window_guide.html
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// lol
GLFWwindow* createGlWindowAndMakeContextCurrent() {
	if (!glfwInit()) {
		fprintf(stderr, "\nWARNING : glfw initialization failed.");
		return; // TODO : Replace with a custom error code that means something?
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
	GLFWwindow* window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "GPbase", NULL, NULL);
	if (!window) {
		fprintf(stderr, "\nWARNING : glfw window creation failed.");
		return; // TODO : Replace with a custom error code that means something?
	}

	// Sets the key press callback.
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// Make the window context current.
	glfwMakeContextCurrent(window);

	lastTime = glfwGetTime();

	return window;
}

void initBuffers() {
	// TODO : This next.
	static const GLfloat vertices[6][2] = {
		{ -0.90f, -0.90f }, // t1
		{  0.85f, -0.90f },
		{ -0.90f,  0.85f },
		{  0.90f, -0.85f }, // t2
		{  0.90f,  0.90f },
		{ -0.85f,  0.90f }
	};

	glCreateBuffers(NumBuffers, Buffers);
	glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices), vertices, 0);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "../../src/Shaders/triangles.vert"},
		{GL_FRAGMENT_SHADER, "../../src/Shaders/triangles.frag"},
		{GL_NONE, NULL}
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, 
						  GL_FALSE, 0, (void*)(0));
	glEnableVertexAttribArray(vPosition);
}

void draw() {
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f};
	glClearBufferfv(GL_COLOR, 0, black);

	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main()
{
	printf("Application begin.");

	GLFWwindow* window = createGlWindowAndMakeContextCurrent();

	// Load OpenGL extensions via gl3w
	// Excerpt from : https://github.com/skaslev/gl3w
	// Returns 0 when gl3w was initialized successfully, non-zero if there was an error.
	if (gl3wInit()) {
		fprintf(stderr, "\nWARNING : OpenGL extension loading failed.");
		return 1; // TODO : Replace with a custom error code that means something?
	}
	
	initBuffers();


	// TODO : Figure out way to stop this from producing GPU-melting number of frames
	// Main loop which draws, updates, and polls events from the window. This must exist for the window to function
	while (!glfwWindowShouldClose(window)) {
		//GLdouble elapsedTime = glfwGetTime() - lastTime;
		//lastTime = glfwGetTime();
		//printf("\nTime Since Last Frame: %.8f", elapsedTime);

		draw();
		// Swaps the display buffers of glfw. In other words, updates what's on screen.
		glfwSwapBuffers(window);
		// Processes events. Needed or else the window will be shown as not responding.
		glfwPollEvents();
	}

	// Window destruction must occur manually after is has been flagged that it should close.
	glfwDestroyWindow(window);

	// Frees all resources used by glfw.
	glfwTerminate();
	printf("\nTerminated glfw.");

	return 0;
}
