#include "ParticleSystem.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

#include <random>
#include <iostream>

void Particle::update(float totalTime, float deltaTime, dzg* app)
{

	static std::random_device dev;
	static std::mt19937 rng(dev());

	static std::normal_distribution<float> RandFloat(1.0f, 0.5f); // distribution in range [1, 6]

	if (!this->Active) return;

	//std::cout << "Updating particle" << std::endl;

	if (this->LifeRemaining <= 0.0f)
	{
		this->Active = false;
		return;
	}

	float playerSpeed = 5.0f;

	offsetPosition(glm::vec3(-2.0f * deltaTime * RandFloat(rng), playerSpeed * deltaTime, 0.0f));

	this->LifeRemaining -= 1.0f *deltaTime;

	//std::cout << LifeRemaining << std::endl;

	this->RotationAngle += deltaTime;
	auto rot = glm::rotate(glm::mat4(1.0f), RotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
	this->setRotation(rot);
	//TODO scale and rotation

	float life = this->LifeRemaining / this->LifeTime;
	glm::vec4 color = glm::lerp(this->ColorEnd, this->ColorBegin, life);
	//	color.a = color.a * life; //TODO turn on blending
	this->Color = color;
	this->Size = glm::lerp(this->SizeEnd, this->SizeBegin, life);
	auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(this->Size, this->Size, 1.0f));
	this->setScale(scale);

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
	for (int i = 0; i < 100; i++)
	{
		std::shared_ptr<Particle> particle = std::make_shared<Particle>();
		m_ParticlePool.push_back(particle);

	}
}

void ParticleSystem::Emit(const ParticleProps& particleProps)
{
	static std::random_device dev;
	static std::mt19937 rng(dev());

	static std::uniform_real_distribution<float> RandFloat(0.0f, 1.0f); // distribution in range [1, 6]

	float angle = RandFloat(rng);

	auto& particle = m_ParticlePool[m_PoolIndex];
	particle->Active = true;
	particle->setPosition(glm::vec3(particleProps.Position,0.0f));
	particle->RotationAngle = angle * 2.0f * glm::pi<float>();

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