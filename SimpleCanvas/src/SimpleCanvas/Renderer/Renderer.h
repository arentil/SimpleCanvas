#pragma once

#include <SCMath.h>

#include "VertexArray.h"
#include "Camera.h"
#include "Shader.h"

namespace sc
{
class Renderer
{
public:
    static void init();
    static void beginScene(Camera const& camera);
    static void submit(VertexArrayPtr const& vertexArray, ShaderPtr const& shader, scmath::Mat4 const& transform = scmath::Mat4::identity());
    static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    static void endScene();

private:
    struct SceneData
    {
        scmath::Mat4 viewProjMatrix;
    };

    static SceneData *_sceneData;
};
} // namespace sc