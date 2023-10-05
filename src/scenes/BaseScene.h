#pragma once

namespace scene {
	
	class BaseScene {
	public:
		BaseScene() {};
		virtual ~BaseScene() {};

		virtual void OnUpdate(float deltaTime) {};
		virtual void OnRender() {};
		virtual void OnImGUIRender() {};
	};

}