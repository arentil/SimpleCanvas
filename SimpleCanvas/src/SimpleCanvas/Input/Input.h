#pragma once

#include "InputBindings.h"
#include <SCMath.h>

namespace sc 
{
class Input
{
public:
    static bool isKeyPressed(int code);
    static bool isMousePressed(int code);
    static scmath::Vec2 getMousePos();
    static std::string getKeyName(int code);
};
} // namespace sc