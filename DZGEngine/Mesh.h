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


    glm::mat4 Model{ glm::mat4(1.0f) };
    glm::vec4 Position{ glm::vec4(0.0f) };
    glm::vec4 Color{ glm::vec4(1.0) };

    void update(float totalTime, float deltaTime)
    {
        offsetPosition(glm::vec3(-50000.0f * deltaTime, 0.0f, 0.0f));
    }

private:
    void computeModelMatrix();
    
    glm::mat4 translation{ glm::mat4(1.0f) };
    glm::mat4 rotation{ glm::mat4(1.0f) };
    glm::mat4 scale{ glm::mat4(1.0f) };

};
