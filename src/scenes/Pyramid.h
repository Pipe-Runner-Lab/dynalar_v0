#pragma once

#include <GLEW/glew.h>
#include "glm/glm.hpp"
#include "../engine/core/IndexBuffer.h"
#include "../engine/core/VertexArray.h"
#include "../engine/core/VertexBuffer.h"
#include "../engine/Renderer.h"

#include "BaseScene.h"

namespace scene {
	class Pyramid : public BaseScene {
	private:
		GLfloat vertices[4 * 3];
		GLuint indices[12];
		VertexArray va;
		VertexBuffer vb;
		VertexBufferLayout layout;
		IndexBuffer ib;
		Shader shader;
		Camera camera;
		Renderer renderer;
		glm::mat4 model_1;
		glm::vec3 translation_1;
	public:
		Pyramid();

		void OnUpdate(float deltaTime, WindowManager& windowManager) override;
		void OnRender() override;
		void OnImGUIRender() override;
	};
}
