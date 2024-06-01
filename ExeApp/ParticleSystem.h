#pragma once
#include "Mesh.h"
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

struct ParticleProps
{
	glm::vec2 Position;
	glm::vec2 Velocity, VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime = 1.0f;
};


struct Particle : public Mesh
{
	Particle() : Mesh(MeshType::Quad)
	{
	}
	glm::vec2 Velocity;
	glm::vec4 ColorBegin, ColorEnd;
	float RotationAngle = 0.0f;
	float SizeBegin, SizeEnd, Size;

	float LifeTime = 1.0f;
	float LifeRemaining = 1.0f;

	bool Active = false;

	virtual void update(float totalTime, float deltaTime, dzg* app) override;
	virtual void render(VkCommandBuffer commandBuffer, int instanceIndex, int currFrame) override;

};

using ParticlesVec_t = std::vector<std::shared_ptr<Particle>>;

class ParticleSystem
{
public:
	ParticleSystem();

	void Emit(const ParticleProps& particleProps);

	void update(float totalTime, float deltaTime, dzg* app);


	ParticlesVec_t m_ParticlePool;
private:
	uint32_t m_PoolIndex = 99;
};