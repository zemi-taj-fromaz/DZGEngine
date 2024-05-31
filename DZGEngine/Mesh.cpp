#include "Mesh.h"


void Mesh::load_quad()
{
    // Clear existing data
    Vertices.clear();
    Indices.clear();

    Vertices = {
    {{  0.0f, 50.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    {{  50.0f, 50.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    {{  50.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{  0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}
    };


    Indices = {
        0, 1, 2, 2, 3, 0
    };
}

void Mesh::load()
{

    switch (this->meshType)
    {
    //case MeshType::Sphere:
    //{
    //    return load_sphere(illuminated, textured);
    //    break;
    //}
    //case MeshType::Cube:
    //{
    //    return load_cube(illuminated, textured);
    //    break;
    //}
    case MeshType::Quad:
    {
        load_quad();
        return;
    }
    //case MeshType::Line:
    //{
    //    return load_line(illuminated, textured);
    //    break;
    //}
    //case MeshType::Plain:
    //{
    //    return load_plain(illuminated, textured);
    //    break;
    //}
    //case MeshType::Terrain:
    //{
    //    return load_terrain(illuminated, textured);
    //    break;
    //}
    }
}
