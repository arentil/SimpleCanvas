#include "Skybox.h"

#include <vector>

namespace
{
void applyMatrixAndAppend(std::vector<sc::TextureVertex> &vertices, scmath::Mat4 const& matrix)
{
    for (size_t i = 0; i < 6; i++)
    {
        sc::TextureVertex v{matrix * vertices[i].position};
        vertices.push_back(v);
    }
}
}

Skybox::Skybox(sc::Shader const& shader, sc::Camera const& camera, sc::TexturePtr const texture) 
: _shader(shader), _camera(camera)
{
    std::vector<sc::TextureVertex> vertices{        // front
        {{-0.5f, -0.5f, -0.5f}},
        {{0.5f, -0.5f, -0.5f}},
        {{0.5f, 0.5f, -0.5f}},
        {{0.5f, 0.5f, -0.5f}},
        {{-0.5f, 0.5f, -0.5f}},
        {{-0.5f, -0.5f, -0.5f}}
    };
    vertices.reserve(24);
    applyMatrixAndAppend(vertices, scmath::Mat4::rotateY(scmath::degToRad(90))); //right
    applyMatrixAndAppend(vertices, scmath::Mat4::rotateY(scmath::degToRad(-90))); //left
    applyMatrixAndAppend(vertices, scmath::Mat4::rotateX(scmath::degToRad(-90))); //top
    applyMatrixAndAppend(vertices, scmath::Mat4::rotateX(scmath::degToRad(90))); //bottom
    applyMatrixAndAppend(vertices, scmath::Mat4::rotateY(scmath::degToRad(180))); //back

    auto mesh = std::make_shared<sc::TextureMesh>(vertices, texture);
    std::vector<sc::BaseMeshPtr> const meshes{ mesh };
    _model = std::make_shared<sc::Model>(meshes);
}

void Skybox::draw(scmath::Mat4 const& modelMatrix) const
{
    glDepthMask(GL_FALSE);
    _model->draw(_shader, _camera, sc::Material{}, modelMatrix);
    glDepthMask(GL_TRUE);
}