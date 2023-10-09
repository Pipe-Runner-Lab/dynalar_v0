#pragma once

#include <GLEW/glew.h>
#include "glm/glm.hpp"
#include "BaseScene.h"
#include "../engine/core/Texture.h"
#include "../engine/core/IndexBuffer.h"
#include "../engine/core/VertexArray.h"
#include "../engine/core/VertexBuffer.h"
#include "../engine/Renderer.h"

namespace scene {

	class Texture2D : public BaseScene {
	private:
		Texture texture;
		GLfloat vertices[4 * 5];
		GLuint indices[6];
		VertexArray va;
		VertexBuffer vb;
		VertexBufferLayout layout;
		IndexBuffer ib;
		Shader shader;
		Camera camera;
		Renderer renderer;
		glm::mat4 model_1;
		glm::mat4 model_2;
		glm::vec3 translation_1;
		glm::vec3 translation_2;
	public:
		Texture2D();
		virtual ~Texture2D() {};

		void OnUpdate(float deltaTime) {};
		void OnRender() override;
		void OnImGUIRender() override;
	};

}


