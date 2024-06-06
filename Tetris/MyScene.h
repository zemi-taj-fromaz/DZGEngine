#pragma once

#include <app/app.h>

#include "Scene.h"
#include "BufferObject.h"

#include <vendor/imgui/imgui.h>
#include <vendor/imgui/imgui_impl_glfw.h>
#include <vendor/imgui/imgui_impl_vulkan.h>

#include <random>
#include <deque>

#include "Tetromino.h"
#include "Field.h"


using FieldVec_t = std::vector<std::shared_ptr<Field>>;

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
	virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;

private:
	void restartScene();
	void clearNextFields()
	{
		for (int i = 0; i < m_NextTetrominoFieldVec.size(); i++)
		{
			dynamic_cast<Field*>(m_NextTetrominoFieldVec[i].get())->Free();
		}
	}

	void drawNextFields()
	{
		for (int i = 0; i < 3; ++i)
		{
			TetrominoType type = m_TetroQueue[i].type;
			glm::vec4 color = m_TetroQueue[i].Color;
			if (type == TetrominoType::I)
			{
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 0 * 4 + 2].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 1 * 4 + 2].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 2 * 4 + 2].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 3 * 4 + 2].get())->Take(color);
			}
			if (type == TetrominoType::O)
			{
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 1 * 4 + 1].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 1 * 4 + 2].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 2 * 4 + 1].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 2 * 4 + 2].get())->Take(color);
			}
			else if (type == TetrominoType::J)
			{
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 1 * 4 + 2].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 2 * 4 + 2].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 3 * 4 + 2].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 3 * 4 + 1].get())->Take(color);
			}
			else if (type == TetrominoType::L)
			{
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 1 * 4 + 2].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 2 * 4 + 2].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 3 * 4 + 2].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 3 * 4 + 3].get())->Take(color);
			}
			else if (type == TetrominoType::T)
			{
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 2 * 4 + 0].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 2 * 4 + 1].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 2 * 4 + 2].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 3 * 4 + 1].get())->Take(color);
			}
			else if (type == TetrominoType::Z)
			{
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 2 * 4 + 0].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 2 * 4 + 1].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 3 * 4 + 1].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 3 * 4 + 2].get())->Take(color);
			}
			else if (type == TetrominoType::S)
			{
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 2 * 4 + 2].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 2 * 4 + 3].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 3 * 4 + 1].get())->Take(color);
				dynamic_cast<Field*>(m_NextTetrominoFieldVec[i * 4 * 4 + 3 * 4 + 2].get())->Take(color);
			}
		}
	}

	bool m_GameOver = false;

	GameState gs = GameState::PREPARE;

	Tetromino m_CurrentTetro;
	std::deque<Tetromino> m_TetroQueue;
	std::vector<std::shared_ptr<Mesh>> m_NextTetrominoFieldVec;


	int m_Score = 0;
};

