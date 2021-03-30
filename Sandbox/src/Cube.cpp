#include "Cube.h"

#include <vector>

namespace
{
void applyMatrixAndAppend(std::vector<sc::Vertex> &vertices, scmath::Mat4 const& matrix, scmath::Mat4 const& normalMatrix)
{
    for (size_t i = 0; i < 4; i++)
    {
        sc::Vertex v{matrix * vertices[i].position, normalMatrix * vertices[i].normal, vertices[i].texCoord};
        vertices.push_back(v);
    }
}
}

Cube::Cube(sc::Shader const& shader, sc::Camera const& camera, sc::Texture2d const& texture) 
: _shader(shader), _camera(camera)
{
    std::vector<sc::Vertex> vertices{
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}
    };
    vertices.reserve(24);
    applyMatrixAndAppend(vertices, scmath::Mat4::translate(-0.5f, 0.0f, -0.5f) * scmath::Mat4::rotateY(scmath::degToRad(90)), scmath::Mat4::rotateY(scmath::degToRad(90))); //left
    applyMatrixAndAppend(vertices, scmath::Mat4::translate(0.0f, 0.0f, -1.0f) * scmath::Mat4::rotateY(scmath::degToRad(180)), scmath::Mat4::rotateY(scmath::degToRad(180))); //back
    applyMatrixAndAppend(vertices, scmath::Mat4::translate(0.5f, 0.0f, -0.5f) * scmath::Mat4::rotateY(scmath::degToRad(-90)), scmath::Mat4::rotateY(scmath::degToRad(-90))); //right
    applyMatrixAndAppend(vertices, scmath::Mat4::translate(0.0f, 0.5f, -0.5f) * scmath::Mat4::rotateX(scmath::degToRad(90)), scmath::Mat4::rotateX(scmath::degToRad(90))); //top
    applyMatrixAndAppend(vertices, scmath::Mat4::translate(0.0f, -0.5f, -0.5f) * scmath::Mat4::rotateX(scmath::degToRad(-90)), scmath::Mat4::rotateX(scmath::degToRad(-90))); //bottom

    std::vector<uint32_t> indices;
    indices.reserve(24);

    for (int i = 0; i < 6; i++)
    {
        indices.push_back((i * 4));
        indices.push_back((i * 4) + 1);
        indices.push_back((i * 4) + 2);
        indices.push_back((i * 4) + 2);
        indices.push_back((i * 4) + 3);
        indices.push_back((i * 4));
    }

    //std::vector<sc::Mesh> const meshes{{vertices, indices, texture}};
    //_model = std::make_shared<sc::Model>(meshes);
}

void Cube::draw(scmath::Mat4 const& modelMatrix) const
{
    //_model->draw(_shader, _camera, modelMatrix);
}