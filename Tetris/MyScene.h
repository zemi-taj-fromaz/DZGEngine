#pragma once

#include <app/app.h>

#include "Scene.h"
#include "BufferObject.h"

#include <vendor/imgui/imgui.h>
#include <vendor/imgui/imgui_impl_glfw.h>
#include <vendor/imgui/imgui_impl_vulkan.h>

#include <random>

#include "Tetrominoes.h"

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
	MyScene(uint32_t width, uint32_t height);

	virtual void scene_update(float totalTime, float deltaTime, dzg* app) override;
	virtual void inputPolling(GLFWwindow* window, float deltaTime) override;
	virtual void drawImgui(dzg* app, VkCommandBuffer commandbuffer) override;
	virtual std::unique_ptr<Camera> GetCamera(dzg* app) override;

private:
	void restartScene();

	bool CollisionTest(dzg* app);

	bool m_GameOver = false;

	GameState gs = GameState::PLAY;

	Tetrominoes m_CurrentTetro;

	int m_Score = 0;
};

