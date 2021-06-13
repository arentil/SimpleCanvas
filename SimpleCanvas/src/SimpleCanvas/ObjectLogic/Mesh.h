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
    TextureMesh(TextureMesh const& other);
    virtual ~TextureMesh() = default;
    virtual BaseMeshPtr clone() const override;

    virtual void draw(ShaderPtr shader, CameraController const& camCtrl, Lights const& diffuse, scmath::Mat4 const& modelMatrix) override;

    TexturePtr texturePtr;

private:
    void initialize(std::vector<TextureVertex> const& vertices);
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
    ColorMesh(ColorMesh const& other);
    virtual ~ColorMesh() = default;
    virtual BaseMeshPtr clone() const override;

    virtual void draw(ShaderPtr shader, CameraController const& camCtrl, Lights const& diffuse, scmath::Mat4 const& modelMatrix) override;

private:
    void initialize(std::vector<ColorVertex> const& vertices);
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
    CubemapMesh(CubemapMesh const& other);
    virtual ~CubemapMesh() = default;
    virtual BaseMeshPtr clone() const override;

    virtual void draw(ShaderPtr shader, CameraController const& camCtrl, Lights const& , scmath::Mat4 const& modelMatrix) override;

    TexturePtr texturePtr;

private:
    void initialize(std::vector<CubemapVertex> const& vertices);
};
} // namespace sc