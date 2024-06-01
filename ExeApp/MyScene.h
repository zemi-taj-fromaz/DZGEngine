#pragma once

#include <app/app.h>

#include "Scene.h"
#include "BufferObject.h"


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
		dsl->bindings.push_back(bInfoStorage);
		dsl->bindings.push_back(bInfoUbo);
		dsl->bindings.push_back(bInfoSampler);

		DescriptorSetLayoutVec.push_back(dsl);

		//6) Pipelines
		std::shared_ptr<PipelineData> pData = std::make_shared<PipelineData>();
		pData->shaderNames = std::array<std::string, 2>({ "TriangleShader.vert", "TriangleShader.frag" });
		pData->pDescriptorSetLayout = dsl;
		pipelineDataVec.push_back(pData);

		//7) Descriptors
		std::shared_ptr<DescriptorSet> ds = std::make_shared<DescriptorSet>();
		ds->layout = pData->pDescriptorSetLayout;
		ds->bufferDataVec.push_back(std::shared_ptr<BufferData>(bufferDataStorage));
		ds->bufferDataVec.push_back(std::shared_ptr<BufferData>(bufferDataUbo));
		ds->bufferDataVec.push_back(std::shared_ptr<BufferData>(imageData));
		DescriptorSetVec.push_back(ds);

		//8) Mesh
		Mesh m = Mesh(MeshType::Quad);
		m.DescriptorSetVec = DescriptorSetVec;
		m.PipelineData = pData;
		MeshVec.push_back(m);
	}
};

