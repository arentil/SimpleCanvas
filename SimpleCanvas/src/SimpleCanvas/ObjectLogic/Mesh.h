#pragma once

#include "Renderer/Texture2d.h"
#include "ObjectLogic/BaseMesh.h"
#include "ObjectLogic/Lights.h"

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
    TextureMesh(std::vector<TextureVertex> const& vertices, TexturePtr texturePtr);
    virtual ~TextureMesh() = default;

    virtual void draw(ShaderPtr shader, FPSCamera const& camera, Lights const& diffuse, scmath::Mat4 const& modelMatrix) override;

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

    virtual void draw(ShaderPtr shader, FPSCamera const& camera, Lights const& diffuse, scmath::Mat4 const& modelMatrix) override;

private:
    std::vector<ColorVertex> const _vertices;

    void initialize();
};

struct CubemapVertex
{
    scmath::Vec3 position;
    scmath::Vec2 texCoord;
};

class CubemapMesh : public BaseMesh
{
public:
    CubemapMesh(std::vector<CubemapVertex> const& vertices, TexturePtr texturePtr);
    virtual ~CubemapMesh() = default;

    virtual void draw(ShaderPtr shader, FPSCamera const& camera, Lights const& , scmath::Mat4 const& modelMatrix) override;

private:
    std::vector<CubemapVertex> const _vertices;
    TexturePtr _texturePtr;
    void initialize();
};
} // namespace sc