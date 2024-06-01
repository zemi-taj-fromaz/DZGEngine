#pragma once
#pragma once

#include "app.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <chrono>

void dzg::createVertexBuffer()
{
    for (Mesh& mesh : m_scene->MeshVec)
    {
        VkDeviceSize bufferSize = sizeof(mesh.Vertices[0]) * mesh.Vertices.size();

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(core.device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, mesh.Vertices.data(), (size_t)bufferSize);
        vkUnmapMemory(core.device, stagingBufferMemory);

        createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, mesh.VertexBuffer, mesh.VertexBufferMemory);

        copyBuffer(stagingBuffer, mesh.VertexBuffer, bufferSize);

        vkDestroyBuffer(core.device, stagingBuffer, nullptr);
        vkFreeMemory(core.device, stagingBufferMemory, nullptr);
    }

    //Issue :  the driver may not immediately copy the data into the buffer memory, 
    // Solution: Use a memory heap that is host coherent, indicated with VK_MEMORY_PROPERTY_HOST_COHERENT_BIT 
    //Call vkFlushMappedMemoryRanges after writing to the mapped memory, and call vkInvalidateMappedMemoryRanges before reading from the mapped memory

    //The transfer of data to the GPU is an operation that happens in the background and the specification simply tells us that it is guaranteed to be complete as of the next call to vkQueueSubmit.
}

void dzg::createIndexBuffer() 
{

    for (Mesh& mesh : m_scene->MeshVec)
    {
        VkDeviceSize bufferSize = sizeof(mesh.Indices[0]) * mesh.Indices.size();

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

        void* data;
        vkMapMemory(core.device, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, mesh.Indices.data(), (size_t)bufferSize);
        vkUnmapMemory(core.device, stagingBufferMemory);

        createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, mesh.IndexBuffer, mesh.IndexBufferMemory);

        copyBuffer(stagingBuffer, mesh.IndexBuffer, bufferSize);

        vkDestroyBuffer(core.device, stagingBuffer, nullptr);
        vkFreeMemory(core.device, stagingBufferMemory, nullptr);
    }

}

void dzg::createUniformBuffers() {

    for (int i = 0; i < m_scene->BufferDataVec.size(); ++i)
    {
        if (m_scene->BufferDataVec[i]->type == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER) continue;

        m_scene->BufferDataVec[i]->Buffers.resize(MAX_FRAMES_IN_FLIGHT);
        m_scene->BufferDataVec[i]->BuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
        m_scene->BufferDataVec[i]->BuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

        for (size_t j = 0; j < MAX_FRAMES_IN_FLIGHT; j++) {
            createBuffer(m_scene->BufferDataVec[i]->size, m_scene->BufferDataVec[i]->usage, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                m_scene->BufferDataVec[i]->Buffers[j], m_scene->BufferDataVec[i]->BuffersMemory[j]);

            vkMapMemory(core.device, m_scene->BufferDataVec[i]->BuffersMemory[j], 0, m_scene->BufferDataVec[i]->size, 0, &m_scene->BufferDataVec[i]->BuffersMapped[j]);
        }
    }
}

void dzg::updateUniformBuffer(uint32_t currentImage) {
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    for (int i = 0; i < m_scene->BufferDataVec.size(); i++)
    {
        if (m_scene->BufferDataVec[i]->type != VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER) m_scene->BufferDataVec[i]->update(this, currentImage);
    }
}

void dzg::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(core.device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(core.device, buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(core.device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    /*
    It should be noted that in a real world application, you're not supposed to actually call vkAllocateMemory for every individual buffer.
    The maximum number of simultaneous memory allocations is limited by the maxMemoryAllocationCount physical device limit,
    which may be as low as 4096 even on high end hardware like an NVIDIA GTX 1080.
    The right way to allocate memory for a large number of objects at the same time is to create a custom allocator that splits up a single allocation among many different objects by using the offset parameters that we've seen in many functions.
    */

    vkBindBufferMemory(core.device, buffer, bufferMemory, 0);
}

uint32_t dzg::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(core.physicalDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if (typeFilter & (1 << i) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }
    throw std::runtime_error("failed to find suitable memory type!");
}

void dzg::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
    VkCommandBuffer commandBuffer = beginSingleTimeCommands();

    VkBufferCopy copyRegion{};
    copyRegion.size = size;
    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

    endSingleTimeCommands(commandBuffer);
}