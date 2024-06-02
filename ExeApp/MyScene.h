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
	MyScene()
	{
		//STEPS
		// 1) Textures
		// 2) Samplers
		// 3) Bindings
		// 4) Descriptor set layouts
		// 5) BufferData
		// 6) PipelineData
		// 7) Descriptor set
		// 8) Mesh

		//1) Samplers
		auto texSampler = std::make_shared<Sampler>();
		SamplersVec.push_back(texSampler);

		//2) Textures
		std::shared_ptr<Texture> tex = std::make_shared<Texture>("statue.jpg");
		TexturesVec.push_back(tex);


		//3) Bindings
		BindingInfo bInfoStorage(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, VK_SHADER_STAGE_VERTEX_BIT);
		BindingInfo bInfoUbo(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,  VK_SHADER_STAGE_VERTEX_BIT);
		BindingInfo bInfoSampler(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,  VK_SHADER_STAGE_FRAGMENT_BIT);


		//4) Buffers
		auto bufferDataUbo = std::make_shared<BufferData>(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(UniformBufferObject), 
			[](dzg* app, void* bufferMapped) { UniformBufferObject::bufferUpdateFunction(app, bufferMapped); });

		auto bufferDataStorage = std::make_shared<BufferData>(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, sizeof(ObjectDataBuffer) * 500,
			[](dzg* app, void* bufferMapped) { ObjectDataBuffer::bufferUpdateFunction(app, bufferMapped); });

		auto imageData = std::make_shared<BufferData>(tex, texSampler);

		BufferDataVec.push_back(bufferDataStorage);
		BufferDataVec.push_back(bufferDataUbo);
		BufferDataVec.push_back(imageData);

		//5) Descriptor set Layouts
		std::shared_ptr<DescriptorSetLayout> dsl = std::make_shared<DescriptorSetLayout>();
		dsl->bindings.push_back(bInfoUbo);
		dsl->bindings.push_back(bInfoSampler);

		std::shared_ptr<DescriptorSetLayout> dsl2 = std::make_shared<DescriptorSetLayout>();
		dsl2->bindings.push_back(bInfoStorage);

		DescriptorSetLayoutVec.push_back(dsl2);
		DescriptorSetLayoutVec.push_back(dsl);

		//6) Pipelines
		std::shared_ptr<PipelineData> pData = std::make_shared<PipelineData>();
		pData->shaderNames = std::array<std::string, 2>({ "TriangleShader.vert", "TriangleShader.frag" });
		pData->pDescriptorSetLayouts = DescriptorSetLayoutVec;

		pipelineDataVec.push_back(pData);

		//7) Descriptors
		std::shared_ptr<DescriptorSet> ds = std::make_shared<DescriptorSet>();
		ds->layout = dsl;
		ds->bufferDataVec.push_back(std::shared_ptr<BufferData>(bufferDataUbo));
		ds->bufferDataVec.push_back(std::shared_ptr<BufferData>(imageData));

		std::shared_ptr<DescriptorSet> ds2 = std::make_shared<DescriptorSet>();
		ds2->layout = dsl2;
		ds2->bufferDataVec.push_back(std::shared_ptr<BufferData>(bufferDataStorage));

		DescriptorSetVec.push_back(ds2);
		DescriptorSetVec.push_back(ds);

		//8) Mesh

		Player = std::make_shared<Mesh>(MeshType::Quad);
		Player->DescriptorSetVec = DescriptorSetVec;
		Player->PipelineData = pData;

		MeshVec.push_back(Player);

		float offset = 8.0f;
		for (int i = 0; i < 8; i++)
		{
			//TODO handle this dangling pointer
			Pillar* pillar = new Pillar();
			std::shared_ptr<Mesh> m2 = std::shared_ptr<Mesh>(pillar);
			m2->DescriptorSetVec = DescriptorSetVec;
			m2->PipelineData = pData;
			
			m2->setPosition(glm::vec3(offset*i,  0.0f, 0.0f));

			auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 1.0f));
			m2->setScale(scale);
			MeshVec.push_back(m2);
			m_PillarsVec.push_back(m2);
		}

		m_ParticleSystem = std::make_unique<ParticleSystem>();

		for (int i = 0; i < m_ParticleSystem->m_ParticlePool.size(); ++i)
		{
			m_ParticleSystem->m_ParticlePool[i]->DescriptorSetVec = DescriptorSetVec;
			m_ParticleSystem->m_ParticlePool[i]->PipelineData = pData;
			MeshVec.push_back(m_ParticleSystem->m_ParticlePool[i]);
		}
	//	MeshVec.insert(MeshVec.end(), m_ParticleSystem->m_ParticlePool.begin(), m_ParticleSystem->m_ParticlePool.end());
		//Mesh m = Mesh(MeshType::Quad);
		//m.DescriptorSetVec = DescriptorSetVec;
		//m.PipelineData = pData;

		//Mesh m2 = Mesh(MeshType::Quad);
		//m2.DescriptorSetVec = DescriptorSetVec;
		//m2.PipelineData = pData;
		//m2.offsetPosition(glm::vec3(0.0f, 5.0f, 0.0f));

		//MeshVec.push_back(m);
		//MeshVec.push_back(m2);

		m_EngineParticle.Position = { 0.0f, 0.0f };
		m_EngineParticle.Velocity = { -2.0f, 0.0f }, m_EngineParticle.VelocityVariation = { 3.0f, 1.0f };
		m_EngineParticle.SizeBegin = 0.3f, m_EngineParticle.SizeEnd = 0.0f, m_EngineParticle.SizeVariation = 0.3f;
		m_EngineParticle.ColorBegin = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
		m_EngineParticle.ColorEnd = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f , 1.0f };
		m_EngineParticle.LifeTime = 1.0f;

	}

	virtual void scene_update(float totalTime, float deltaTime, dzg* app) override
	{
		if (m_GameOver) return;

		for (int i = 0; i < MeshVec.size(); ++i)
		{
			MeshVec[i]->update(totalTime, deltaTime, app);
		}

		if (CollisionTest())
		{
			m_GameOver = true;
			return;
		}
	}

	virtual void inputPolling(GLFWwindow* window, float deltaTime) override
	{
		if (m_GameOver) return;

		float playerSpeed = 6.0f;
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    			this->Player->offsetPosition(glm::vec3(0.0f, -playerSpeed * deltaTime, 0.0f));

			m_EngineParticle.Position = glm::vec2(this->Player->Position) + glm::vec2(0.0f, 1.0f);
		//	m_EngineParticle.Position = m_Position + glm::vec2{ rotated.x, rotated.y };
		//	m_EngineParticle.Velocity.y = -playerSpeed * 0.2f;
			this->m_ParticleSystem->Emit(m_EngineParticle);
		}
		else
		{
			this->Player->offsetPosition(glm::vec3(0.0f, playerSpeed * deltaTime, 0.0f));
		}
	}

private:

	bool CollisionTest()
	{
		return CheckBorders() || CheckPillars();
	}

	bool CheckBorders()
	{
		//TODO - remove hardcoded 9 and say - app->camera width
		//TODO move impl to cpp file
		return 9.0f <= this->Player->Position.y || this->Player->Position.y <= -8.0f;
	}

	bool CheckPillars()
	{
		for (auto& pillar : m_PillarsVec)
		{
			if (pillar->Position.x <= 1.0f && pillar->Position.x >= -2.0f) //TODO add explanations/remove hardcoding for these fixed variables
			{

			//	std::cout << " PILLAR ZONE" << std::endl;

  				bool Nocollision = (pillar->Position.z < this->Player->Position.y) && (this->Player->Position.y + 1.0f < pillar->Position.w);

				if (!Nocollision) {
					std::cout << "COLISION" << std::endl;
					return true;
				}
			}

		}

		return false;
	}

	ParticleProps m_EngineParticle;
	std::unique_ptr<ParticleSystem> m_ParticleSystem;
	PillarsVec_t m_PillarsVec;

	bool m_GameOver = false;
};

