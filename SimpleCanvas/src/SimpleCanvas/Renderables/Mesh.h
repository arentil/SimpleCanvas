#pragma once

#include "Renderer/Shader.h"
#include "Renderer/Camera.h"
#include "Renderer/Texture.h"

#include <SCMath.h>

namespace sc
{
struct Vertex
{
    scmath::Vec3 position;
    scmath::Vec3 normal;
    scmath::Vec2 texCoord;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> const& vertices, std::shared_ptr<Texture2d> texturePtr);
    ~Mesh() = default;

    void draw(Shader const& shader, Camera const& camera, scmath::Mat4 const& modelMatrix) const;

private:
    std::vector<Vertex> const _vertices;
    std::shared_ptr<Texture2d> _texturePtr;

    uint32_t VAO, VBO;

    void initialize();
};
} // namespace sc