#pragma once
#include <array>
#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Shader.h"


class Ball
{
private:
	const glm::vec3 defaultPostion = glm::vec3{ 0.0f, 0.0f, 0.0f };
	const glm::vec3 center = glm::vec3{ 0.0f, 0.0f, 0.3f };
	const float friction = 0.7f;
	const float horizontalSpeed = 5.0f;

	glm::vec3 position = glm::vec3{ 0, 0, 0 };
	float speed = 0.0f;
	float horizontalAngle = 0.0f;
	float verticalAngle = 0.0f;

public:
	Ball();

	void Accelerate();
	void Move(float deltaTime);
	void Rotate(float deltaTime, bool right);
	void Reset();

	glm::mat4 Model();
	glm::vec3 Position();
	glm::vec3 FollowingPosition();

	~Ball();
};