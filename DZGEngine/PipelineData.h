#pragma once

#include "vulkan/vulkan.h"

#include <array>
#include <string>
#include <memory>
#include <vector>

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

