#include <iostream>
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include "IMGUI/imgui_impl_opengl3.h"
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "engine/Renderer.h"
#include "engine/primitives/TexturedSquare.h"
#include "engine/primitives/Pyramid.h"
#include "engine/core/Camera.h"

const GLint WIDTH = 1200, HEIGHT = 900;

int main() {
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
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Dynalar V0", NULL, NULL);

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

	/* Enable vsync : Sync render loop to monitor refresh rate */
	glfwSwapInterval(1);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	/* Initialize IMGUI */
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(mainWindow, true);
	ImGui_ImplOpenGL3_Init("#version 440");

	/* Initialize GLEW */
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "GLEW initialization failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Enable depth test */
	glEnable(GL_DEPTH_TEST);

	/* Enable blending, set blending function and equation */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendEquation(GL_ADD);

	/* Setup viewport size */
	glViewport(0, 0, bufferWidth, bufferHeight);

	/*Triangle triangle = Triangle();
	triangle.move(0.3f, 0, 0);*/
	//TriangleImp tri = TriangleImp();
	Camera camera = Camera();
	Renderer renderer = Renderer(camera);

	TexturedSquare texturedSquare = TexturedSquare();
	Pyramid pyramid = Pyramid();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(mainWindow))
	{
		/* Check for user events */
		glfwPollEvents();

		/* Create IMGUI frame */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/* Render here */
		renderer.Clear();

		{
			ImGui::Begin("Dashboard");
			static float f = 0.0f;
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		// INFO: swap buffer should not be called before drawing
		//texturedSquare.Draw(renderer);
		pyramid.Draw(renderer);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(mainWindow);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	return 0;
}