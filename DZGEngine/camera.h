#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Camera
{
	Camera(float left, float right, float bottom, float top)
		: ProjectionMatrix( glm::ortho(left, right, bottom ,top, -1.0f, 1.0f))
	{
		ViewMatrix = glm::mat4(1.0f);
	}

	void setPosition(glm::vec3 pos)
	{
		Position = pos;
		ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), Position));
	}

	glm::vec3 Position;
	


	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

};