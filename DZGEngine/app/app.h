#pragma once

#include <vulkan/vulkan.h>

#include <cstdlib>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <optional>
#include <stdexcept>
#include <memory>

#include "Camera.h"
#include "Vertex.h"
#include "scene.h"
#include "PipelineData.h"

//#include "vendor/imgui/imgui.h"
//#include "vendor/imgui/imgui_impl_glfw.h"
//#include "vendor/imgui/imgui_impl_vulkan.h"

class dzg {
public:
    
    friend void build_pipeline(dzg* app, PipelineData* pipelineData);
    
    void run(std::unique_ptr<Scene>& s);

    uint32_t GetWidth() { return WIDTH; }
    uint32_t GetHeight() { return HEIGHT; }
 
private:

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct VkCore
    {
        VkInstance instance;
        VkDevice device;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkQueue graphicsQueue;
        VkSurfaceKHR surface;
        VkQueue presentQueue;
        VkSwapchainKHR swapChain;
        VkDebugUtilsMessengerEXT debugMessenger;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
    };

    struct VkSync
    {
        VkSemaphore imageAvailableSemaphore;
        VkSemaphore renderFinishedSemaphore;
        VkFence inFlightFence;
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct UniformBufferObject {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 proj;
    };

    void initWindow();
    void initVulkan();
    void initImgui();
    void createSurface();
    void createLogicalDevice();
    void pickPhysicalDevice();
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);


    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    void createInstance();

    void mainLoop();

    void cleanup();
    bool checkValidationLayerSupport();

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    std::vector<const char*> getRequiredExtensions();
    void createSwapChain();
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    void setupDebugMessenger();
    bool isDeviceSuitable(VkPhysicalDevice device);
    void createImageViews();
    void createGraphicsPipelines();
    VkShaderModule createShaderModule(const std::vector<char>& code);
    void createRenderPass();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    void drawFrame();
    void createSyncObjects();
    void recreateSwapChain();
    void cleanupSwapChain();

    void createVertexBuffers();
    void createIndexBuffers();
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    void createDescriptorSetLayout();
    void createUniformBuffers();
    void updateUniformBuffer(uint32_t currentImage);

    void createDescriptorPool();
    void createDescriptorSets();
    void createTextureImage();
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

    void createTextureImageView();
    VkImageView createImageView(VkImage image, VkFormat format);
    void createTextureSampler();
    bool         inputPolling(float deltaTime);

    void createFontAtlas(char* pixels);

public:
    bool framebufferResized = false;
    std::unique_ptr<Camera> camera;
    int camHeight;
    std::unique_ptr<Scene> m_scene;
    float initialTime;

private:
    const int MAX_FRAMES_IN_FLIGHT = 2;
    int currentFrame;

    uint32_t WIDTH; //TODO pack this up nicely and don't make it public and possibly fix window init, it's annoying
    uint32_t HEIGHT;
    GLFWwindow* window;

    const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
    };
    const bool enableValidationLayers = true;

    VkCore core;
    std::vector<VkSync> sync;


    const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;
    VkDescriptorPool descriptorPool;
    VkDescriptorPool m_ImguiPool;
    std::vector<VkDescriptorSet> descriptorSets;

    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    VkImage textureImage;
    VkImageView textureImageView;
    VkDeviceMemory textureImageMemory;
    VkSampler textureSampler;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;


    const std::vector<Vertex> vertices = {
    {{  0.0f, 50.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{  50.0f, 50.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{  50.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    {{  0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
    };


    const std::vector<uint16_t> indices = {
        0, 1, 2, 2, 3, 0
    };
};
