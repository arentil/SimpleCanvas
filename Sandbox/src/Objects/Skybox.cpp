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

Skybox::Skybox(sc::Shader const& shader) 
: sc::SCObject("Skybox", shader)
{
    std::vector<std::string> cubemapFacesFiles
    {
        "assets/textures/skybox/right.jpg",
        "assets/textures/skybox/left.jpg",
        "assets/textures/skybox/top.jpg",
        "assets/textures/skybox/bottom.jpg",
        "assets/textures/skybox/front.jpg",
        "assets/textures/skybox/back.jpg"
    };

    cubemap = sc::Cubemap::create(cubemapFacesFiles);

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

    auto mesh = std::make_shared<sc::TextureMesh>(vertices, cubemap);
    std::vector<sc::BaseMeshPtr> const meshes{ mesh };
    _model = std::make_shared<sc::Model>(meshes);
}

void Skybox::draw(sc::FPSCamera const& camera, sc::Lights const& lights) 
{
    _modelMatrix = scmath::Mat4::translate(camera.getPosition());
    glDepthMask(GL_FALSE);
    sc::SCObject::draw(camera, sc::Lights{});
    glDepthMask(GL_TRUE);
}