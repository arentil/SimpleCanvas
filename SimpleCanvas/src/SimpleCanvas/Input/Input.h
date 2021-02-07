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
    static std::string getKeyName(int code);

    // TODO: TO BE CHANGED INTO VECTOR2
    static scmath::Vec2 getMousePos();
};
} // namespace sc