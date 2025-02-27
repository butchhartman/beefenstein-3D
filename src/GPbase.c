// OpenGL Documentation : https://registry.khronos.org/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml

// Much of the following code was directly taken and/or modified from the following sources:
// https://books.google.com/books?id=vUK1DAAAQBAJ
// https://www.glfw.org/docs/latest/quick_guide.html
// https://github.com/skaslev/gl3w

#include "../include/GPbase.h"

//TODO : Define custom error codes?
//TODO : Make functions less of a clusterfuck.


// VAOs hold VBOs
// Taken from : https://www.khronos.org/opengl/wiki/Tutorial2:_VAOs,_VBOs,_Vertex_and_Fragment_Shaders_(C_/_SDL)
/*A Vertex Array Object (VAO) is an object which contains one or more Vertex Buffer Objects and is designed to store 
the information for a complete rendered object.
*/
GLuint VAO;

// VBOs hold vertex data
// Taken from : https://www.khronos.org/opengl/wiki/Tutorial2:_VAOs,_VBOs,_Vertex_and_Fragment_Shaders_(C_/_SDL)
/*A Vertex Buffer Object (VBO) is a memory buffer in the high speed memory of your video card designed to hold 
information about vertices. VBOs can also store information such as normals, 
texcoords, indicies, etc.
*/
GLuint VBO;


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
	static const GLfloat vertices[6][6] = {
		// FORMAT : First three values are clip-space coordinates.
		//			Last three values are RGB values.

		// Triangle 1 vertex and color data.
		{ -0.90f, -0.90f, 1.0f, 1.0f, 0.0f, 0.0f },
		{  0.85f, -0.90f, 1.0f, 0.0f, 1.0f, 0.0f },
		{ -0.90f,  0.85f, 1.0f, 0.0f, 0.0f, 1.0f },

		// Triangle 1 vertex and color data.
		{  0.90f, -0.85f, 1.0f, 1.0f, 0.0f, 0.0f },
		{  0.90f,  0.90f, 1.0f, 0.0f, 1.0f, 0.0f },
		{ -0.85f,  0.90f, 1.0f, 0.0f, 0.0f, 1.0f },
	};

	// Generates a VAO and returns its ID to the second parameter.
	// The second parameter can also be a table.
	glGenVertexArrays(1, &VAO);
	// Binds the VAO, setting it as the one currently in use by OpenGL.
	glBindVertexArray(VAO);

	// Generates a VBO and returns its ID to the second parameter.
	// The second parameter can also be a table.
	glCreateBuffers(1, &VBO);
	// Binds the VBO, setting it as the one currently in use by OpenGL.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Buffers data into the currently bound VBO.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* IMPORTANT : Multi-dimensional arrays are treated the same as one dimensional arrays by glVertexAttribPointer
	 i.e {1.0f, 2.0f, 3.0f}
		 {4.0f, 5.0f, 6.0f}
	 index[0] IS NOT the entire first array
	 index[0] is 1.0f
	 index[4] is 5.0f

     Additionally :
     Stride and offset are BOTH in bytes.
     This means they both should be written as (num of values) * sizeof(value type)
 */

	// Defines the format to use when reading the data from the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Enables the previously defined Vertex Attrib Pointers via their indicies.
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	ShaderInfo shaders[] = {
		{GL_VERTEX_SHADER, "../../src/Shaders/triangles.vert"},
		{GL_FRAGMENT_SHADER, "../../src/Shaders/triangles.frag"},
		{GL_NONE, NULL}
	};
	// Loads shaders via the Red Book's LoadShaders function. Returns a shader program ID
	GLuint program = LoadShaders(shaders);
	// Sets the loaded shader program as the one currently in use.
	glUseProgram(program);
}

void draw() {
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f};
	glClearBufferfv(GL_COLOR, 0, black);

	// Draws using the data found in the VBO.
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
