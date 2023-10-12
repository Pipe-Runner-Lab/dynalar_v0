#include "WindowManager.h"
#include <iostream>
#include <algorithm>


WindowManager::WindowManager(int width, int height) :
	m_lastX(0),
	m_lastY(0),
	m_deltaX(0),
	m_deltaY(0),
	mouse_initialized(false),
	is_camera_control_active(false)
{
	std::fill(m_keys.begin(), m_keys.end(), false);

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

	glfwSetWindowUserPointer(m_window_ptr, (void*)this);

	/* Set key callbacks */
	glfwSetKeyCallback(m_window_ptr, HandleKeys);
	glfwSetCursorPosCallback(m_window_ptr, HandleMouse);
}

WindowManager::~WindowManager()
{
	glfwDestroyWindow(m_window_ptr);
	glfwTerminate();
}

void WindowManager::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	WindowManager* windowManager = (WindowManager*)glfwGetWindowUserPointer(window);

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
	}

	/* Camera control toggle is done by pressing 'M' */
	if (key == GLFW_KEY_M) {
		if (windowManager->is_camera_control_active) {
			windowManager->is_camera_control_active = false;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else {
			windowManager->is_camera_control_active = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		return;
	}

	if (KEYCODE_LOWER_LIMIT < key && key < KEYCODE_UPPER_LIMIT) {
		if (action == GLFW_PRESS) {
			windowManager->GetKey(key) = true;
		}

		if (action == GLFW_RELEASE) {
			windowManager->GetKey(key) = false;
		}
	}
}

void WindowManager::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
	WindowManager* windowManager = (WindowManager*)glfwGetWindowUserPointer(window);

	if (!windowManager->is_camera_control_active) return;

	// check initial movement, to avoid jerky start
	if (windowManager->mouse_initialized) {
		windowManager->m_deltaX = xPos - windowManager->m_lastX;
		windowManager->m_deltaX = xPos - windowManager->m_lastX;

	}

	windowManager->m_lastX = xPos;
	windowManager->m_lastY = yPos;
	windowManager->mouse_initialized = true;
}
