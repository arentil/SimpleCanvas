#pragma once

#include <SCMath.h>
#include <glad/glad.h>

namespace sc 
{
class RenderCommand
{
public:
    static void setClearColor(scmath::Vec4 const& color)
    {
        glClearColor(color.x, color.y, color.z, color.w);
    }

    static void drawIndexed(std::shared_ptr<VertexArray> const& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->count(), GL_UNSIGNED_INT, nullptr);
    }

    static void clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
};
} // namespace sc