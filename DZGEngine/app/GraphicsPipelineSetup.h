#pragma once

#include "app.h"
#include "../Vertex.h"

void dzg::createGraphicsPipelines() 
{
    /*
        TODO
        create_pipeline_layouts() -> takes scene as an argument
            Move pipeline layouts from PipelineData somewhere else
    */

    for (auto& pipelineData : m_scene->pipelineDataVec)
    {
        std::vector<VkDescriptorSetLayout> dSetLayoutVec;
        for (int i = 0; i < pipelineData->pDescriptorSetLayouts.size(); ++i)
        {
            dSetLayoutVec.push_back(pipelineData->pDescriptorSetLayouts[i]->dSetLayout);
        }

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(dSetLayoutVec.size()); // Optional
        pipelineLayoutInfo.pSetLayouts = dSetLayoutVec.data(); // Optional 
        pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
        pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

        if (vkCreatePipelineLayout(core.device, &pipelineLayoutInfo, nullptr, &(pipelineData->PipelineLayout)) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }
        build_pipeline(this, pipelineData.get());
    }

}

void dzg::createRenderPass() {
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = core.swapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT; // change this when multisampling
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR; // clears the framebuffer to black before starting a new frame
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    if (vkCreateRenderPass(core.device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
        throw std::runtime_error("failed to create render pass!");
    }
}