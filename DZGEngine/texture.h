#pragma once

#include <vulkan/vulkan.h>
#include <string>

struct Texture
{
	Texture(const std::string& Name) : Name(Name) {}

	std::string Name;
	VkImage textureImage;
	VkImageView textureImageView;
	VkDeviceMemory TextureImageMemory;
	int width; int height;
};

