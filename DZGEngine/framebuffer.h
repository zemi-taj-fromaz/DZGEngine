#pragma once

#include "app.h"

void dzg::createFramebuffers() 
{
    core.swapChainFramebuffers.resize(core.swapChainImageViews.size());

    for (size_t i = 0; i < core.swapChainImageViews.size(); i++) 
    {
        VkImageView attachments[] = {
            core.swapChainImageViews[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = core.swapChainExtent.width;
        framebufferInfo.height = core.swapChainExtent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(core.device, &framebufferInfo, nullptr, &core.swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }

    }
}