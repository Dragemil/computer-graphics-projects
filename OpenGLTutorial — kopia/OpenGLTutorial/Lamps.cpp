#include "Lamps.h"

Lamps::Lamps()
{
	for (int i = 0; i < 5; i++)
	{
		positions[i] = startingPositions[i];
	}
}

void Lamps::Move(float deltaTime)
{
	if ((positions[0].y > startingPositions[0].y + flightLimit && speed > 0)
		|| (positions[0].y < startingPositions[0].y - flightLimit && speed < 0))
	{
		speed = -speed;
	}

	for (int i = 0; i < 4; i++)
	{
		positions[i].y += speed * deltaTime;
	}
}

glm::mat4* Lamps::Models()
{
	static glm::mat4 models[5];

	for (int i = 0; i < 5; i++)
	{
		models[i] = glm::mat4(1.0f);
		models[i] = glm::translate(models[i], positions[i]);
		models[i] = glm::scale(models[i], glm::vec3(0.002f));
	}
	
	//model = glm::rotate(model, angle, glm::vec3{ 0, 0, 1 });
	return models;
}

Lamps::~Lamps()
{

}