#pragma once

#include <SCMath.h>

#include "Input/InputBindings.h"

namespace sc
{
class Renderer
{
public:
    static void init();
    static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    static void setCursorMode(CursorMode mode);
};
} // namespace sc