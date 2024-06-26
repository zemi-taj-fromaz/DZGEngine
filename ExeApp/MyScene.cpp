#include "MyScene.h"

#include <windows.h>
//#include "vendor/imgui/imgui.h"
//#include "vendor/imgui/imgui_impl_glfw.h"
//#include "vendor/imgui/imgui_impl_vulkan.h"

MyScene::MyScene()
{
	this->clearColor = { {0.1f, 0.06f, 0.06f, 1.0f}};
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
	Player->offsetPosition(glm::vec3(0.5f, 0.5f, 0.0f));

	m_Player = Player;

	MeshVec.push_back(m_Player);

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
	m_EngineParticle.Velocity = { -2.0f, 0.0f },
	m_EngineParticle.VelocityVariation = { 3.0f, 1.0f };
	m_EngineParticle.SizeBegin = 0.3f, m_EngineParticle.SizeEnd = 0.0f, m_EngineParticle.SizeVariation = 0.3f;
	m_EngineParticle.ColorBegin = { 254.0f / 255.0f, 10.0f / 255.0f, 10.0f / 255.0f, 1.0f };
	m_EngineParticle.ColorEnd = { 254.0f / 255.0f, 212.0f / 255.0f, 50.0f / 255.0f , 1.0f };
	m_EngineParticle.LifeTime = 1.0f;

}

std::wstring ConvertToWideString(const std::string& narrowStr) {
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, narrowStr.c_str(), (int)narrowStr.size(), NULL, 0);
	std::wstring wideStr(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, narrowStr.c_str(), (int)narrowStr.size(), &wideStr[0], size_needed);
	return wideStr;
}

void MyScene::scene_update(float totalTime, float deltaTime, dzg* app) 
{
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
		return;
	}
}

void MyScene::restartScene()
{
	//Todo - extract this to  a separate function
		
	m_Score = 0;
	gs = GameState::PLAY;
	float offset = 8.0f;
	for (int i = 3; i < 11; i++)
	{
		m_PillarsVec[i - 3]->setPosition(glm::vec3(offset * i, 0.0f, 0.0f));
	}
	m_Player->setPosition({ 0.0f, 0.0f, 0.0f });
}

void MyScene::inputPolling(GLFWwindow* window, float deltaTime) 
{

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

	float playerSpeed = 6.0f;
	//float gravity = 2.0f;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		this->Player->offsetPosition(glm::vec3(0.0f, -playerSpeed * deltaTime, 0.0f));
		auto rot = glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		this->Player->setRotation(rot);

		m_EngineParticle.Position = glm::vec2(this->Player->Position) + glm::vec2(-0.5f, 1.0f);
		m_EngineParticle.Velocity = glm::vec2(dynamic_cast<Pillar*>(m_PillarsVec[0].get())->Speed, 6.0f);
		this->m_ParticleSystem->Emit(m_EngineParticle);
	}
	else
	{
		auto rot = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		this->Player->setRotation(rot);
		this->Player->offsetPosition(glm::vec3(0.0f, playerSpeed * deltaTime, 0.0f));
	}
}

bool MyScene::CollisionTest(dzg* app)
{
	return CheckBorders(app) || CheckPillars();
}

bool MyScene::CheckBorders(dzg* app)
{
	return  app->camHeight <= this->Player->Position.y +1.0f || this->Player->Position.y <= app->camHeight * -1.0f; // 1.0f is player size
}

bool MyScene::CheckPillars()
{
	for (auto& pillar : m_PillarsVec)
	{
		if (pillar->Position.x <= 1.0f && pillar->Position.x >= -2.0f) //TODO add explanations/remove hardcoding for these fixed variables
		{

			if (std::abs(pillar->Position.x) < 0.05f) m_Score++;

			bool Nocollision = (pillar->Position.z < this->Player->Position.y) && (this->Player->Position.y + 1.0f < pillar->Position.w);

			if (!Nocollision) {
				return true;
			}
		}
	}

	return false;
}

void MyScene::drawImgui(dzg* app, VkCommandBuffer commandbuffer)
{	if(gs == GameState::PLAY)
	{
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		ImGuiWindowFlags window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoBackground;
		window_flags |= ImGuiWindowFlags_NoTitleBar;

		ImVec2 windowSize{ 250, 350 };
		ImGui::SetNextWindowSize(windowSize);

		ImGui::SetNextWindowPos(ImVec2(app->GetWidth() / 1.2, app->GetHeight() / 10));

		//ImGui::SetNextWindowPos(ImVec2(0, 0));

		// etc.
		bool open_ptr = true;
		ImGui::Begin("I'm a Window!", &open_ptr, window_flags);

		ImFont* font = ImGui::GetFont();
		font->Scale = 2;

		// font->Color
		ImGui::PushFont(font);
		//imgui commands

		std::string score = "Score : " + std::to_string(m_Score);
		ImGui::Text(score.c_str());

		ImGui::PopFont();

		ImGui::End();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandbuffer);
	}
	else if(gs == GameState::OVER)
	{
		ImGui_ImplVulkan_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		ImGuiWindowFlags window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoBackground;
		window_flags |= ImGuiWindowFlags_NoTitleBar;

		ImVec2 windowSize{ 270, 350 };
		ImGui::SetNextWindowSize(windowSize);
		ImGui::SetNextWindowPos(ImVec2(app->GetWidth() / 2, app->GetHeight() / 2));
		// etc.
		bool open_ptr = true;
		ImGui::Begin("I'm a Window!", &open_ptr, window_flags);

		ImFont* font = ImGui::GetFont();
		font->Scale = 2;

		// font->Color
		ImGui::PushFont(font);
		//imgui commands

		std::string score = "Your score : " + std::to_string(m_Score);
		ImGui::Text("GAME OVER");
		ImGui::Text(score.c_str());
		ImGui::Text("Press R to restart Game");

		ImGui::PopFont();

		ImGui::End();

		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandbuffer);
	}
}

std::unique_ptr<Camera> MyScene::GetCamera(dzg* app)
{
	float aspectRation = (float)this->WIDTH / (float)this->HEIGHT;

	float camHeight = 9.0f;
	app->camHeight = camHeight;
	float bottom = -camHeight;
	float top = camHeight;
	float left = bottom * aspectRation;
	float right = top * aspectRation;
	return std::make_unique<Camera>(left, right, bottom, top);
}
