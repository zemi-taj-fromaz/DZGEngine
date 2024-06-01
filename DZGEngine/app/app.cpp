#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>
#include <set>
#include <limits> 
#include <algorithm> 

#include "AppBoilerplate.h"

void dzg::run(std::unique_ptr<Scene>& s) {

    this->m_scene = std::move(s);

    this->WIDTH = m_scene->WIDTH;
    this->HEIGHT = m_scene->HEIGHT;

    initWindow();

    initVulkan();
    
    float aspectRation = (float)this->WIDTH / (float)this->HEIGHT;

    float camHeight = 9.0f;
    float bottom = -camHeight;
    float top = camHeight;
    float left = bottom * aspectRation;
    float right = top * aspectRation;

    //float camHeight = 9.0f;
    //float bottom = 0.f;
    //float top = this->HEIGHT;
    //float left = 0.f;
    //float right = this->WIDTH;
    camera = std::make_unique<Camera>(left, right, bottom, top);


 //   camera = std::make_unique<Camera>(0.0f, static_cast<float>(this->WIDTH), 0.0f, (float)this->HEIGHT);

    mainLoop();
    cleanup();
}

void  dzg::mainLoop() {
    
    static float initialTime{ (float)glfwGetTime() };


    float time = (float)glfwGetTime();
    float deltaTime = time - initialTime;
    float totalTime = time - initialTime;


    while (!glfwWindowShouldClose(window)) {

        float currTime = (float)glfwGetTime();
        deltaTime = currTime - time;
        totalTime = currTime - initialTime;
        time = currTime;
        
        glfwPollEvents();

        if (inputPolling(deltaTime) == false) break;
        m_scene->scene_update(totalTime, deltaTime, this);

        drawFrame();
    }

    vkDeviceWaitIdle(core.device);
}


void dzg::drawFrame() {

    auto& device = core.device;
    auto& inFlightFence = sync[currentFrame].inFlightFence;
    auto& swapChain = core.swapChain;
    auto& imageAvailableSemaphore = sync[currentFrame].imageAvailableSemaphore;
    auto& renderFinishedSemaphore = sync[currentFrame].renderFinishedSemaphore;
    auto& commandBuffer = commandBuffers[currentFrame];

    vkWaitForFences(core.device, 1, &inFlightFence, VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || framebufferResized) {
        framebufferResized = false;
        recreateSwapChain();
        return;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    // Only reset the fence if we are submitting work
    vkResetFences(device, 1, &inFlightFence);

    updateUniformBuffer(currentFrame);

    vkResetCommandBuffer(commandBuffer, 0);
    recordCommandBuffer(commandBuffer, imageIndex);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { imageAvailableSemaphore };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    VkSemaphore signalSemaphores[] = { renderFinishedSemaphore };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(core.graphicsQueue, 1, &submitInfo, inFlightFence) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { core.swapChain };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;

    result = vkQueuePresentKHR(core.presentQueue, &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
        recreateSwapChain();
    }
    else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }


    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

}