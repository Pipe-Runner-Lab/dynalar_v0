#include "WindowManager.h"
#include <iostream>

WindowManager::WindowManager(int width, int height)
{
	/* Initialize GLFW library */
	if (!glfwInit()) {
		std::cout << "GLFW initialization failed" << std::endl;
		throw;
	}

	/* Setup GLFW window property */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Set major version to 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Set minor version to 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Set profile to core
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Set forward compatibility to true

	/* Create a windowed mode window and its OpenGL context */
	m_window_ptr = glfwCreateWindow(width, height, "Dynalar V0", NULL, NULL);

	if (!m_window_ptr)
	{
		std::cout << "GLFW failed to create window" << std::endl;
		glfwTerminate();
		throw;
	}

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(m_window_ptr, &bufferWidth, &bufferHeight); // get actual sizes of the created window

	/* Make the window's context current */
	glfwMakeContextCurrent(m_window_ptr); // tells openGL which window to use

	/* Enable vsync : Sync render loop to monitor refresh rate */
	glfwSwapInterval(1);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	/* Initialize GLEW */
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "GLEW initialization failed" << std::endl;
		glfwTerminate();
		throw;
	}

	/* Enable depth test */
	glEnable(GL_DEPTH_TEST);

	/* Enable blending, set blending function and equation */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_ADD);

	/* Setup viewport size */
	glViewport(0, 0, bufferWidth, bufferHeight);
}

WindowManager::~WindowManager()
{
	glfwDestroyWindow(m_window_ptr);
	glfwTerminate();
}
