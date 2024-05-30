#pragma once

#include "app.h"

#include <unordered_map>

void dzg::createDescriptorSetLayout()
{
    DescriptorSetLayoutVec_t& descriptorSetLayouts = m_scene->DescriptorSetLayoutVec;


    for (auto& descriptorSetLayoutPtr : descriptorSetLayouts)
    {
        std::vector<VkDescriptorSetLayoutBinding> bindingVec;

        for (int i = 0; i < descriptorSetLayoutPtr->bindings.size(); ++i)
        {
            VkDescriptorSetLayoutBinding layoutBinding{};
            layoutBinding.binding = i;
            layoutBinding.descriptorType = descriptorSetLayoutPtr->bindings[i].type;
            layoutBinding.descriptorCount = descriptorSetLayoutPtr->bindings[i].descriptorCount; // number of values in the array of uniform buffer object
            layoutBinding.stageFlags = descriptorSetLayoutPtr->bindings[i].stageFlags;
            layoutBinding.pImmutableSamplers = nullptr; // Optional
            bindingVec.push_back(layoutBinding);
        }

        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = static_cast<uint32_t>(bindingVec.size());
        layoutInfo.pBindings = bindingVec.data();

        if (vkCreateDescriptorSetLayout(core.device, &layoutInfo, nullptr, &(descriptorSetLayoutPtr->dSetLayout))  != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }
    }
}

void dzg::createDescriptorPool()
{
    std::vector<VkDescriptorPoolSize> sizes =
    {
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 50 },
        { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 50 },
        { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 50 },
        { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 50 },
        { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 100 }
    };

    VkDescriptorPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.flags = 0;
    poolInfo.maxSets = 100;
    poolInfo.poolSizeCount = (uint32_t)sizes.size();
    poolInfo.pPoolSizes = sizes.data();

    if (vkCreateDescriptorPool(core.device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}

void dzg::createDescriptorSets() {
    for(int i = 0; i < m_scene->DescriptorSetVec.size(); ++i)
    {

        std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, m_scene->DescriptorSetVec[i]->layout->dSetLayout);

        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
        allocInfo.pSetLayouts = layouts.data();

        m_scene->DescriptorSetVec[i]->sets.resize(MAX_FRAMES_IN_FLIGHT);
        if (vkAllocateDescriptorSets(core.device, &allocInfo, m_scene->DescriptorSetVec[i]->sets.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }

        std::vector<VkWriteDescriptorSet> descriptorWrites; //TASK

        for (size_t j = 0; j < MAX_FRAMES_IN_FLIGHT; j++) {
            
            for (int k = 0; k < m_scene->DescriptorSetVec[i]->bufferDataVec.size(); k++)
            {
                VkDescriptorBufferInfo bufferInfo{};
                bufferInfo.buffer = m_scene->DescriptorSetVec[i]->bufferDataVec[k]->Buffers[j];
                bufferInfo.offset = 0;
                bufferInfo.range = m_scene->DescriptorSetVec[i]->bufferDataVec[k]->size;

                VkWriteDescriptorSet descriptorWrite{}; //TASK

                descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                descriptorWrite.dstSet = m_scene->DescriptorSetVec[i]->sets[j];
                descriptorWrite.dstBinding = k;
                descriptorWrite.dstArrayElement = 0;
                descriptorWrite.descriptorType = m_scene->DescriptorSetVec[i]->bufferDataVec[k]->type;
                descriptorWrite.descriptorCount = 1;
                descriptorWrite.pBufferInfo = &bufferInfo;
                
                descriptorWrites.push_back(descriptorWrite);
            }

 /*           VkDescriptorBufferInfo bufferInfo{};
            bufferInfo.buffer = uniformBuffers[i];
            bufferInfo.offset = 0;
            bufferInfo.range = sizeof(UniformBufferObject);*/


            VkDescriptorImageInfo imageInfo{};
            imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            imageInfo.imageView = textureImageView;
            imageInfo.sampler = textureSampler;

            //std::array<VkWriteDescriptorSet, 1> descriptorWrites{}; //TASK

            //descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            //descriptorWrites[0].dstSet = descriptorSets[i];
            //descriptorWrites[0].dstBinding = 0;
            //descriptorWrites[0].dstArrayElement = 0;
            //descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            //descriptorWrites[0].descriptorCount = 1;
            //descriptorWrites[0].pBufferInfo = &bufferInfo;

            //descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            //descriptorWrites[1].dstSet = descriptorSets[i];
            //descriptorWrites[1].dstBinding = 1;
            //descriptorWrites[1].dstArrayElement = 0;
            //descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            //descriptorWrites[1].descriptorCount = 1;
            //descriptorWrites[1].pImageInfo = &imageInfo;

            vkUpdateDescriptorSets(core.device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
        }
    }
}