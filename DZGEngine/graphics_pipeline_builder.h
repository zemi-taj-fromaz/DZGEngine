#pragma once

#include <fstream>
#include <vulkan/vulkan.h>

#include "app/app.h"
#include "PipelineData.h"

void build_pipeline(dzg* app, PipelineData* pipelineData);// (std::string vertShaderName, std::string fragShaderName, VkDevice device, VkPipelineLayout pipelineLayout, VkRenderPass pass, VkExtent2D extent, VkPolygonMode polygonMode, VkPrimitiveTopology topology);
