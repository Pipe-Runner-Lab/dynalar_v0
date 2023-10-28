#pragma once

#include <GLEW/glew.h>
#include <array>
#include <vector>
#include "glm/glm.hpp"
#include "../engine/core/IndexBuffer.h"
#include "../engine/core/VertexArray.h"
#include "../engine/core/VertexBuffer.h"
#include "../engine/core/Texture.h"
#include "../engine/Renderer.h"
#include "../engine/core/lights/PointLight.h"
#include "../engine/core/lights/SpotLigh.h"
#include "../engine/core/lights/DirectionalLight.h"
#include "../engine/core/materials/BaseMaterial.h"
#include "../engine/core/models/MeshGroup.h"

#include "BaseScene.h"

namespace scene {
	class ModelImport : public BaseScene {
	private:
		MeshGroup meshGroup;
		std::vector <VertexArray> va_list;
		std::vector <IndexBuffer> ib_list;
		Shader shader;
		Camera camera;
		Renderer renderer;
		glm::mat4 model;
		glm::vec3 translation;
		DirectionalLight directionalLight;
		std::array<PointLight, 2> pointLight_array;
		std::array<SpotLight, 1> spotLight_array;
		std::array<BaseMaterial, 1> material_array;
	public:
		ModelImport();

		void OnUpdate(float deltaTime, WindowManager& windowManager) override;
		void OnRender() override;
		void OnImGUIRender() override;
	};
}
