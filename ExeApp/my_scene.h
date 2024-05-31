#pragma once

#include "scene.h"
#include "BufferObject.h"
#include "app/app.h"


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

		//1) Samplers
		auto texSampler = std::make_shared<sampler>();
		SamplersVec.push_back(texSampler);

		//2) Textures
		std::shared_ptr<texture> tex = std::make_shared<texture>("statue.jpg");
		TexturesVec.push_back(tex);


		//3) Bindings
		BindingInfo bInfo1(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,  VK_SHADER_STAGE_VERTEX_BIT);
		BindingInfo bInfo2(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,  VK_SHADER_STAGE_FRAGMENT_BIT);

		//4) Buffers
		auto bufferData = std::make_shared<BufferData>(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(UniformBufferObject), 
			[](dzg* app, void* bufferMapped) { UniformBufferObject::bufferUpdateFunction(app, bufferMapped); });

		auto imageData = std::make_shared<BufferData>(tex, texSampler);

		BufferDataVec.push_back(bufferData);
		BufferDataVec.push_back(imageData);

		//5) Descriptor set Layouts
		std::shared_ptr<DescriptorSetLayout> dsl = std::make_shared<DescriptorSetLayout>();
		dsl->bindings.push_back(bInfo1);
		dsl->bindings.push_back(bInfo2);
		DescriptorSetLayoutVec.push_back(dsl);

		//6) Pipelines
		std::shared_ptr<PipelineData> pData = std::make_shared<PipelineData>();
		pData->shaderNames = std::array<std::string, 2>({ "TriangleShader.vert", "TriangleShader.frag" });
		pData->pDescriptorSetLayout = dsl;
		pipelineDataVec.push_back(pData);

		//7) Descriptors
		std::shared_ptr<DescriptorSet> ds = std::make_shared<DescriptorSet>();
		ds->layout = pData->pDescriptorSetLayout;
		ds->bufferDataVec.push_back(std::shared_ptr<BufferData>(bufferData));
		ds->bufferDataVec.push_back(std::shared_ptr<BufferData>(imageData));
		DescriptorSetVec.push_back(ds);

		//8) Mesh
		Mesh m = Mesh(MeshType::Quad);
		m.DescriptorSetVec = DescriptorSetVec;
		m.PipelineData = pData;
		MeshVec.push_back(m);
	}
};

