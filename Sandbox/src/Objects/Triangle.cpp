#include "Triangle.h"

#include <vector>

Triangle::Triangle(sc::Shader const& shader)
: sc::SCObject("Triangle", shader)
{
    std::vector<sc::ColorVertex> const vertices{
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
        {{0.0f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f}}
    };

    auto mesh = std::make_shared<sc::ColorMesh>(vertices);
    std::vector<sc::BaseMeshPtr> const meshes{ mesh };
    _model = std::make_shared<sc::Model>(meshes);
}

void Triangle::onAnimate(float deltaTime) 
{
    rotationTriangle += scmath::degToRad(rotationTriangleSpeed) * deltaTime;
    scmath::Vec3 tranlPos(1.0f, 0.0f, 0.0f);
    _modelMatrix = scmath::Mat4::rotate(rotationTriangle, rotateAxis) * scmath::Mat4::translate(tranlPos) * scmath::Mat4::scale(scmath::Vec3(0.3f, 0.3f, 0.3f));
}