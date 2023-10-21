#pragma once

#include <GLEW/glew.h>
#include <array>
#include "glm/glm.hpp"
#include "../engine/core/IndexBuffer.h"
#include "../engine/core/VertexArray.h"
#include "../engine/core/VertexBuffer.h"
#include "../engine/core/Texture.h"
#include "../engine/Renderer.h"
#include "../engine/core/lights/DirectionalLight.h"
#include "../engine/core/materials/BaseMaterial.h"

#include "BaseScene.h"

namespace scene {
	class DirectionalLightPyramid : public BaseScene {
	private:
		Texture texture1;
		Texture texture2;
		GLfloat vertices[4 * 8];
		GLuint indices[12];
		VertexArray va;
		VertexBuffer vb;
		VertexBufferLayout layout;
		IndexBuffer ib;
		Shader shader;
		Camera camera;
		Renderer renderer;
		glm::mat4 model;
		glm::vec3 translation;
		DirectionalLight directionalLight;
		std::array<BaseMaterial, 1> material_array;
	public:
		DirectionalLightPyramid();

		void OnUpdate(float deltaTime, WindowManager& windowManager) override;
		void OnRender() override;
		void OnImGUIRender() override;
	};
}
