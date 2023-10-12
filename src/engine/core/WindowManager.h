#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <array>

struct MouseDelta {
	double deltaX;
	double deltaY;
};

class WindowManager
{
private:
	static const unsigned int KEYCODE_UPPER_LIMIT = 1024;
	static const unsigned int KEYCODE_LOWER_LIMIT = 0;

	GLFWwindow* m_window_ptr = nullptr;
	std::array<bool, KEYCODE_UPPER_LIMIT> m_keys;
	double m_lastX;
	double m_lastY;
	double m_deltaX;
	double m_deltaY;
	bool mouse_initialized;
	bool is_camera_control_active;
public:
	WindowManager(int width, int height);
	~WindowManager();
	inline GLFWwindow* GetWindowPtr() {
		return m_window_ptr;
	};
	inline int ShouldWindowClose() { return glfwWindowShouldClose(m_window_ptr); }
	inline bool& GetKey(int keyCode) { return m_keys[keyCode]; }
	inline MouseDelta GetMouseDelta() { return MouseDelta{ m_deltaX, m_deltaY }; }
	inline bool GetIsCameraControlActive() { return is_camera_control_active; }
private:
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
};

