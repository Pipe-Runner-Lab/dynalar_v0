#pragma once

#include <GLEW/glew.h>
#include "glm/glm.hpp"
#include "../engine/core/IndexBuffer.h"
#include "../engine/core/VertexArray.h"
#include "../engine/core/VertexBuffer.h"
#include "../engine/core/Texture.h"
#include "../engine/Renderer.h"

#include "BaseScene.h"

namespace scene {
	class TexturePyramid : public BaseScene {
	private:
		Texture texture1;
		Texture texture2;
		GLfloat vertices[4 * 5];
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
	public:
		TexturePyramid();

		void OnUpdate(float deltaTime, WindowManager& windowManager) override;
		void OnRender() override;
		void OnImGUIRender() override;
	};
}
