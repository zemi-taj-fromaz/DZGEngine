#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include "PipelineData.h"
#include "Mesh.h"
#include "texture.h"
#include "Sampler.h"

using PipelineDataVec_t = std::vector<std::shared_ptr<PipelineData>>;
using DescriptorSetLayoutVec_t = std::vector<std::shared_ptr<DescriptorSetLayout>>;
using DescriptorSetVec_t = std::vector<std::shared_ptr<DescriptorSet>>;
using BufferDataVec_t = std::vector<std::shared_ptr<BufferData>>;
using BufferDataVec_t = std::vector<std::shared_ptr<BufferData>>;
using TextureVec_t = std::vector<std::shared_ptr<Texture>>;
using SamplersVec_t = std::vector<std::shared_ptr<Sampler>>;
using MeshVec_t = std::vector<std::shared_ptr<Mesh>>;

class dzg;

class Scene
{
public:
	Scene() : WIDTH(800u), HEIGHT(600u) {}
	uint32_t WIDTH;
	uint32_t HEIGHT;
	PipelineDataVec_t pipelineDataVec;
	DescriptorSetLayoutVec_t DescriptorSetLayoutVec;
	DescriptorSetVec_t DescriptorSetVec;
	BufferDataVec_t BufferDataVec;
	TextureVec_t TexturesVec;
	SamplersVec_t SamplersVec;
	MeshVec_t MeshVec;

	std::shared_ptr<Mesh> Player;
	//std::vector<Mesh> MeshVec;

	virtual void scene_update(float totalTime, float deltaTime, dzg* app) {}
};




