#include "ColorCube.h"

#include <vector>

namespace
{
void applyMatrixAndAppend(std::vector<sc::ColorVertex> &vertices, scmath::Mat4 const& matrix, scmath::Mat4 const& normalMatrix)
{
    for (size_t i = 0; i < 6; i++)
    {
        sc::ColorVertex v{matrix * vertices[i].position, normalMatrix * vertices[i].normal, vertices[i].color};
        vertices.push_back(v);
    }
}
}

ColorCube::ColorCube(sc::AssetsContainer const& assets) 
: sc::SCObject("ColorCube", assets.Shaders.getShader("FlatColor"))
{
    std::vector<sc::ColorVertex> vertices{
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
        {{0.5f, -0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
        {{0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.5f, 0.0f},  {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}
    };
    vertices.reserve(24);
    applyMatrixAndAppend(vertices, scmath::Mat4::translate(-0.5f, 0.0f, -0.5f) * scmath::Mat4::rotateY(scmath::degToRad(90)), scmath::Mat4::rotateY(scmath::degToRad(90))); //left
    applyMatrixAndAppend(vertices, scmath::Mat4::translate(0.0f, 0.0f, -1.0f) * scmath::Mat4::rotateY(scmath::degToRad(180)), scmath::Mat4::rotateY(scmath::degToRad(180))); //back
    applyMatrixAndAppend(vertices, scmath::Mat4::translate(0.5f, 0.0f, -0.5f) * scmath::Mat4::rotateY(scmath::degToRad(-90)), scmath::Mat4::rotateY(scmath::degToRad(-90))); //right
    applyMatrixAndAppend(vertices, scmath::Mat4::translate(0.0f, 0.5f, -0.5f) * scmath::Mat4::rotateX(scmath::degToRad(90)), scmath::Mat4::rotateX(scmath::degToRad(90))); //top
    applyMatrixAndAppend(vertices, scmath::Mat4::translate(0.0f, -0.5f, -0.5f) * scmath::Mat4::rotateX(scmath::degToRad(-90)), scmath::Mat4::rotateX(scmath::degToRad(-90))); //bottom

    auto mesh = std::make_shared<sc::ColorMesh>(vertices);
    std::vector<sc::BaseMeshPtr> const meshes{ mesh };
    _model = std::make_shared<sc::Model>(meshes);
}

void ColorCube::onAnimate(float deltaTime) 
{
    rotationAngle += scmath::degToRad(rotationSpeed) * deltaTime;
    _modelMatrix = scmath::Mat4::translate(pos) * scmath::Mat4::rotateZ(rotationAngle) * scmath::Mat4::scale(scmath::Vec3(0.3f, 0.3f, 0.3f));
}