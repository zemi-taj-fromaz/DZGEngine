#pragma once

#include <vulkan/vulkan.h>

struct Sampler
{
    Sampler()
	{
        SamplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        SamplerInfo.magFilter = VK_FILTER_LINEAR;
        SamplerInfo.minFilter = VK_FILTER_LINEAR;
        SamplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        SamplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        SamplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        //SamplerInfo.anisotropyEnable = VK_FALSE;
      //  S/samplerInfo.maxAnisotropy = 1.0f;
        SamplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        SamplerInfo.unnormalizedCoordinates = VK_FALSE;
        SamplerInfo.compareEnable = VK_FALSE;
        SamplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
        SamplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        SamplerInfo.mipLodBias = 0.0f;
        SamplerInfo.minLod = 0.0f;
        SamplerInfo.maxLod = 0.0f;
	}
    Sampler(VkSamplerCreateInfo samplerInfo) : SamplerInfo(samplerInfo) {}

	VkSampler vkSampler;
    VkSamplerCreateInfo SamplerInfo{};
};

