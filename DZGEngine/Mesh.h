#pragma once
#pragma once

#include <vulkan/vulkan.h>
#include "vertex_buffer.h"
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

struct Mesh
{
    Mesh()
    {}

    //Mesh(std::string filename) : Filename(filename)
    //{}

    Mesh(MeshType meshType) : meshType(meshType)
    {
        load();
    }

    //Mesh(MeshType meshType, int vertexCount, int patchSize) : meshType(meshType), vertex_count(vertexCount), patch_size(patchSize)
    //{}

    //Mesh(const Mesh& mesh)
    //{
    //    Vertices = mesh.Vertices;
    //    Indices = mesh.Indices;
    //    VertexBuffer = mesh.VertexBuffer;
    //    IndexBuffer = mesh.IndexBuffer;
    //    VertexBufferMemory = mesh.VertexBufferMemory;
    //    IndexBufferMemory = mesh.IndexBufferMemory;
    //    Animation = mesh.Animation;
    //    TextureSets = mesh.TextureSets;
    //    Animated = mesh.Animated;
    //    Filename = mesh.Filename;
    //    meshType = mesh.meshType;
    //    patch_size = mesh.patch_size;
    //    vertex_count = mesh.vertex_count;
    //}

    Mesh operator=(const Mesh& mesh)
    {
        return Mesh(mesh);
    }

    MeshType meshType{ MeshType::None };

    std::vector<Vertex> Vertices;
    std::vector<uint32_t> Indices;
    VkBuffer VertexBuffer;
    VkBuffer IndexBuffer;
    VkDeviceMemory VertexBufferMemory;
    VkDeviceMemory IndexBufferMemory;

    //bool Animated{ false };
    //std::string Filename;
    //int patch_size{ 0 };
    //int vertex_count{ 0 };

    std::vector<VkDescriptorSet> TextureSets; //texture defaulted to null


   // const std::string MODEL_PATH = "resources/models/";
   // const std::string ANIMATION_PATH = "resources/animations/";


    //bool load_from_obj(bool illuminated, bool texture = false);
    //bool load_sphere(bool illuminated, bool textured);

    //bool load_cube(bool illuminated, bool textured);
    //bool load_quad(bool illuminated, bool textured);
    //bool load_line(bool illuminated, bool textured);
    //bool load_terrain(bool illuminated, bool textured);
    //bool load_plain(bool illuminated, bool textured);
    void load_quad();
    void load();

    //bool load_animation(std::string filename);


   // const int ARENA_SIZE{ 800 };

    //static std::vector<std::vector<float>> heightMap;
};
