#pragma once

#include "scene.h"

class my_scene : public scene
{
public:
	my_scene()
	{
		BindingInfo bInfo1(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,  VK_SHADER_STAGE_VERTEX_BIT);
		BindingInfo bInfo2(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,  VK_SHADER_STAGE_FRAGMENT_BIT);

		DescriptorSetLayout* dsl = new DescriptorSetLayout();
		dsl->bindings.push_back(bInfo1);
		dsl->bindings.push_back(bInfo2);

		PipelineData* pData = new PipelineData();
		pData->shaderNames = std::array<std::string, 2>({ "TriangleShader.vert", "TriangleShader.frag" });
		pData->pDescriptorSetLayout = std::shared_ptr<DescriptorSetLayout>(dsl);
		pipelineDataVec.push_back(std::shared_ptr<PipelineData>(pData));

		DescriptorSetLayoutVec.push_back(std::shared_ptr<DescriptorSetLayout>(dsl));

		pData = nullptr;
		dsl = nullptr;
	}
};

