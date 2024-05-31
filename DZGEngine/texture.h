#pragma once

#include <vulkan/vulkan.h>
#include <string>

struct texture
{
	texture(const std::string& Name) : Name(Name) {}

	std::string Name;
	VkImage textureImage;
	VkImageView textureImageView;
	VkDeviceMemory TextureImageMemory;
};

