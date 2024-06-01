#pragma once
#pragma once

#include <vulkan/vulkan.h>
#include "Vertex.h"
#include "PipelineData.h"
#include <vector>
#include <optional>

enum class MeshType
{
    None = 0,
    Sphere = 1,
    Cube = 2,
    Quad = 3,
    Line = 4,
    Terrain = 5,
    Plain = 6
};

using DescriptorSetVec_t = std::vector<std::shared_ptr<DescriptorSet>>;

struct Mesh
{
    Mesh()
    {}


    Mesh(MeshType meshType) : meshType(meshType)
    {
        load();
    }


    Mesh operator=(const Mesh& mesh)
    {
        return Mesh(mesh);
    }

    MeshType meshType{ MeshType::None };

    std::vector<Vertex> Vertices;
    std::vector<uint16_t> Indices;
    VkBuffer VertexBuffer;
    VkBuffer IndexBuffer;
    VkDeviceMemory VertexBufferMemory;
    VkDeviceMemory IndexBufferMemory;

    DescriptorSetVec_t DescriptorSetVec;
    std::shared_ptr<PipelineData> PipelineData;

    void load();
    void load_quad();

    void setTranslation(glm::mat4& translation);
    void setRotation(glm::mat4& rotation);
    void setScale(glm::mat4& scale);
    void offsetPosition(glm::vec3 offset);
    void setPosition(glm::vec3 pos);


    glm::mat4 Model{ glm::mat4(1.0f) };
    glm::vec4 Position{ glm::vec4(0.0f) };
    glm::vec4 Color{ glm::vec4(1.0) };

    virtual void update(float totalTime, float deltaTime, dzg* app) {}
    virtual void render(VkCommandBuffer commandBuffer, int instanceIndex, int currFrame) 
    {
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, this->PipelineData->pipeline);

        VkBuffer vertexBuffers[] = { this->VertexBuffer };
        VkDeviceSize offsets[] = { 0 };
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);
        vkCmdBindIndexBuffer(commandBuffer, this->IndexBuffer, 0, VK_INDEX_TYPE_UINT16);

        for (int j = 0; j < this->DescriptorSetVec.size(); ++j)
        {
            vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, this->PipelineData->PipelineLayout, j, 1, &this->DescriptorSetVec[j]->sets[currFrame], 0, nullptr);
        }
        vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(this->Indices.size()), 1, 0, 0, instanceIndex);
    }

private:
    void computeModelMatrix();
    
    glm::mat4 translation{ glm::mat4(1.0f) };
    glm::mat4 rotation{ glm::mat4(1.0f) };
    glm::mat4 scale{ glm::mat4(1.0f) };

};
