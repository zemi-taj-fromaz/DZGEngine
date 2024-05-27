#pragma once

#include "app.h"
#include <stdexcept>

void dzg::createSyncObjects() {

    sync.resize(MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for(int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
    {
        if (vkCreateSemaphore(core.device, &semaphoreInfo, nullptr, &sync[i].imageAvailableSemaphore) != VK_SUCCESS ||
            vkCreateSemaphore(core.device, &semaphoreInfo, nullptr, &sync[i].renderFinishedSemaphore) != VK_SUCCESS ||
            vkCreateFence(core.device, &fenceInfo, nullptr, &sync[i].inFlightFence) != VK_SUCCESS) {
            throw std::runtime_error("failed to create semaphores!");
        }
    }

}