#include "MyScene.h"

#include <windows.h>
//#include "vendor/imgui/imgui.h"
//#include "vendor/imgui/imgui_impl_glfw.h"
//#include "vendor/imgui/imgui_impl_vulkan.h"

MyScene::MyScene(uint32_t width, uint32_t height) : Scene(width, height)
{
	this->clearColor = { {0.1f, 0.06f, 0.06f, 1.0f} };
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

	Field* field = nullptr;
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			field = new Field();
			std::shared_ptr<Mesh> m2 = std::shared_ptr<Mesh>(field);
			m2->DescriptorSetVec = DescriptorSetVec;
			m2->PipelineData = pDataPillar;
			m2->offsetPosition(glm::vec3(0.5f, 0.5f, 0.0f));
			m2->offsetPosition(glm::vec3(j * 1.1f, i * 1.1f, 0.0f));
			MeshVec.push_back(m2);
		}
	}
	field = nullptr;

	for (auto& pos : m_CurrentTetro.Positions)
	{
		dynamic_cast<Field*>(MeshVec[pos.first * 10 + pos.second].get())->Take();
	}

}

std::wstring ConvertToWideString(const std::string& narrowStr) {
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, narrowStr.c_str(), (int)narrowStr.size(), NULL, 0);
	std::wstring wideStr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, narrowStr.c_str(), (int)narrowStr.size(), &wideStr[0], size_needed);
	return wideStr;
}

void MyScene::scene_update(float totalTime, float deltaTime, dzg* app) 
{
	//for (auto& vec : MeshVec)
	//{
	//	vec->Color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	//}
	//if (m_CurrentTetro.type == TetrominoType::SQUARE)
	//{
	//	auto pos = m_CurrentTetro.Positions[0];
	//	MeshVec[pos.first * 10 + pos.second]->Color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
	//}

	return;
	// TODO Add sound
	//bool isit = PlaySound(TEXT("C:/Users/hrcol/Downloads/about_time.wav"), NULL, SND_ASYNC);
	//
	//if (isit == false)
	//{
	//	std::cout << " Sound not playing" << std::endl;
	//}

	if (gs == GameState::OVER) return;

	for (int i = 0; i < MeshVec.size(); ++i)
	{
		MeshVec[i]->update(totalTime, deltaTime, app);
	}

	if (CollisionTest(app))
	{
		gs = GameState::OVER;
		m_GameOver = true;
		return;
	}
}

void MyScene::restartScene()
{
	//Todo - extract this to  a separate function
		
	m_Score = 0;
	gs = GameState::PLAY;
	m_GameOver = false;
}

void MyScene::inputPolling(GLFWwindow* window, float deltaTime) 
{

	return;
	if (gs == GameState::OVER)
	{
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) 
		{
			auto app = reinterpret_cast<dzg*>(glfwGetWindowUserPointer(window));

			this->restartScene();

			app->initialTime = (float)glfwGetTime();
		}
		return;
	}

	//float playerSpeed = 6.0f;
	////float gravity = 2.0f;
	//if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
	//	this->Player->offsetPosition(glm::vec3(0.0f, -playerSpeed * deltaTime, 0.0f));
	//	auto rot = glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//	this->Player->setRotation(rot);

	//	m_EngineParticle.Position = glm::vec2(this->Player->Position) + glm::vec2(-0.5f, 1.0f);
	//	m_EngineParticle.Velocity = glm::vec2(dynamic_cast<Pillar*>(m_PillarsVec[0].get())->Speed, 6.0f);
	//	this->m_ParticleSystem->Emit(m_EngineParticle);
	//}
	//else
	//{
	//	auto rot = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//	this->Player->setRotation(rot);
	//	this->Player->offsetPosition(glm::vec3(0.0f, playerSpeed * deltaTime, 0.0f));
	//}
}

bool MyScene::CollisionTest(dzg* app)
{
	return false;
}


void MyScene::drawImgui(dzg* app, VkCommandBuffer commandbuffer)
{
}

std::unique_ptr<Camera> MyScene::GetCamera(dzg* app)
{
	return std::make_unique<Camera>(-0.5f, 15.0f * 1.1f + 0.5f, -0.5f, 20.0f * 1.1f+ 0.5f);
}

void MyScene::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case(GLFW_KEY_DOWN):
		{
			if (!m_CurrentTetro.processDown(this->MeshVec)) 
			{ 
				m_CurrentTetro = Tetromino(); 

				for (auto& pos : m_CurrentTetro.Positions)
				{
					dynamic_cast<Field*>(MeshVec[pos.first * 10 + pos.second].get())->Take();
				}
			}
			else if(m_CurrentTetro.IsAttached(this->MeshVec))
			{
				m_CurrentTetro = Tetromino();

				for (auto& pos : m_CurrentTetro.Positions)
				{
					dynamic_cast<Field*>(MeshVec[pos.first * 10 + pos.second].get())->Take();
				}
			}
			break;
		}
		case(GLFW_KEY_UP):
		{
			m_CurrentTetro.processUp(MeshVec);
			break;
		}
		case(GLFW_KEY_LEFT):
		{
			m_CurrentTetro.processLeft(MeshVec);
			break;
		}
		case(GLFW_KEY_RIGHT):
		{
			m_CurrentTetro.processRight(MeshVec);
			break;
		}
		}
	}
}


