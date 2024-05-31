#pragma once

#include <vulkan/vulkan.h>

#include <array>
#include <string>
#include <memory>
#include <vector>
#include <functional>

#include "sampler.h"
#include "texture.h"

class dzg;

struct BindingInfo
{
	BindingInfo(VkDescriptorType type, VkShaderStageFlagBits stageFlags) : type(type), stageFlags(stageFlags), descriptorCount(1)
	{}
	BindingInfo(VkDescriptorType type, VkShaderStageFlagBits stageFlags, int descriptorCount) : type(type), stageFlags(stageFlags), descriptorCount(descriptorCount)
	{}

	VkDescriptorType type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	VkShaderStageFlagBits stageFlags;
	int descriptorCount; // number of values in the array of object
};

struct DescriptorSetLayout
{
	VkDescriptorSetLayout dSetLayout;
	std::vector<BindingInfo> bindings;
};

struct BufferData
{
	BufferData(VkDescriptorType type, VkBufferUsageFlagBits usage, size_t size) 
		: type(type), usage(usage), size(size)
	{}
	BufferData(VkDescriptorType type, VkBufferUsageFlagBits usage, size_t size, std::function<void(dzg*, void*)> bufferUpdateFunc)
		: type(type), usage(usage), size(size), bufferUpdateFunc(bufferUpdateFunc)
	{}


	BufferData(std::shared_ptr<texture> Texture, std::shared_ptr<sampler> TextureSampler) 
		: Texture(Texture), TextureSampler(TextureSampler), type(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
	{}
	BufferData(std::shared_ptr<texture> Texture, std::shared_ptr<sampler> TextureSampler, std::function<void(dzg*, void*)> bufferUpdateFunc)
		: Texture(Texture), TextureSampler(TextureSampler), type(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER), bufferUpdateFunc(bufferUpdateFunc)
	{}

	std::vector<VkBuffer> Buffers;
	std::vector<VkDeviceMemory> BuffersMemory;
	std::vector<void*> BuffersMapped;

	VkDescriptorType type;
	VkBufferUsageFlagBits usage;
	size_t size;

	std::function<void(dzg*, void*)> bufferUpdateFunc = [](dzg* app, void*) {};

	std::shared_ptr<sampler> TextureSampler;
	std::shared_ptr<texture> Texture;

	void update(dzg* app,int currFrame)
	{
		bufferUpdateFunc(app, BuffersMapped[currFrame % BuffersMapped.size()]);
	}
};

struct DescriptorSet
{
	std::shared_ptr<DescriptorSetLayout> layout;
	std::vector<VkDescriptorSet> sets;
	std::vector<std::shared_ptr<BufferData>> bufferDataVec;
};

struct PipelineData
{
	VkPipeline pipeline;
	VkPipelineLayout PipelineLayout;
	std::array<std::string, 2> shaderNames;

	std::shared_ptr<DescriptorSetLayout> pDescriptorSetLayout;

	VkPrimitiveTopology Topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	VkPolygonMode PolygonMode = VK_POLYGON_MODE_FILL;
	VkCullModeFlags cullMode = VK_CULL_MODE_BACK_BIT;
};

