#include "Terrain.h"

#include <vector>

namespace
{
void applyMatrixAndAppend(std::vector<sc::TextureVertex> &vertices, scmath::Mat4 const& matrix, scmath::Mat4 const& normalMatrix)
{
    for (size_t i = 0; i < 6; i++)
    {
        sc::TextureVertex v{matrix * vertices[i].position, matrix * vertices[i].normal, vertices[i].texCoord};
        vertices.push_back(v);
    }
}
}

Terrain::Terrain(sc::AssetsContainer const& assets)
: sc::SCObject("Terrain", assets.Shaders.getShader("Texture"))
{
    std::vector<sc::TextureVertex> vertices{
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}
    };
    vertices.reserve(24);
    applyMatrixAndAppend(vertices, scmath::Mat4::translate(-0.5f, 0.0f, -0.5f) * scmath::Mat4::rotateY(scmath::degToRad(90)), scmath::Mat4::rotateY(scmath::degToRad(90))); //left
    applyMatrixAndAppend(vertices, scmath::Mat4::translate(0.0f, 0.0f, -1.0f) * scmath::Mat4::rotateY(scmath::degToRad(180)), scmath::Mat4::rotateY(scmath::degToRad(180))); //back
    applyMatrixAndAppend(vertices, scmath::Mat4::translate(0.5f, 0.0f, -0.5f) * scmath::Mat4::rotateY(scmath::degToRad(-90)), scmath::Mat4::rotateY(scmath::degToRad(-90))); //right
    applyMatrixAndAppend(vertices, scmath::Mat4::translate(0.0f, 0.5f, -0.5f) * scmath::Mat4::rotateX(scmath::degToRad(90)), scmath::Mat4::rotateX(scmath::degToRad(90))); //top
    applyMatrixAndAppend(vertices, scmath::Mat4::translate(0.0f, -0.5f, -0.5f) * scmath::Mat4::rotateX(scmath::degToRad(-90)), scmath::Mat4::rotateX(scmath::degToRad(-90))); //bottom

    for (auto &vertex : vertices)
    {
        vertex.position = scmath::Mat4::translate(0.0f, -2.0f, 6.0f) *
            scmath::Mat4::scale(12.0f, 1.0f, 12.0f) * vertex.position;

        // multiplying tex coords will force to repeat texture over the surface
        vertex.texCoord.x *= 6.0f;
        vertex.texCoord.y *= 6.0f;
    }

    auto mesh = std::make_shared<sc::TextureMesh>(vertices, assets.Textures.getTexture("Cobblestone"));
    std::vector<sc::BaseMeshPtr> const meshes{ mesh };
    _model = std::make_shared<sc::Model>(meshes);
    Rigidbody.emplace();
}