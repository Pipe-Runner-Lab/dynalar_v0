#include "ModelImport.h"

#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "../engine/utils.h"

using namespace std::string_literals; // for string literal `s`

scene::ModelImport::ModelImport() :
	meshGroup(MeshGroup("assets/models/x-wing.obj")),
	shader(Shader("assets/shaders/model.vert", "assets/shaders/model.frag")),
	camera(Camera()),
	renderer(Renderer(camera, glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f))),
	model(glm::mat4(1.0f)),
	translation(glm::vec3(0.0f, -5.0f, -20.0f)),
	directionalLight(DirectionalLight(0.17f, glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, glm::vec3(0.0f, -1.0f, 0.0f))),
	pointLight_array(
		{
			PointLight(1.4f, glm::vec3(0.0f, 1.0f, 0.0f), 0.75f, glm::vec3(-2.0f, -4.0f, -27.5f), Attenuation{0.2f, 0.2f, 0.3f}),
			PointLight(1.5f, glm::vec3(1.0f, 0.0f, 0.0f), 0.55f, glm::vec3(-6.7f, -11.0f, -19.5f), Attenuation{0.1f, 0.3f, 0.3f})
		}
	),
	spotLight_array(
		{
			SpotLight(0.4f, glm::vec3(1.0f, 0.0f, 1.0f), 0.3f, glm::vec3(-2.0f, -1.0f, -19.0f), glm::vec3(1.0f, -1.0f, 0.648f), Attenuation{0.1f, 0.2f, 0.3f}, 20)
		}
	),
	material_array(
		{
			BaseMaterial(1.0f, 32.0f)
		}
	)
{
	for (size_t meshIdx = 0; meshIdx < meshGroup.m_MeshList.size(); meshIdx++) {
		Mesh mesh = meshGroup.m_MeshList[meshIdx];
		VertexArray va = VertexArray();
		VertexBuffer vb = VertexBuffer(
			mesh.vertices.data(),
			sizeof(mesh.vertices.data()[0]) * mesh.vertices.size()
		);

		VertexBufferLayout layout = VertexBufferLayout();
		layout.Push<float>(3); // vertices
		layout.Push<float>(2); // uv
		layout.Push<float>(3); // normal
		va.AddBuffer(vb, layout);

		IndexBuffer ib = IndexBuffer(
			mesh.indices.data(),
			mesh.indices.size()
		);

		va_list.push_back(va);
		ib_list.push_back(ib);
	}

	// Initialize Uniforms

	shader.Bind();
	shader.SetUniform1i("u_Texture", 0); // setting slot in shader (activating)
	shader.Unbind();

	model = glm::scale(model, glm::vec3(0.006f, 0.006f, 0.006f));
}

void scene::ModelImport::OnUpdate(float deltaTime, WindowManager& windowManager)
{
	camera.Update(deltaTime, windowManager);
	//model = glm::rotate(model, deltaTime * 0.005f, glm::vec3(0, 1, 0));
}

void scene::ModelImport::OnRender()
{
	glm::vec3& color = directionalLight.GetColor();
	glm::vec3& direction = directionalLight.GetDirection();

	shader.Bind();
	shader.SetUniform1f("u_directionalLight.base.ambientIntensity", directionalLight.GetAmbientIntensity());
	shader.SetUniform3f("u_directionalLight.base.color", color.r, color.g, color.b);
	shader.SetUniform1f("u_directionalLight.base.diffuseIntensity", directionalLight.GetDiffuseIntensity());
	shader.SetUniform3f("u_directionalLight.direction", direction.x, direction.y, direction.z);
	shader.SetUniformMatrix4f("u_model", glm::translate(model, translation));
	shader.SetUniform3f("u_eyePos", camera.position.x, camera.position.y, camera.position.z);

	shader.SetUniform1i("u_num_pointLights", pointLight_array.size());
	for (int pointLightIdx = 0; pointLightIdx < pointLight_array.size(); pointLightIdx++) {
		glm::vec3 color = pointLight_array[pointLightIdx].GetColor();
		glm::vec3 position = pointLight_array[pointLightIdx].GetPosition();
		Attenuation attenuation = pointLight_array[pointLightIdx].GetAttenuation();
		shader.SetUniform3f(
			"u_pointLightArray["s + std::to_string(pointLightIdx) + "].base.color",
			color.x, color.y, color.z
		);
		shader.SetUniform1f(
			"u_pointLightArray["s + std::to_string(pointLightIdx) + "].base.ambientIntensity",
			pointLight_array[pointLightIdx].GetAmbientIntensity()
		);
		shader.SetUniform1f(
			"u_pointLightArray["s + std::to_string(pointLightIdx) + "].base.diffuseIntensity",
			pointLight_array[pointLightIdx].GetDiffuseIntensity()
		);
		shader.SetUniform3f(
			"u_pointLightArray["s + std::to_string(pointLightIdx) + "].position",
			position.x, position.y, position.z
		);
		shader.SetUniform1f(
			"u_pointLightArray["s + std::to_string(pointLightIdx) + "].attenuation.exponent_coef",
			attenuation.exponent_coef
		);
		shader.SetUniform1f(
			"u_pointLightArray["s + std::to_string(pointLightIdx) + "].attenuation.linear_coef",
			attenuation.linear_coef
		);
		shader.SetUniform1f(
			"u_pointLightArray["s + std::to_string(pointLightIdx) + "].attenuation.constant_coef",
			attenuation.constant_coef
		);
	}

	shader.SetUniform1i("u_num_spotLights", spotLight_array.size());
	for (int spotLightIdx = 0; spotLightIdx < spotLight_array.size(); spotLightIdx++) {
		glm::vec3 color = spotLight_array[spotLightIdx].GetColor();
		glm::vec3 direction = spotLight_array[spotLightIdx].GetDirection();
		glm::vec3 position = spotLight_array[spotLightIdx].GetPosition();
		Attenuation attenuation = spotLight_array[spotLightIdx].GetAttenuation();
		shader.SetUniform3f(
			"u_spotLightArray["s + std::to_string(spotLightIdx) + "].base.color",
			color.x, color.y, color.z
		);
		shader.SetUniform1f(
			"u_spotLightArray["s + std::to_string(spotLightIdx) + "].base.ambientIntensity",
			spotLight_array[spotLightIdx].GetAmbientIntensity()
		);
		shader.SetUniform1f(
			"u_spotLightArray["s + std::to_string(spotLightIdx) + "].base.diffuseIntensity",
			spotLight_array[spotLightIdx].GetDiffuseIntensity()
		);
		shader.SetUniform3f(
			"u_spotLightArray["s + std::to_string(spotLightIdx) + "].position",
			position.x, position.y, position.z
		);
		shader.SetUniform3f(
			"u_spotLightArray["s + std::to_string(spotLightIdx) + "].direction",
			direction.x, direction.y, direction.z
		);
		shader.SetUniform1f(
			"u_spotLightArray["s + std::to_string(spotLightIdx) + "].attenuation.exponent_coef",
			attenuation.exponent_coef
		);
		shader.SetUniform1f(
			"u_spotLightArray["s + std::to_string(spotLightIdx) + "].attenuation.linear_coef",
			attenuation.linear_coef
		);
		shader.SetUniform1f(
			"u_spotLightArray["s + std::to_string(spotLightIdx) + "].attenuation.constant_coef",
			attenuation.constant_coef
		);
		shader.SetUniform1f(
			"u_spotLightArray["s + std::to_string(spotLightIdx) + "].coneAngle",
			spotLight_array[spotLightIdx].GetConeAngle()
		);
	}

	for (int materialIdx = 0; materialIdx < material_array.size(); materialIdx++) {
		shader.SetUniform1f(
			"u_material_"s + std::to_string(materialIdx) + ".shininess",
			material_array[materialIdx].GetShininess()
		);
		shader.SetUniform1f(
			"u_material_"s + std::to_string(materialIdx) + ".specularIntensity",
			material_array[materialIdx].GetSpecularIntensity()
		);
	}

	for (size_t idx = 0; idx < ib_list.size(); idx++) {
		unsigned int materialIndex = meshGroup.m_MeshToTexture[idx];

		// each mesh is bound to one texture of any type

		if (materialIndex < meshGroup.m_TextureList.size() && meshGroup.m_TextureList[materialIndex])
		{
			meshGroup.m_TextureList[materialIndex]->Bind(0);
		}

		renderer.Draw(va_list[idx], ib_list[idx], shader);
	}
}

void scene::ModelImport::OnImGUIRender()
{
	ImGui::SliderFloat3("Translation", glm::value_ptr(translation), -100.0f, 0.0f);
	ImGui::Text("Directional Light");
	ImGui::ColorEdit3("D Color", glm::value_ptr(directionalLight.GetColor()));
	ImGui::SliderFloat("D Ambient Intensity", &directionalLight.GetAmbientIntensity(), 0.0f, 1.0f);
	ImGui::SliderFloat("D Diffuse Intensity", &directionalLight.GetDiffuseIntensity(), 0.0f, 1.0f);
	ImGui::SliderFloat3("D Direction", glm::value_ptr(directionalLight.GetDirection()), -1.0f, 1.0f);

	ImGui::Text("Specular Light");
	for (int materialIdx = 0; materialIdx < material_array.size(); materialIdx++) {
		ImGui::SliderFloat(
			("M Specular Intensity "s + std::to_string(materialIdx)).c_str(),
			&material_array[materialIdx].GetSpecularIntensity(),
			0.0f, 1.0f
		);
		ImGui::SliderFloat(
			("M Shininess " + std::to_string(materialIdx)).c_str(),
			&material_array[materialIdx].GetShininess(),
			2.0f, 32.0f
		);
	}

	ImGui::Text("Point Light");
	for (int pointLightIdx = 0; pointLightIdx < pointLight_array.size(); pointLightIdx++) {
		Attenuation& att = pointLight_array[pointLightIdx].GetAttenuation();
		ImGui::SliderFloat3(
			("P Position "s + std::to_string(pointLightIdx)).c_str(),
			glm::value_ptr(pointLight_array[pointLightIdx].GetPosition()),
			-100.0f, 100.0f
		);
		ImGui::ColorEdit3(
			("P Color "s + std::to_string(pointLightIdx)).c_str(),
			glm::value_ptr(pointLight_array[pointLightIdx].GetColor())
		);
		ImGui::SliderFloat(
			("P Exponent "s + std::to_string(pointLightIdx)).c_str(),
			&att.exponent_coef,
			0.0f, 100.0f
		);
		ImGui::SliderFloat(
			("P Linear "s + std::to_string(pointLightIdx)).c_str(),
			&att.linear_coef,
			0.0f, 100.0f
		);
		ImGui::SliderFloat(
			("P Constant "s + std::to_string(pointLightIdx)).c_str(),
			&att.constant_coef,
			0.0f, 100.0f
		);
		ImGui::SliderFloat(
			("P Ambient Intensity "s + std::to_string(pointLightIdx)).c_str(),
			&pointLight_array[pointLightIdx].GetAmbientIntensity(),
			0.0f, 100.0f
		);
		ImGui::SliderFloat(
			("P Diffused Intensity "s + std::to_string(pointLightIdx)).c_str(),
			&pointLight_array[pointLightIdx].GetDiffuseIntensity(),
			0.0f, 100.0f
		);
	}

	ImGui::Text("Spot Light");
	for (int spotLightIdx = 0; spotLightIdx < spotLight_array.size(); spotLightIdx++) {
		Attenuation& att = spotLight_array[spotLightIdx].GetAttenuation();
		ImGui::SliderFloat3(
			("S Direction "s + std::to_string(spotLightIdx)).c_str(),
			glm::value_ptr(spotLight_array[spotLightIdx].GetDirection()),
			-1.0f, 1.0f
		);
		ImGui::SliderFloat3(
			("S Position "s + std::to_string(spotLightIdx)).c_str(),
			glm::value_ptr(spotLight_array[spotLightIdx].GetPosition()),
			-100.0f, 100.0f
		);
		ImGui::ColorEdit3(
			("S Color "s + std::to_string(spotLightIdx)).c_str(),
			glm::value_ptr(spotLight_array[spotLightIdx].GetColor())
		);
		ImGui::SliderFloat(
			("S Exponent "s + std::to_string(spotLightIdx)).c_str(),
			&att.exponent_coef,
			0.0f, 100.0f
		);
		ImGui::SliderFloat(
			("S Linear "s + std::to_string(spotLightIdx)).c_str(),
			&att.linear_coef,
			0.0f, 100.0f
		);
		ImGui::SliderFloat(
			("S Constant "s + std::to_string(spotLightIdx)).c_str(),
			&att.constant_coef,
			0.0f, 100.0f
		);
		ImGui::SliderFloat(
			("S Ambient Intensity "s + std::to_string(spotLightIdx)).c_str(),
			&spotLight_array[spotLightIdx].GetAmbientIntensity(),
			0.0f, 100.0f
		);
		ImGui::SliderFloat(
			("S Diffused Intensity "s + std::to_string(spotLightIdx)).c_str(),
			&spotLight_array[spotLightIdx].GetDiffuseIntensity(),
			0.0f, 100.0f
		);
		ImGui::SliderFloat(
			("S Angle "s + std::to_string(spotLightIdx)).c_str(),
			&spotLight_array[spotLightIdx].GetRawConeAngle(),
			1.0f, 180.0f
		);
	}
}
