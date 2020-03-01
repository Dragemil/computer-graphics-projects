#pragma once
#include <array>
#include <vector>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Shader.h"


class Lamps
{
private:
	const glm::vec3 startingPositions[5]
	{
		glm::vec3{ 20.0f, 5.0f, -6.0f },
		glm::vec3{ 20.0f, 5.0f, 13.5f },
		glm::vec3{ -22.0f, 5.0f, -6.0f },
		glm::vec3{ -22.0f, 5.0f, 13.5f },
		glm::vec3{-1.0f, 6.0f, 5.3f},
	};
	const float flightLimit = 3.0f;
	float speed = 0.7f;
	float angle = 0.0f;
	float angleSpeed = 0.0f;

public:
	glm::vec3 positions[5];

	Lamps();

	void Move(float deltaTime);

	glm::mat4* Models();

	~Lamps();
};