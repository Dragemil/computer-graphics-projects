#include "Ball.h"

Ball::Ball()
{
	Reset();
}

void Ball::Accelerate()
{
	if (speed <= 2.5f)
		speed = 5.0f;
}

void Ball::Reset()
{
	position = defaultPostion;
	speed = 0.0f;
	verticalAngle = 0.0f;
	horizontalAngle = 0.0f;
}

void Ball::Move(float deltaTime)
{
	if (speed > 0)
	{
		position.x += speed * deltaTime * glm::cos(horizontalAngle);
		position.z -= speed * deltaTime * glm::sin(horizontalAngle);

		verticalAngle -= 1.3f * speed * deltaTime;
		verticalAngle = fmod(verticalAngle, 360);

		speed *= (1.0f - deltaTime * friction);
	}
}

void Ball::Rotate(float deltaTime, bool right)
{
	if (right)
	{
		horizontalAngle -= deltaTime * horizontalSpeed;
	}
	else
	{
		horizontalAngle += deltaTime * horizontalSpeed;
	}

	horizontalAngle = fmod(horizontalAngle, 360);
}

glm::mat4 Ball::Model()
{
	auto model = glm::translate(glm::mat4(1.0f), position);
	model = glm::translate(model, center);
	model = glm::rotate(model, horizontalAngle, glm::vec3{ 0, 1, 0 });
	model = glm::translate(model, -center);
	model = glm::rotate(model, verticalAngle, glm::vec3{ 0, 0, 1 });
	model = glm::scale(model, glm::vec3(0.02f));
	return model;
}

glm::vec3 Ball::Position()
{
	return position + center;
}

glm::vec3 Ball::FollowingPosition()
{
	return position + center + glm::vec3
	{
		-glm::cos(horizontalAngle) * 5,
		2,
		glm::sin(horizontalAngle) * 5,
	};
}

Ball::~Ball()
{

}