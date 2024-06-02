#pragma once

#include <app/app.h>

#include "Scene.h"
#include "BufferObject.h"
#include "Pillar.h"
#include "ParticleSystem.h"

#include <random>

using PillarsVec_t = std::vector<std::shared_ptr<Mesh>>;

class MyScene : public Scene
{
public:
	MyScene();

	virtual void scene_update(float totalTime, float deltaTime, dzg* app) override;
	virtual void inputPolling(GLFWwindow* window, float deltaTime) override;

private:

	bool CollisionTest(dzg* app);
	bool CheckBorders(dzg* app);
	bool CheckPillars();

	ParticleProps m_EngineParticle;
	std::unique_ptr<ParticleSystem> m_ParticleSystem;
	PillarsVec_t m_PillarsVec;

	bool m_GameOver = false;
};

