#pragma once

#include <SCMath.h>

#include "VertexArray.h"
#include "Camera.h"
#include "Shader.h"
#include "Input/InputBindings.h"

namespace sc
{
class Renderer
{
public:
    static void init();
    static void beginScene(Camera const& camera);
    static void endScene();
    static void submit(VertexArrayPtr const& vertexArray, ShaderPtr const& shader, scmath::Mat4 const& modelMatrix = scmath::Mat4::identity());
    static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    static void setCursorMode(CursorMode mode);

private:
    struct SceneData
    {
        scmath::Mat4 viewProjMatrix;
    };

    static SceneData *_sceneData;
};
} // namespace sc