#pragma once

#include <SCMath.h>
#include <glad/glad.h>

#include "Renderer/VertexArray.h"

namespace sc 
{
class RenderCommand
{
public:
    static void init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
        
    }

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
};
} // namespace sc