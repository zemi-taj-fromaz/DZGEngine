#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include "PipelineData.h"
#include "Mesh.h"
#include "texture.h"
#include "Sampler.h"
#include "Camera.h"

#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_vulkan.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using PipelineDataVec_t = std::vector<std::shared_ptr<PipelineData>>;
using DescriptorSetLayoutVec_t = std::vector<std::shared_ptr<DescriptorSetLayout>>;
using DescriptorSetVec_t = std::vector<std::shared_ptr<DescriptorSet>>;
using BufferDataVec_t = std::vector<std::shared_ptr<BufferData>>;
using BufferDataVec_t = std::vector<std::shared_ptr<BufferData>>;
using TextureVec_t = std::vector<std::shared_ptr<Texture>>;
using SamplersVec_t = std::vector<std::shared_ptr<Sampler>>;
using MeshVec_t = std::vector<std::shared_ptr<Mesh>>;

class dzg;

struct Glyph
{
	glm::vec2 offset;
	glm::vec2 advance;
	glm::vec2 textureCoords;
	glm::vec2 size;
};

class Scene
{
public:
	Scene() : WIDTH(1280u), HEIGHT(720u) {}
	Scene(uint32_t width, uint32_t height) : WIDTH(width), HEIGHT(height) {}
	uint32_t WIDTH;
	uint32_t HEIGHT;
	PipelineDataVec_t pipelineDataVec;
	DescriptorSetLayoutVec_t DescriptorSetLayoutVec;
	DescriptorSetVec_t DescriptorSetVec;
	BufferDataVec_t BufferDataVec;
	TextureVec_t TexturesVec;
	SamplersVec_t SamplersVec;
	MeshVec_t MeshVec;
	VkClearValue clearColor = { {0.06f, 0.06f, 0.06f, 1.0f} };
	long fontHeight = 0;

	std::shared_ptr<Mesh> Player;

	Glyph glyphs[127];
	std::shared_ptr<Texture> TextureAtlas;

	//std::vector<Mesh> MeshVec;

	virtual void scene_update(float totalTime, float deltaTime, dzg* app) {}
	virtual void inputPolling(GLFWwindow* window, float deltaTime) {}
	virtual void drawImgui(dzg* app, VkCommandBuffer commandbuffer) {}
	virtual std::unique_ptr<Camera> GetCamera(dzg* app) 
	{
		float aspectRation = (float)this->WIDTH / (float)this->HEIGHT;
		return std::make_unique<Camera>(0, WIDTH, 0, HEIGHT);
	}
};




