#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera(glm::vec3 starPosition, glm::vec3 startUp, float startPitch, float startYaw, float turnSpeed, float moveSpeed) :
	position(starPosition),
	up(startUp),
	pitch(startPitch),
	yaw(startYaw),
	front(glm::vec3(0.0f, 0.0f, -1.0f)),
	worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	movementSpeed(moveSpeed),
	turnSpeed(turnSpeed)
{}

Camera::Camera(float turnSpeed, float moveSpeed) :
	position(glm::vec3(0, 0, 0)),
	up(glm::vec3(0, 1.0f, 0)),
	pitch(0),
	yaw(-90),
	front(glm::vec3(0.0f, 0.0f, -1.0f)),
	worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	movementSpeed(moveSpeed),
	turnSpeed(turnSpeed)
{}

Camera::Camera() :
	position(glm::vec3(0, 0, 0)),
	up(glm::vec3(0, 1.0f, 0)),
	pitch(0),
	yaw(-90),
	front(glm::vec3(0.0f, 0.0f, -1.0f)),
	worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	movementSpeed(0.02f),
	turnSpeed(0.2f)
{}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(position, position + front, up);
}

void Camera::Update(float deltaTime, WindowManager& windowManger)
{
	MouseDelta delta = windowManger.GetMouseDelta();
	yaw += delta.deltaX * turnSpeed;
	pitch += delta.deltaY * turnSpeed;

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	glm::vec3 right = glm::normalize(glm::cross(front, worldUp));

	up = glm::normalize(glm::cross(right, front));

	float scaledDelta = movementSpeed * deltaTime;

	/* Key controls */
	if (windowManger.GetKey(GLFW_KEY_W)) {
		position += front * scaledDelta;
	}

	if (windowManger.GetKey(GLFW_KEY_A)) {
		position -= right * scaledDelta;
	}

	if (windowManger.GetKey(GLFW_KEY_S)) {
		position -= front * scaledDelta;
	}

	if (windowManger.GetKey(GLFW_KEY_D)) {
		position += right * scaledDelta;
	}
}
