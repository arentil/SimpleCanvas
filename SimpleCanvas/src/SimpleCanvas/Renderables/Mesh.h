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
    Mesh(std::vector<Vertex> const& vertices, std::vector<uint32_t> const& indices, Texture2d const& texture);
    ~Mesh() = default;

    void draw(Shader const& shader, Camera const& camera, scmath::Mat4 const& modelMatrix) const;

private:
    std::vector<Vertex> const _vertices;
    std::vector<uint32_t> const _indices;
    Texture2d const& _texture;

    uint32_t VAO, VBO, EBO;

    void initialize();
};
} // namespace sc