#pragma once

#include <set>
#include <stdexcept>

#include "glfw_window_init.h"
#include "ShaderLoad.h"
#include "SwapchainSetup.h"
#include "GraphicsPipelineSetup.h"
#include "Framebuffer.h"
#include "CommandBuffers.h"
#include "SyncObjects.h"
#include "Descriptors.h"
#include "Buffers.h"
#include "Images.h"
#include "Scene.h"

void  dzg::cleanup() {
    auto& device = core.device;

    cleanupSwapChain();

    for (size_t i = 0; i < m_scene->SamplersVec.size(); ++i)
    {
        vkDestroySampler(device, m_scene->SamplersVec[i]->vkSampler, nullptr);
    }

    for (size_t i = 0; i < m_scene->TexturesVec.size(); ++i)
    {
        vkDestroyImageView(device, m_scene->TexturesVec[i]->textureImageView, nullptr);
        vkDestroyImage(device, m_scene->TexturesVec[i]->textureImage, nullptr);
        vkFreeMemory(device, m_scene->TexturesVec[i]->TextureImageMemory, nullptr);
    }

    for (size_t i = 0; i < m_scene->BufferDataVec.size(); ++i)
    {
        if (m_scene->BufferDataVec[i]->Texture != nullptr) continue;
        for (size_t j = 0; j < MAX_FRAMES_IN_FLIGHT; ++j) 
        {
            vkDestroyBuffer(core.device, m_scene->BufferDataVec[i]->Buffers[j], nullptr);
            vkFreeMemory(core.device, m_scene->BufferDataVec[i]->BuffersMemory[j], nullptr);
        }
    }

    vkDestroyDescriptorPool(core.device, descriptorPool, nullptr);

    for (size_t i = 0; i < m_scene->DescriptorSetLayoutVec.size(); ++i)
    {
        vkDestroyDescriptorSetLayout(core.device, m_scene->DescriptorSetLayoutVec[i]->dSetLayout, nullptr);
    }

    for (size_t i = 0; i < m_scene->MeshVec.size(); ++i)
    {
        vkDestroyBuffer(core.device, m_scene->MeshVec[i]->IndexBuffer, nullptr);
        vkFreeMemory(core.device, m_scene->MeshVec[i]->IndexBufferMemory, nullptr);

        vkDestroyBuffer(core.device, m_scene->MeshVec[i]->VertexBuffer, nullptr);
        vkFreeMemory(core.device, m_scene->MeshVec[i]->VertexBufferMemory, nullptr);
    }

    for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i)
    {
        vkDestroySemaphore(core.device, sync[i].imageAvailableSemaphore, nullptr);
        vkDestroySemaphore(core.device, sync[i].renderFinishedSemaphore, nullptr);
        vkDestroyFence(core.device, sync[i].inFlightFence, nullptr);
    }

    for (size_t i = 0; i < m_scene->pipelineDataVec.size(); ++i)
    {
        vkDestroyPipeline(core.device, m_scene->pipelineDataVec[i]->pipeline, nullptr);
        vkDestroyPipelineLayout(core.device, m_scene->pipelineDataVec[i]->PipelineLayout, nullptr);
    }

    vkDestroyRenderPass(core.device, renderPass, nullptr);

    vkDestroyCommandPool(core.device, commandPool, nullptr);

    vkDestroyDevice(core.device, nullptr);

    if (enableValidationLayers) {
        DestroyDebugUtilsMessengerEXT(core.instance, core.debugMessenger, nullptr);
    }
    vkDestroySurfaceKHR(core.instance, core.surface, nullptr);
    vkDestroyInstance(core.instance, nullptr);

    glfwDestroyWindow(window);
    glfwTerminate();
}


void  dzg::initWindow() {
    window = glfw::initWindowGLFW(WIDTH, HEIGHT);

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);

    glfwSetWindowMonitor(window, primaryMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}

void dzg::inputPolling(float deltaTime)
{
    glfw::inputPolling(window, camera, deltaTime);
}

void  dzg::initVulkan() {
    createInstance();
    setupDebugMessenger();
    createSurface();
    pickPhysicalDevice();
    createLogicalDevice();
    createSwapChain();
    createRenderPass();

    {
        createDescriptorSetLayout(); // takes scene
        createGraphicsPipelines(); // takes scene
    }


    createImageViews();
    createFramebuffers();
    createCommandPool();

    /*
      take scene
    */
    {
        createTextureImage();
        createTextureImageView();
        createTextureSampler();

        createVertexBuffers();
        createIndexBuffers();
        createUniformBuffers(); 

        createDescriptorPool();
        createDescriptorSets();
    }
    createCommandBuffers();
    createSyncObjects();
}



void  dzg::createLogicalDevice() {
    QueueFamilyIndices indices = findQueueFamilies(core.physicalDevice);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};
    deviceFeatures.samplerAnisotropy = VK_TRUE;

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());

    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }
    if (vkCreateDevice(core.physicalDevice, &createInfo, nullptr, &core.device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }
    vkGetDeviceQueue(core.device, indices.graphicsFamily.value(), 0, &core.graphicsQueue);
    vkGetDeviceQueue(core.device, indices.presentFamily.value(), 0, &core.presentQueue);
}

void  dzg::pickPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(core.instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(core.instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (isDeviceSuitable(device)) {
            core.physicalDevice = device;
            break;
        }
    }

    if (core.physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }

}

bool  dzg::checkDeviceExtensionSupport(VkPhysicalDevice device) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

dzg::QueueFamilyIndices  dzg::findQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices;
    std::optional<uint32_t> graphicsFamily;

    graphicsFamily = 0;
    uint32_t queueFamilyCount = 0;

    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, core.surface, &presentSupport);
        if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) && (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)) {
            indices.graphicsFamily = i;
        }
        if (presentSupport) {
            indices.presentFamily = i;
        }
        if (indices.isComplete()) {
            break;
        }
        i++;
    }

    return indices;
}

bool dzg::isDeviceSuitable(VkPhysicalDevice device) {
    QueueFamilyIndices indices = findQueueFamilies(device);

    bool extensionsSupported = checkDeviceExtensionSupport(device);

    bool swapChainAdequate = false;
    if (extensionsSupported) {
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    VkPhysicalDeviceFeatures supportedFeatures;
    vkGetPhysicalDeviceFeatures(device, &supportedFeatures);
    return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
}

void  dzg::createInstance() {
    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;


    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else {
        createInfo.enabledLayerCount = 0;

        createInfo.pNext = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &core.instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
}

void  dzg::createSurface() {
    if (glfwCreateWindowSurface(core.instance, window, nullptr, &core.surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

bool  dzg::checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    for (const char* layerName : validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}


std::vector<const char*>  dzg::getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);


    return extensions;
}

void  dzg::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
}

VkResult  dzg::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void  dzg::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

void  dzg::setupDebugMessenger() {
    if (!enableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo{};
    populateDebugMessengerCreateInfo(createInfo);
    if (CreateDebugUtilsMessengerEXT(core.instance, &createInfo, nullptr, &core.debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}


