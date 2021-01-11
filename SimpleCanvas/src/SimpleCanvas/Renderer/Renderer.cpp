#include "Renderer.h"

#include "RenderCommand.h"

namespace sc
{
void Renderer::beginScene()
{
}

void Renderer::submit(std::shared_ptr<VertexArray> const& vertexArray)
{
    vertexArray->bind();
    RenderCommand::drawIndexed(vertexArray);
}

void Renderer::endScene()
{
}
} // namespace sc