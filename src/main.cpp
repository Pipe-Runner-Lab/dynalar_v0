#include <iostream>
#include <IMGUI/imgui.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "engine/Renderer.h"
#include "engine/core/WindowManager.h"
#include "scenes/BaseScene.h"
#include "scenes/ClearColor.h"
#include "scenes/Texture2D.h"
#include "scenes/Pyramid.h"
#include "scenes/TexturePyramid.h"
#include "scenes/DirectionalLightPyramid.h"
#include "scenes/PointLightPyramid.h"
#include "scenes/SpotLightPyramid.h"
#include "ASSIMP/Importer.hpp"

static const GLint WIDTH = 1920, HEIGHT = 1080;


int main() {
	Assimp::Importer importer;

	WindowManager windowManager = WindowManager(WIDTH, HEIGHT);

	/* Initialize ImGui */
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(windowManager.GetWindowPtr(), true);
	ImGui_ImplOpenGL3_Init("#version 440");

	scene::BaseScene* currentScene = nullptr;
	scene::SceneMenu* sceneMenu = new scene::SceneMenu(currentScene);

	/* Set active scene to be main menu */
	currentScene = sceneMenu;

	sceneMenu->RegisterScene<scene::ClearColor>("Clear Color");
	sceneMenu->RegisterScene<scene::Texture2D>("2D Texture");
	sceneMenu->RegisterScene<scene::Pyramid>("Pyramid");
	sceneMenu->RegisterScene<scene::TexturePyramid>("Textured Pyramid");
	sceneMenu->RegisterScene<scene::DirectionalLightPyramid>("Directional Light Pyramid");
	sceneMenu->RegisterScene<scene::PointLightPyramid>("Point Light Pyramid");
	sceneMenu->RegisterScene<scene::SpotLightPyramid>("Spot Light Pyramid");

	/* Loop until the user closes the window */
	while (!windowManager.ShouldWindowClose())
	{
		float dt = 1000.0f / ImGui::GetIO().Framerate;

		/* Check for user events */
		glfwPollEvents();

		/* Create IMGUI frame */
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/* Clear frame */
		Renderer::Clear();

		/* Custom render starts here */

		if (currentScene) {
			currentScene->OnUpdate(dt, windowManager);
			currentScene->OnRender();
			ImGui::Begin("Scene");
			if (currentScene != sceneMenu && ImGui::Button("<-")) {
				delete currentScene;
				currentScene = sceneMenu;
			}
			currentScene->OnImGUIRender();
			ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
			ImGui::End();
		}

		/* Custom render ends here */

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(windowManager.GetWindowPtr());
	}

	if (currentScene != sceneMenu) {
		delete sceneMenu;
	}
	delete currentScene;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
	return 0;
}