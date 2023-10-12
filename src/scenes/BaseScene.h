#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <IMGUI/imgui.h>
#include "../engine/core/WindowManager.h"

namespace scene {

	class BaseScene {
	public:
		BaseScene() {};
		virtual ~BaseScene() {};

		virtual void OnUpdate(float deltaTime, WindowManager& windowManager) {};
		virtual void OnRender() {};
		virtual void OnImGUIRender() {};
	};

	class SceneMenu : public BaseScene {
	public:
		SceneMenu(BaseScene*& ActiveScenePtr);
		void OnImGUIRender() override;

		template<typename T>
		void RegisterScene(const std::string& sceneName) {
			std::cout << "Registering scene: " << sceneName << std::endl;
			m_scenes.push_back(std::make_pair(
				sceneName,
				[]() {
					return new T();
				}
			));
		}
	private:
		BaseScene*& m_ActiveScene;
		std::vector<std::pair<std::string, std::function<BaseScene* ()>>> m_scenes;
	};
}