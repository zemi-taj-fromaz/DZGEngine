#pragma once

#include <app/app.h>

#include "Scene.h"
#include "BufferObject.h"
#include "Pillar.h"
#include "ParticleSystem.h"

#include <vendor/imgui/imgui.h>
#include <vendor/imgui/imgui_impl_glfw.h>
#include <vendor/imgui/imgui_impl_vulkan.h>

#include <random>

using PillarsVec_t = std::vector<std::shared_ptr<Mesh>>;

enum GameState
{
	UNKNOWN = 0,
	PREPARE = 1,
	PLAY = 2,
	OVER = 3
};

class MyScene : public Scene
{
public:
	MyScene();
	MyScene(uint32_t, uint32_t);

	virtual void scene_update(float totalTime, float deltaTime, dzg* app) override;
	virtual void inputPolling(GLFWwindow* window, float deltaTime) override;
	virtual void drawImgui(dzg* app, VkCommandBuffer commandbuffer) override;
	virtual std::unique_ptr<Camera> GetCamera(dzg* app) override;

private:

	void restartScene();

	bool CollisionTest(dzg* app);
	bool CheckBorders(dzg* app);
	bool CheckPillars();

	ParticleProps m_EngineParticle;
	std::unique_ptr<ParticleSystem> m_ParticleSystem;
	PillarsVec_t m_PillarsVec;

	std::shared_ptr<Mesh> m_Player;

	GameState gs = GameState::PLAY;

	int m_Score = 0;
};

