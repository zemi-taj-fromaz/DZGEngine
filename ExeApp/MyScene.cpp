#include "MyScene.h"

//#include "vendor/imgui/imgui.h"
//#include "vendor/imgui/imgui_impl_glfw.h"
//#include "vendor/imgui/imgui_impl_vulkan.h"

MyScene::MyScene()
{
	this->clearColor = { {1.00f, 0.06f, 0.06f, 1.0f}};
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
	std::shared_ptr<Texture> tex = std::make_shared<Texture>("jetpack.png");
	TexturesVec.push_back(tex);

	//TextureAtlas = std::make_shared<Texture>("AtariClassic - gry3.ttf");

	//3) Bindings
	BindingInfo bInfoStorage(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, VK_SHADER_STAGE_VERTEX_BIT);
	BindingInfo bInfoUbo(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT);
	BindingInfo bInfoResolution(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_FRAGMENT_BIT);
	BindingInfo bInfoSampler(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_FRAGMENT_BIT);


	//4) Buffers
	auto bufferDataUbo = std::make_shared<BufferData>(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(UniformBufferObject),
		[](dzg* app, void* bufferMapped) { UniformBufferObject::bufferUpdateFunction(app, bufferMapped); });

	auto bufferDataRes = std::make_shared<BufferData>(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(ResolutionBufferObject),
		[](dzg* app, void* bufferMapped) { ResolutionBufferObject::bufferUpdateFunction(app, bufferMapped); });

	auto bufferDataStorage = std::make_shared<BufferData>(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, sizeof(ObjectDataBuffer) * 500,
		[](dzg* app, void* bufferMapped) { ObjectDataBuffer::bufferUpdateFunction(app, bufferMapped); });

	auto imageData = std::make_shared<BufferData>(tex, texSampler);

	BufferDataVec.push_back(bufferDataStorage);
	BufferDataVec.push_back(bufferDataUbo);
	BufferDataVec.push_back(imageData);
	BufferDataVec.push_back(bufferDataRes);

	//5) Descriptor set Layouts
	std::shared_ptr<DescriptorSetLayout> dsl = std::make_shared<DescriptorSetLayout>();
	dsl->bindings.push_back(bInfoUbo);
	dsl->bindings.push_back(bInfoSampler);
	dsl->bindings.push_back(bInfoResolution);

	std::shared_ptr<DescriptorSetLayout> dsl2 = std::make_shared<DescriptorSetLayout>();
	dsl2->bindings.push_back(bInfoStorage);

	DescriptorSetLayoutVec.push_back(dsl2);
	DescriptorSetLayoutVec.push_back(dsl);

	//6) Pipelines
	std::shared_ptr<PipelineData> pData = std::make_shared<PipelineData>();
	pData->shaderNames = std::array<std::string, 2>({ "TriangleShader.vert", "TriangleShader.frag" });
	pData->pDescriptorSetLayouts = DescriptorSetLayoutVec;

	std::shared_ptr<PipelineData> pDataPillar = std::make_shared<PipelineData>();
	pDataPillar->shaderNames = std::array<std::string, 2>({ "PillarShader.vert", "PillarShader.frag" });
	pDataPillar->pDescriptorSetLayouts = DescriptorSetLayoutVec;

	pipelineDataVec.push_back(pData);
	pipelineDataVec.push_back(pDataPillar);

	//7) Descriptors
	std::shared_ptr<DescriptorSet> ds = std::make_shared<DescriptorSet>();
	ds->layout = dsl;
	ds->bufferDataVec.push_back(std::shared_ptr<BufferData>(bufferDataUbo));
	ds->bufferDataVec.push_back(std::shared_ptr<BufferData>(imageData));
	ds->bufferDataVec.push_back(std::shared_ptr<BufferData>(bufferDataRes));

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
	Pillar* pillar = nullptr;
	for (int i = 3; i < 11; i++)
	{
		pillar = new Pillar();
		std::shared_ptr<Mesh> m2 = std::shared_ptr<Mesh>(pillar);
		m2->DescriptorSetVec = DescriptorSetVec;
		m2->PipelineData = pDataPillar;

		m2->setPosition(glm::vec3(offset * i, 0.0f, 0.0f));

		auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 1.0f));
		m2->setScale(scale);
		MeshVec.push_back(m2);
		m_PillarsVec.push_back(m2);
	}
	pillar = nullptr;

	m_ParticleSystem = std::make_unique<ParticleSystem>();

	for (int i = 0; i < m_ParticleSystem->m_ParticlePool.size(); ++i)
	{
		m_ParticleSystem->m_ParticlePool[i]->DescriptorSetVec = DescriptorSetVec;
		m_ParticleSystem->m_ParticlePool[i]->PipelineData = pDataPillar;
		MeshVec.push_back(m_ParticleSystem->m_ParticlePool[i]);
	}

	m_EngineParticle.Position = { 0.0f, 0.0f };
	m_EngineParticle.Velocity = { -2.0f, 0.0f }, m_EngineParticle.VelocityVariation = { 3.0f, 1.0f };
	m_EngineParticle.SizeBegin = 0.3f, m_EngineParticle.SizeEnd = 0.0f, m_EngineParticle.SizeVariation = 0.3f;
	m_EngineParticle.ColorBegin = { 254.0f / 255.0f, 10.0f / 255.0f, 10.0f / 255.0f, 1.0f };
	m_EngineParticle.ColorEnd = { 254.0f / 255.0f, 212.0f / 255.0f, 50.0f / 255.0f , 1.0f };
	m_EngineParticle.LifeTime = 1.0f;

}


void MyScene::scene_update(float totalTime, float deltaTime, dzg* app) 
{
	if (m_GameOver) return;

	for (int i = 0; i < MeshVec.size(); ++i)
	{
		MeshVec[i]->update(totalTime, deltaTime, app);
	}

	if (CollisionTest(app))
	{
		m_GameOver = true;
		return;
	}
}

void MyScene::inputPolling(GLFWwindow* window, float deltaTime) 
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

bool MyScene::CollisionTest(dzg* app)
{
	return CheckBorders(app) || CheckPillars();
}

bool MyScene::CheckBorders(dzg* app)
{
	return  app->camHeight <= this->Player->Position.y || this->Player->Position.y - 1.0f <= app->camHeight * -1.0f; // 1.0f is player size
}

bool MyScene::CheckPillars()
{
	for (auto& pillar : m_PillarsVec)
	{
		if (pillar->Position.x <= 1.0f && pillar->Position.x >= -2.0f) //TODO add explanations/remove hardcoding for these fixed variables
		{

			bool Nocollision = (pillar->Position.z < this->Player->Position.y) && (this->Player->Position.y + 1.0f < pillar->Position.w);

			if (!Nocollision) {
				return true;
			}
		}
	}

	return false;
}
