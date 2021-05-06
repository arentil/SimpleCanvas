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

Skybox::Skybox(sc::AssetsContainer const& assets, sc::FPSCamera const& camera) 
: sc::SCObject("Skybox", assets.Shaders.getShader("Skybox"))
, _camera(camera)
{
    std::vector<sc::TextureVertex> vertices
    {
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

    auto mesh = std::make_shared<sc::TextureMesh>(vertices, assets.Textures.getTexture("Skybox"));
    std::vector<sc::BaseMeshPtr> const meshes{ mesh };
    _model = std::make_shared<sc::Model>(meshes);
}

void Skybox::onAnimate(float deltaTime) 
{
    Transform.Translation = _camera.getPosition();
}

void Skybox::onDraw(sc::FPSCamera const& camera, sc::Lights const& lights, scmath::Mat4 const& modelMatrix)
{
    glDepthMask(GL_FALSE);
    sc::SCObject::onDraw(camera, lights, modelMatrix);
    glDepthMask(GL_TRUE);
}