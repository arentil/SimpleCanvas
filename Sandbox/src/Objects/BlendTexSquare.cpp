#include "BlendTexSquare.h"

#include <vector>

namespace
{
void applyMatrixAndAppend(std::vector<sc::TextureVertex> &vertices, scmath::Mat4 const& matrix, scmath::Mat4 const& normalMatrix)
{
    for (size_t i = 0; i < 6; i++)
    {
        sc::TextureVertex v{matrix * vertices[i].position, normalMatrix * vertices[i].normal, vertices[i].texCoord};
        vertices.push_back(v);
    }
}
}

BlendTexSquare::BlendTexSquare(sc::AssetsContainer const& assets) 
: sc::SCObject("BlendTexSquare", assets.Shaders.getShader("Texture"))
{
    std::vector<sc::TextureVertex> vertices{
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}
    };

    auto mesh = std::make_shared<sc::TextureMesh>(vertices, assets.Textures.getTexture("Blend"));
    std::vector<sc::BaseMeshPtr> const meshes{ mesh };
    _model = std::make_shared<sc::Model>(meshes);
}