#pragma once

#include <vulkan/vulkan.h>
#include <string>

struct texture
{
	std::string Name;
	VkImage textureImage;
	VkImageView textureImageView;
	VkDeviceMemory TextureImageMemory;
};

