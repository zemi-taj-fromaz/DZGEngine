#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include "PipelineData.h"
#include "Mesh.h"
#include "texture.h"
#include "Sampler.h"

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
	VkClearValue clearColor = { {0.06f, 0.06f, 0.06f, 1.0f} };
	long fontHeight = 0;

	std::shared_ptr<Mesh> Player;

	Glyph glyphs[127];
	std::shared_ptr<Texture> TextureAtlas;

	//std::vector<Mesh> MeshVec;

	virtual void scene_update(float totalTime, float deltaTime, dzg* app) {}
	virtual void inputPolling(GLFWwindow* window, float deltaTime) {}
	virtual void drawImgui(dzg* app, VkCommandBuffer commandbuffer) {
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		ImGuiWindowFlags window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoBackground;
		window_flags |= ImGuiWindowFlags_NoTitleBar;

		ImVec2 windowSize{ 250, 350 };
		ImGui::SetNextWindowSize(windowSize);
		// etc.
		bool open_ptr = true;
		ImGui::Begin("I'm a Window!", &open_ptr, window_flags);

		ImFont* font = ImGui::GetFont();
		font->Scale = 2;

		// font->Color
		ImGui::PushFont(font);
		//imgui commands

		std::string score = "Score : " + std::to_string(0);
		std::string enemies_left = "Deer left : " + std::to_string(0);
		ImGui::Text(score.c_str());
		ImGui::Text(enemies_left.c_str());

		ImGui::PopFont();

		ImGui::End();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandbuffer);
	}
};




