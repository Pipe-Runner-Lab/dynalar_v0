#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

class WindowManager
{
private:
	GLFWwindow* m_window_ptr = nullptr;
public:
	WindowManager(int width, int height);
	~WindowManager();
	inline GLFWwindow* GetWindowPtr() {
		return m_window_ptr;
	};
	inline int ShouldWindowClose() { return glfwWindowShouldClose(m_window_ptr); }
};

