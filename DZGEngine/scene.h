#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include "PipelineData.h"

using PipelineDataVec_t = std::vector<std::shared_ptr<PipelineData>>;

class scene
{
public:
	scene() : WIDTH(800u), HEIGHT(600u) {}
	uint32_t WIDTH;
	uint32_t HEIGHT;
	PipelineDataVec_t pipelineDataVec;
};




