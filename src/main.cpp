#include <iostream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "engine/engine.h"

const GLint WIDTH = 800, HEIGHT = 600;

int main() {
	GLFWwindow* mainWindow;

	/* Initialize the library */
	if (!glfwInit()) {
		std::cout << "GLFW initialization failed" << std::endl;
		return -1;
	}

	/* Setup GLFW window property */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Set major version to 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Set minor version to 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set profile to core
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Set forward compatibility to true

	/* Create a windowed mode window and its OpenGL context */
	mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Dynalar V0", NULL, NULL);
	if (!mainWindow)
	{
		std::cout << "GLFW failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight); // get actual sizes of the created window

	/* Make the window's context current */
	glfwMakeContextCurrent(mainWindow); // tells openGL which window to use

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	/* Initialize GLEW */
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "GLEW initialization failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Setup viewport size */
	glViewport(0, 0, bufferWidth, bufferHeight);

	Triangle triangle;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(mainWindow))
	{
		/* Check for user events */
		glfwPollEvents();

		/* Render here */
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		triangle.draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(mainWindow);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}