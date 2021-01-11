#pragma once

#include "SCMath/SCMath.h"

#include "VertexArray.h"

namespace sc
{
class Renderer
{
public:
    static void beginScene();
    static void submit(std::shared_ptr<VertexArray> const& vertexArray);
    static void endScene();
};
} // namespace sc