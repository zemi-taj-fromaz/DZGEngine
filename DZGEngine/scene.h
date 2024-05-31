#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include "PipelineData.h"
#include "Mesh.h"
#include "texture.h"
#include "sampler.h"

using PipelineDataVec_t = std::vector<std::shared_ptr<PipelineData>>;
using DescriptorSetLayoutVec_t = std::vector<std::shared_ptr<DescriptorSetLayout>>;
using DescriptorSetVec_t = std::vector<std::shared_ptr<DescriptorSet>>;
using BufferDataVec_t = std::vector<std::shared_ptr<BufferData>>;
using BufferDataVec_t = std::vector<std::shared_ptr<BufferData>>;
using TextureVec_t = std::vector<std::shared_ptr<texture>>;
using SamplersVec_t = std::vector<std::shared_ptr<sampler>>;

class scene
{
public:
	scene() : WIDTH(800u), HEIGHT(600u) {}
	uint32_t WIDTH;
	uint32_t HEIGHT;
	PipelineDataVec_t pipelineDataVec;
	DescriptorSetLayoutVec_t DescriptorSetLayoutVec;
	DescriptorSetVec_t DescriptorSetVec;
	BufferDataVec_t BufferDataVec;
	TextureVec_t TexturesVec;
	SamplersVec_t SamplersVec;
	std::vector<Mesh> MeshVec;
};




