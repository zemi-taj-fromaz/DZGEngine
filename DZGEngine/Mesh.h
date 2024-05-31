#pragma once
#pragma once

#include <vulkan/vulkan.h>
#include "vertex_buffer.h"
#include "PipelineData.h"
#include <vector>

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

    void load_quad();
    void load();

};
