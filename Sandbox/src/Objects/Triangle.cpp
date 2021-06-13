#include "Triangle.h"

#include <vector>

Triangle::Triangle(sc::AssetsContainer const& assets)
: sc::SCObject("Triangle", assets.Shaders.getShader("Color"))
{
    std::vector<sc::ColorVertex> const vertices{
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
        {{0.0f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f}}
    };

    auto mesh = std::make_shared<sc::ColorMesh>(vertices);
    std::vector<sc::BaseMeshPtr> const meshes{ mesh };
    _model = std::make_shared<sc::Model>(meshes);

    Transform.Translation = scmath::Vec3(4.0f, 0.0f, 0.0f);
    Transform.Scale = scmath::Vec3(2.0f, 2.0f, 2.0f);
}

void Triangle::onUpdate()
{
    Transform.Rotation.z += scmath::degToRad(50) * deltaTime;
}