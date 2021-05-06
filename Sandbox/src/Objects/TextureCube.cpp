#include "TextureCube.h"

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

TextureCube::TextureCube(sc::AssetsContainer const& assets) 
: sc::SCObject("TextureCube", assets.Shaders.getShader("Texture"))
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

    auto mesh = std::make_shared<sc::TextureMesh>(vertices, assets.Textures.getTexture("Chess"));
    std::vector<sc::BaseMeshPtr> const meshes{ mesh };
    _model = std::make_shared<sc::Model>(meshes);

	Transform.Translation = scmath::Vec3(3.0f, 0.0f, 2.0f);
    //_modelMatrix = scmath::Mat4::translate(pos) * scmath::Mat4::rotateY(scmath::degToRad(45.0f));
}