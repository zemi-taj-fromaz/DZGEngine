#pragma once

#include "app/app.h"

#include <glm/glm.hpp>

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;

	static void bufferUpdateFunction(dzg* app, void* bufferMapped);
};

