#include "Renderer.h"

#include "RenderCommand.h"

namespace sc
{
Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData;

void Renderer::beginScene(OrthoCamera &camera)
{
    _sceneData->viewProjMatrix = camera.getViewProjMatrix();
}

void Renderer::submit(std::shared_ptr<VertexArray> const& vertexArray, std::shared_ptr<Shader> const& shader)
{
    shader->bind();
    shader->uploadUniformMat4("u_ViewProjection", _sceneData->viewProjMatrix);
    vertexArray->bind();
    RenderCommand::drawIndexed(vertexArray);
}

void Renderer::endScene()
{
}
} // namespace sc