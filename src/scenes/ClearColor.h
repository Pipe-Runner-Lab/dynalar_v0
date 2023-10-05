#pragma once
#include "BaseScene.h"

namespace scene {

	class ClearColor : public BaseScene {
	private:
		float m_ClearColor[4];

	public:
		ClearColor();
		virtual ~ClearColor() {};

		void OnUpdate(float deltaTime) {};
		void OnRender() override;
		void OnImGUIRender() override;
	};

}


