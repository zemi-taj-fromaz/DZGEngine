#pragma once

#include "app/app.h"

#include <glm/glm.hpp>

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;

	static void bufferUpdateFunction(dzg* app, void* bufferMapped);
};

struct ObjectDataBuffer
{
	glm::mat4 Model;
	glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

	static void bufferUpdateFunction(dzg* app, void* bufferMapped);

};

struct ResolutionBufferObject {
	float width;
	float height;

	static void bufferUpdateFunction(dzg* app, void* bufferMapped);
};

