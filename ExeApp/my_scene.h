#pragma once

#include "scene.h"

class my_scene : public scene
{
public:
	my_scene()
	{
		PipelineData* pData = new PipelineData();
		pData->shaderNames = std::array<std::string, 2>({ "TriangleShader.vert", "TriangleShader.frag" });
		pipelineDataVec.push_back(std::shared_ptr<PipelineData>(pData));
		pData = nullptr;
	}
};

