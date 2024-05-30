#pragma once

#include "vulkan/vulkan.h"

#include <array>
#include <string>

struct PipelineData
{
	VkPipeline pipeline;
	VkPipelineLayout PipelineLayout;
	std::array<std::string, 2> shaderNames;
	VkPrimitiveTopology Topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	VkPolygonMode PolygonMode = VK_POLYGON_MODE_FILL;
	VkCullModeFlags cullMode = VK_CULL_MODE_BACK_BIT;
};

