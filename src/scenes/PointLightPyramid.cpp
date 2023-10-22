#include "PointLightPyramid.h"

#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "../engine/utils.h"
#include <iostream>

using namespace std::string_literals; // for string literal `s`

scene::PointLightPyramid::PointLightPyramid() :
	texture1(Texture("assets/images/brick.png")),
	texture2(Texture("assets/images/dirt.png")),
	vertices{
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	},
	indices{
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	},
	va(VertexArray()),
	vb(VertexBuffer(
		PopulateNormals<GLfloat>(vertices, indices, 32, 8, 12, 0, 5),
		sizeof(vertices)
	)),
	layout(VertexBufferLayout()),
	ib(IndexBuffer(indices, sizeof(indices) / sizeof(GLuint))),
	shader(Shader("assets/shaders/pointLightPyramid.vert", "assets/shaders/pointLightPyramid.frag")),
	camera(Camera()),
	renderer(Renderer(camera, glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f))),
	model(glm::mat4(1.0f)),
	translation(glm::vec3(0.0f, 0.0f, -20.0f)),
	directionalLight(DirectionalLight(1.0f, glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, glm::vec3(0.0f, -1.0f, 0.0f))),
	pointLight_array({
			PointLight(1.0f, glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, glm::vec3(-4.0f, 0.0f, 0.0f), Attenuation{0.3f, 0.2f, 0.1f})
		}
	),
	material_array(
		{
			BaseMaterial(1.0f, 32.0f)
		}
	)
{
	layout.Push<float>(3); // vertices
	layout.Push<float>(2); // uv
	layout.Push<float>(3); // normal
	va.AddBuffer(vb, layout);

	// Initialize Uniforms

	shader.Bind();
	shader.SetUniform1i("u_Texture", 0); // setting slot in shader
	shader.Unbind();

	std::cout << pointLight_array.size() << std::endl;
}

void scene::PointLightPyramid::OnUpdate(float deltaTime, WindowManager& windowManager)
{
	camera.Update(deltaTime, windowManager);
	//model = glm::rotate(model, deltaTime * 0.005f, glm::vec3(0, 1, 0));
}

void scene::PointLightPyramid::OnRender()
{
	texture1.Bind(0); // activating slot

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
	renderer.Draw(va, ib, shader);

	texture2.Bind(0); // activating slot

	shader.Bind();
	shader.SetUniformMatrix4f("u_model", glm::translate(model, translation + glm::vec3(0.0f, 5.0f, 0.0f)));
	renderer.Draw(va, ib, shader);
}

void scene::PointLightPyramid::OnImGUIRender()
{
	ImGui::SliderFloat3("Translation", glm::value_ptr(translation), -100.0f, 0.0f);
	ImGui::Text("Directional Light");
	ImGui::ColorEdit3("Color", glm::value_ptr(directionalLight.GetColor()));
	ImGui::SliderFloat("Ambient Intensity", &directionalLight.GetAmbientIntensity(), 0.0f, 1.0f);
	ImGui::SliderFloat("Diffuse Intensity", &directionalLight.GetDiffuseIntensity(), 0.0f, 1.0f);
	ImGui::SliderFloat3("Direction", glm::value_ptr(directionalLight.GetDirection()), -1.0f, 1.0f);
	ImGui::Text("Point Light");
	for (int pointLightIdx = 0; pointLightIdx < pointLight_array.size(); pointLightIdx++) {
		Attenuation& att = pointLight_array[pointLightIdx].GetAttenuation();
		ImGui::SliderFloat3(
			("Position "s + std::to_string(pointLightIdx)).c_str(), 
			glm::value_ptr(pointLight_array[pointLightIdx].GetPosition()), 
			-100.0f, 100.0f
		);
		ImGui::ColorEdit3(
			("Color "s + std::to_string(pointLightIdx)).c_str(),
			glm::value_ptr(pointLight_array[pointLightIdx].GetColor())
		);
		ImGui::SliderFloat(
			("Exponent "s + std::to_string(pointLightIdx)).c_str(),
			&att.exponent_coef,
			0.0f, 100.0f
		);
		ImGui::SliderFloat(
			("Linear "s + std::to_string(pointLightIdx)).c_str(),
			&att.linear_coef,
			0.0f, 100.0f
		);
		ImGui::SliderFloat(
			("Constant "s + std::to_string(pointLightIdx)).c_str(),
			&att.constant_coef,
			0.0f, 100.0f
		);
	}
	ImGui::Text("Specular Light");
	for (int materialIdx = 0; materialIdx < material_array.size(); materialIdx++) {
		ImGui::SliderFloat(
			("Specular Intensity "s + std::to_string(materialIdx)).c_str(),
			&material_array[materialIdx].GetSpecularIntensity(),
			0.0f, 1.0f
		);
		ImGui::SliderFloat(
			("Shininess " + std::to_string(materialIdx)).c_str(),
			&material_array[materialIdx].GetShininess(),
			2.0f, 32.0f
		);
	}
}
