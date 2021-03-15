#include "Renderer.h"

#include "RenderCommand.h"

namespace sc
{
Renderer::SceneData* Renderer::_sceneData = new Renderer::SceneData;

void Renderer::init()
{
    RenderCommand::init();
}

void Renderer::beginScene(Camera const& camera)
{
    _sceneData->viewProjMatrix = camera.getViewProjMatrix();
}

void Renderer::endScene()
{}

void Renderer::submit(VertexArrayPtr const& vertexArray, ShaderPtr const& shader, scmath::Mat4 const& modelMatrix)
{
    shader->bind();
    shader->uploadUniformMat4("u_ViewProjection", _sceneData->viewProjMatrix);
    shader->uploadUniformMat4("u_Model", modelMatrix);
    vertexArray->bind();
    RenderCommand::drawIndexed(vertexArray);
}

void Renderer::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
    RenderCommand::setViewport(x, y, width, height);
}

void Renderer::setCursorMode(CursorMode mode)
{
    RenderCommand::setCursorMode(mode);
}
} // namespace sc