#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

struct Camera
{
	//Camera(float left, float right, float bottom, float top);
	//
	//void movePosition(glm::vec3 pos);

	Camera(float left, float right, float bottom, float top)
		: ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
		Position(glm::vec3(0.0f)),
		ViewMatrix(glm::mat4(1.0f))
	{
		ViewMatrix = glm::mat4(1.0f);

	}

	void movePosition(glm::vec3 pos)
	{
		Position += pos;
		std::cout << "position: " << Position.x << "," << Position.y << "," << Position.z << std::endl;
		//ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), Position));
		ViewMatrix = glm::translate(glm::mat4(1.0f), Position);
	}

	glm::vec3 Position;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	float speed{ 10000000.0f };

};