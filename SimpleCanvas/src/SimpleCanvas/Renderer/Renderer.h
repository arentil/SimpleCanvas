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
    static void submit(std::shared_ptr<VertexArray> const& vertexArray, std::shared_ptr<Shader> const& shader);
    static void endScene();

private:
    struct SceneData
    {
        scmath::Mat4 viewProjMatrix;
    };

    static SceneData *_sceneData;
};
} // namespace sc