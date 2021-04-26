#include "TileMap.h"

#include <vector>

namespace
{
void applyMatrixAndAppend(std::vector<sc::ColorVertex> &vertices, scmath::Mat4 const& matrix)
{
   for (int i = 0; i < 6; i++)
   {
       sc::ColorVertex newVertex{matrix * vertices[i].position, vertices.front().normal, vertices.front().color};
       vertices.push_back(newVertex);
   }
}
}

TileMap::TileMap(sc::Shader const& shader, sc::Camera const& camera) 
: _shader(shader), _camera(camera)
{
    std::vector<sc::ColorVertex> vertices{
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.2f, 0.3f, 0.8f}},
        {{0.5f, -0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {0.2f, 0.3f, 0.8f}},
        {{0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {0.2f, 0.3f, 0.8f}},
        {{0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {0.2f, 0.3f, 0.8f}},
        {{-0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {0.2f, 0.3f, 0.8f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.2f, 0.3f, 0.8f}}
    };

    scmath::Mat4 scale = scmath::Mat4::scale(scmath::Vec3(0.1f, 0.1f, 0.1f));
    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 20; y++)
        {
            scmath::Vec3 pos(x * 0.11f, y * 0.11f, -0.4f);
            scmath::Mat4 transform = scmath::Mat4::translate(pos) * scale;
            applyMatrixAndAppend(vertices, transform);            
        }
    }

    vertices.erase(vertices.begin());
    vertices.erase(vertices.begin());
    vertices.erase(vertices.begin());
    vertices.erase(vertices.begin());
    vertices.erase(vertices.begin());
    vertices.erase(vertices.begin());

    auto mesh = std::make_shared<sc::ColorMesh>(vertices);
    std::vector<sc::BaseMeshPtr> const meshes{ mesh };
    _model = std::make_shared<sc::Model>(meshes);
}

void TileMap::draw(sc::Lights const& material, scmath::Mat4 const& modelMatrix) const
{
    _model->draw(_shader, _camera, material, modelMatrix);
}