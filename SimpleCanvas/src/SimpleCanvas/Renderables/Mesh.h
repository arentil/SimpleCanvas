#pragma once

#include "Renderer/Texture2d.h"
#include "BaseMesh.h"
#include "Material.h"


namespace sc
{
struct TextureVertex
{
    scmath::Vec3 position;
    scmath::Vec3 normal;
    scmath::Vec2 texCoord;
};

class TextureMesh : public BaseMesh
{
public:
    TextureMesh(std::vector<TextureVertex> const& vertices, TexturePtr const texturePtr);
    virtual ~TextureMesh() = default;

    virtual void draw(Shader const& shader, Camera const& camera, Material const& diffuse, scmath::Mat4 const& modelMatrix) const override;

private:
    std::vector<TextureVertex> const _vertices;
    TexturePtr _texturePtr;

    void initialize();
};


struct ColorVertex
{
    scmath::Vec3 position;
    scmath::Vec3 normal;
    scmath::Vec3 color;
};

class ColorMesh : public BaseMesh
{
public:
    ColorMesh(std::vector<ColorVertex> const& vertices);
    virtual ~ColorMesh() = default;

    virtual void draw(Shader const& shader, Camera const& camera, Material const& diffuse, scmath::Mat4 const& modelMatrix) const override;

private:
    std::vector<ColorVertex> const _vertices;

    void initialize();
};
} // namespace sc