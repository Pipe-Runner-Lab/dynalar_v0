#pragma once

#include <glm/glm.hpp>
#include "WindowManager.h"

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float movementSpeed;
	float turnSpeed;

public:
	Camera(glm::vec3 starPosition, glm::vec3 startUp, float startPitch, float startYaw, float turnSpeed, float moveSpeed);
	Camera(float turnSpeed, float moveSpeed);
	Camera();
	glm::mat4 GetViewMatrix() const;

	void Update(float deltaTime, WindowManager& windowManger);
};

