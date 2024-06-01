#include "ParticleSystem.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

#include <random>

void Particle::update(float totalTime, float deltaTime, dzg* app)
{
	if (this->LifeRemaining <= 0.0f)
	{
		this->Active = false;
		return;
	}

	this->LifeRemaining -= deltaTime;
	this->offsetPosition(glm::vec3(this->Velocity * deltaTime, 0.0f));
	this->Rotation += 0.01f * deltaTime;
	//TODO scale and rotation

	float life = this->LifeRemaining / this->LifeTime;
	glm::vec4 color = glm::lerp(this->ColorEnd, this->ColorBegin, life);
	//	color.a = color.a * life; //TODO turn on blending
	this->Color = color;
	this->Size = glm::lerp(this->SizeEnd, this->SizeBegin, life);

	//TODO adjust model matrix and color
}

void Particle::render(VkCommandBuffer commandBuffer, int instanceIndex, int currFrame)
{
	if (!this->Active) return;
	Mesh::render(commandBuffer, instanceIndex, currFrame);
	//vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, this->PipelineData->pipeline);

	//VkBuffer vertexBuffers[] = { this->VertexBuffer };
	//VkDeviceSize offsets[] = { 0 };
	//vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
	//vkCmdBindIndexBuffer(commandBuffer, this->IndexBuffer, 0, VK_INDEX_TYPE_UINT16);

	//for (int j = 0; j < this->DescriptorSetVec.size(); ++j)
	//{
	//	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, this->PipelineData->PipelineLayout, j, 1, &this->DescriptorSetVec[j]->sets[currFrame], 0, nullptr);
	//}
	//vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(this->Indices.size()), 1, 0, 0, instanceIndex);
}

ParticleSystem::ParticleSystem()
{
	m_ParticlePool.resize(100, std::make_shared<Particle>());
}

void ParticleSystem::Emit(const ParticleProps& particleProps)
{
	static std::random_device dev;
	static std::mt19937 rng(dev());

	static std::uniform_real_distribution<float> RandFloat(0.0f, 1.0f); // distribution in range [1, 6]

	float angle = RandFloat(rng);

	auto& particle = m_ParticlePool[m_PoolIndex];
	particle->Active = true;
	particle->Active = true;
	particle->offsetPosition(glm::vec3(particleProps.Position,0.0f));
	particle->Rotation = angle * 2.0f * glm::pi<float>();

	// Velocity
	particle->Velocity = particleProps.Velocity;
	particle->Velocity.x += particleProps.VelocityVariation.x * (RandFloat(rng) - 0.5f);
	particle->Velocity.y += particleProps.VelocityVariation.y * (RandFloat(rng) - 0.5f);

	// Color
	particle->ColorBegin = particleProps.ColorBegin;
	particle->ColorEnd = particleProps.ColorEnd;

	// Size
	particle->SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (RandFloat(rng) - 0.5f);
	particle->SizeEnd = particleProps.SizeEnd;

	// Life
	particle->LifeTime = particleProps.LifeTime;
	particle->LifeRemaining = particleProps.LifeTime;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
}

void ParticleSystem::update(float totalTime, float deltaTime, dzg* app)
{
	for (auto& particle : m_ParticlePool)
	{
		if (!particle->Active)
			continue;

		particle->update(totalTime, deltaTime, app);
	}
}