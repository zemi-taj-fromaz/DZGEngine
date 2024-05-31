#pragma once
#include <glm/glm.hpp>

#include "scene.h"
#include "app/app.h"

struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

class my_scene : public scene
{
public:
	my_scene()
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
		auto texSampler = std::make_shared<sampler>();

		std::shared_ptr<texture> tex = std::make_shared<texture>();
		tex->Name = "statue.jpg";

		BindingInfo bInfo1(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,  VK_SHADER_STAGE_VERTEX_BIT);
		BindingInfo bInfo2(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,  VK_SHADER_STAGE_FRAGMENT_BIT);

		std::shared_ptr<BufferData> bufferData = std::make_shared<BufferData>();
		bufferData->type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		bufferData->usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
		bufferData->size = sizeof(UniformBufferObject);
		bufferData->bufferUpdateFunc = [](dzg* app, void* bufferMapped)
			{
				UniformBufferObject ubo{};
				ubo.model = glm::mat4(1.0f);
				ubo.view = app->camera->ViewMatrix;
				ubo.proj = app->camera->ProjectionMatrix;
				//	glm::translate(glm::mat4(1.0f), glm::vec3(0.2f, 0.0f, 0.0f)); //app->camera->ViewMatrix; //TODO - remove hardcoding
				//ubo.proj = glm::ortho(-1.f, 1.f, -1.f, 1.f, -1.0f, 1.0f);// app->camera->ProjectionMatrix;
			//	ubo.proj = glm::ortho(0.f, 800.f, 0.f, 600.f, -1.0f, 1.0f);// app->camera->ProjectionMatrix;
			//	ubo.proj[1][1] *= -1;
				memcpy(bufferMapped, &ubo, sizeof(ubo));
			};

		std::shared_ptr<BufferData> imageData = std::make_shared<BufferData>();
		imageData->type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	//	imageData->size = sizeof(UniformBufferObject);
		imageData->is_image = true;
		imageData->Texture = tex;
		imageData->TextureSampler = texSampler;

		std::shared_ptr<DescriptorSetLayout> dsl = std::make_shared<DescriptorSetLayout>();
		dsl->bindings.push_back(bInfo1);
		dsl->bindings.push_back(bInfo2);

		std::shared_ptr<PipelineData> pData = std::make_shared<PipelineData>();
		pData->shaderNames = std::array<std::string, 2>({ "TriangleShader.vert", "TriangleShader.frag" });
		pData->pDescriptorSetLayout = dsl;

		std::shared_ptr<DescriptorSet> ds = std::make_shared<DescriptorSet>();
		ds->layout = pData->pDescriptorSetLayout;
		ds->bufferDataVec.push_back(std::shared_ptr<BufferData>(bufferData));
		ds->bufferDataVec.push_back(std::shared_ptr<BufferData>(imageData));

		pipelineDataVec.push_back(pData);
		DescriptorSetLayoutVec.push_back(dsl);
		BufferDataVec.push_back(bufferData);
		BufferDataVec.push_back(imageData);
		DescriptorSetVec.push_back(ds);
		TexturesVec.push_back(tex);
		SamplersVec.push_back(texSampler);

		Mesh m = Mesh(MeshType::Quad);
		m.DescriptorSetVec = DescriptorSetVec;
		m.PipelineData = pData;
		MeshVec.push_back(m);
	}
};

