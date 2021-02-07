#pragma once

#include <SCMath.h>

#include "VertexArray.h"
#include "OrthoCamera.h"
#include "Shader.h"

namespace sc
{
class Renderer
{
public:
    static void beginScene(OrthoCamera &camera);
    static void submit(VertexArrayPtr const& vertexArray, ShaderPtr const& shader, scmath::Mat4 const& transform = scmath::Mat4::identity());
    static void endScene();

private:
    struct SceneData
    {
        scmath::Mat4 viewProjMatrix;
    };

    static SceneData *_sceneData;
};
} // namespace sc