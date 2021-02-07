#include "Renderer.h"

#include "RenderCommand.h"
#include <SCMath.h>

namespace sc
{
Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData;

void Renderer::beginScene(OrthoCamera &camera)
{
    _sceneData->viewProjMatrix = camera.getViewProjMatrix();
}

void Renderer::submit(std::shared_ptr<VertexArray> const& vertexArray, std::shared_ptr<Shader> const& shader, scmath::Mat4 const& transform)
{
    shader->bind();
    shader->uploadUniformMat4("u_ViewProjection", _sceneData->viewProjMatrix);
    shader->uploadUniformMat4("u_Model", transform);
    vertexArray->bind();
    RenderCommand::drawIndexed(vertexArray);
}

void Renderer::endScene()
{
}
} // namespace sc