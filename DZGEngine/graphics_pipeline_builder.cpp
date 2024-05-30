#include "graphics_pipeline_builder.h"
#include "vertex_buffer.h"
#include "app/shader_load.h"

#include <vector>

void build_pipeline(dzg* app, PipelineData* pipelineData)//(std::string vertShaderName, std::string fragShaderName, VkDevice device, VkPipelineLayout pipelineLayout, VkRenderPass pass, VkExtent2D extent, VkPolygonMode polygonMode, VkPrimitiveTopology topology)
{
	/*
		TODO
		GraphicsPipelineData
	*/
	VkPrimitiveTopology Topology = pipelineData->Topology;
	VkPolygonMode PolygonMode = pipelineData->PolygonMode;
	VkCullModeFlags cullMode = pipelineData->cullMode;
	std::array<std::string, 2> shaderNames = pipelineData->shaderNames;

	float viewPortWidth = (float)app->core.swapChainExtent.width;
	float viewPortHeight = (float)app->core.swapChainExtent.width;
	VkExtent2D extent = app->core.swapChainExtent;
	VkRenderPass renderPass = app->renderPass;
	VkDevice& device = app->core.device;

	VkVertexInputBindingDescription bindingDescription;
	std::array<VkVertexInputAttributeDescription,3> attributeDescriptions;

	bindingDescription = Vertex::getBindingDescription();
	attributeDescriptions = Vertex::getAttributeDescriptions();
	
	size_t dotPosition = shaderNames[0].find_last_of('.');
	shaderNames[0] = shaderNames[0].substr(0, dotPosition) + shaderNames[0].substr(dotPosition + 1) + ".spv";

	dotPosition = shaderNames[1].find_last_of('.');
	shaderNames[1] = shaderNames[1].substr(0, dotPosition) + shaderNames[1].substr(dotPosition + 1) + ".spv";

	auto vertShaderCode = readFile("../resources/shaders/" + shaderNames[0]);
	auto fragShaderCode = readFile("../resources/shaders/" + shaderNames[1]);

	VkShaderModule vertShaderModule = app->createShaderModule(vertShaderCode);
	VkShaderModule fragShaderModule = app->createShaderModule(fragShaderCode);

	VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
	vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertShaderStageInfo.module = vertShaderModule;
	vertShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
	fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragShaderStageInfo.module = fragShaderModule;
	fragShaderStageInfo.pName = "main";

	VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

	VkPipelineVertexInputStateCreateInfo vertexInputInfo{}; //SEPARATE FUNCTION?
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInputInfo.vertexBindingDescriptionCount = 1;
	vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

	VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.pNext = nullptr;
	inputAssembly.topology = Topology;
	inputAssembly.primitiveRestartEnable = VK_FALSE; // TODO - when enabling index draws

	VkPipelineRasterizationStateCreateInfo rasterizer{};
	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;

	rasterizer.polygonMode = PolygonMode;
	rasterizer.lineWidth = 1.0f;
	rasterizer.cullMode = cullMode;
	rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;
	rasterizer.depthBiasConstantFactor = 0.0f; // Optional
	rasterizer.depthBiasClamp = 0.0f; // Optional
	rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;
	colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional
	colorBlendAttachment.blendEnable = VK_TRUE;
	colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

	VkPipelineColorBlendStateCreateInfo colorBlending{};
	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
	colorBlending.attachmentCount = 1;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.blendConstants[0] = 0.0f; // Optional
	colorBlending.blendConstants[1] = 0.0f; // Optional
	colorBlending.blendConstants[2] = 0.0f; // Optional
	colorBlending.blendConstants[3] = 0.0f; // Optional

	VkPipelineMultisampleStateCreateInfo multisampling{};
	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	multisampling.minSampleShading = 1.0f; // Optional
	multisampling.pSampleMask = nullptr; // Optional
	multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
	multisampling.alphaToOneEnable = VK_FALSE; // Optional



	//VkPipelineDepthStencilStateCreateInfo depthStencil{};
	//depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	//depthStencil.depthTestEnable = this->DepthTest;
	//depthStencil.depthWriteEnable = this->DepthTest;
	//depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
	//depthStencil.depthBoundsTestEnable = VK_FALSE;
	//depthStencil.minDepthBounds = 0.0f; // Optional
	//depthStencil.maxDepthBounds = 1.0f; // Optional
	//depthStencil.stencilTestEnable = VK_FALSE;
	//depthStencil.front = {}; // Optional
	//depthStencil.back = {}; // Optional

	//if (Skybox)
	//{
	//	depthStencil.depthTestEnable = VK_TRUE;
	//	depthStencil.depthWriteEnable = VK_TRUE;
	//	depthStencil.depthCompareOp = VK_COMPARE_OP_EQUAL;
	//	depthStencil.depthBoundsTestEnable = VK_FALSE;
	//	depthStencil.stencilTestEnable = VK_FALSE;
	//}

	std::vector<VkDynamicState> dynamicStates = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};

	VkPipelineDynamicStateCreateInfo dynamicState{};
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
	dynamicState.pDynamicStates = dynamicStates.data();

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = viewPortWidth;
	viewport.height = viewPortHeight;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;

	VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = extent;

	VkPipelineViewportStateCreateInfo viewportState{};
	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.viewportCount = 1;
	viewportState.pViewports = &viewport;
	viewportState.scissorCount = 1;
	viewportState.pScissors = &scissor;

	//VkPipeline newPipeline;
	//if (shaderStages.size() == 1)
	//{
	//	VkComputePipelineCreateInfo computePipelineInfo{};
	//	computePipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
	//	computePipelineInfo.layout = PipelineLayout;
	//	computePipelineInfo.stage = shaderStages[0];

	//	if (vkCreateComputePipelines(Device, VK_NULL_HANDLE, 1, &computePipelineInfo, nullptr, &newPipeline) != VK_SUCCESS) {
	//		throw std::runtime_error("failed to create compute pipeline!");
	//	}

	//	return newPipeline;
	//}

	VkGraphicsPipelineCreateInfo pipelineInfo{};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2; //TODO update when adding compute shaders
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssembly; 
	pipelineInfo.pViewportState = &viewportState; 
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pDepthStencilState = nullptr; //TODO when adding depth
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDynamicState = &dynamicState;
	pipelineInfo.layout = pipelineData->PipelineLayout;
	pipelineInfo.renderPass = renderPass;
	pipelineInfo.subpass = 0; //TODO when adding subpasses
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
	pipelineInfo.basePipelineIndex = -1; // Optional

	if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &(pipelineData->pipeline)) != VK_SUCCESS) {
		throw std::runtime_error("failed to create graphics pipeline!");
	}

	vkDestroyShaderModule(app->core.device, fragShaderModule, nullptr);
	vkDestroyShaderModule(app->core.device, vertShaderModule, nullptr);
}

//
//bool PipelineBuilder::compile_shader(std::string sourcePath, std::vector<char>& spirvCode)
//{
//	std::filesystem::path currentDir = std::filesystem::current_path().parent_path();
//
//	// Initialize the shader compiler
//	//shaderc::Compiler compiler;
//	//shaderc::CompileOptions options;
//
//	size_t dotPosition = sourcePath.find_last_of('.');
//	sourcePath = sourcePath.substr(0, dotPosition) + sourcePath.substr(dotPosition + 1) + ".spv";
//
//	// Load the shader source code from file
//	std::ifstream file(currentDir.string() + SHADER_PATH + sourcePath, std::ios::in | std::ios::binary);
//	if (!file) {
//
//		throw std::runtime_error("Failed to open the shader file");
//	}
//
//	file.seekg(0, std::ios::end);
//	size_t fileSize = static_cast<size_t>(file.tellg());
//	file.seekg(0, std::ios::beg);
//	std::vector<char> buffer(fileSize);
//	file.seekg(0);
//
//
//	file.read(buffer.data(), fileSize);
//	file.close();
//
//	spirvCode = { buffer.begin(), buffer.end() };
//	return true;
//}
//
//
