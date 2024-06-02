#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>


void Mesh::load_quad()
{
    // Clear existing data
    Vertices.clear();
    Indices.clear();

    Vertices = {
    {{  0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    {{  1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    {{  1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
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

void Mesh::computeModelMatrix()
{
    this->Model = this->translation * this->rotation * this->scale;
}

void Mesh::offsetPosition(glm::vec3 offset)
{
    this->Position += glm::vec4(glm::vec2(offset), 0.0f, 0.0f);
    auto translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(Position.x, Position.y, 0.0f));
    this->setTranslation( translationMatrix );
}

void Mesh::setPosition(glm::vec3 pos)
{
    this->Position.x = pos.x;
    this->Position.y = pos.y;
    auto translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(Position.x, Position.y, 0.0f));
    this->setTranslation(translationMatrix);
}

void Mesh::setTranslation(glm::mat4& translation)
{
    this->translation = translation;
    computeModelMatrix();
}
void Mesh::setRotation(glm::mat4& rotation)
{
    this->rotation = rotation;
    computeModelMatrix();
}
void Mesh::setScale(glm::mat4& scale)
{
    this->scale = scale;
    computeModelMatrix();
}
