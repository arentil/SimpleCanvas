#include "Renderer.h"

#include "RenderCommand.h"

namespace sc
{
void Renderer::init()
{
    RenderCommand::init();
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