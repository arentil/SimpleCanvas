#pragma once

#include "SimpleCanvas/Core.h"
#include "InputBindings.h"

namespace sc 
{
class SC_API Input
{
public:
    static bool isKeyPressed(int code);
    static bool isMousePressed(int code);
    static std::string getKeyName(int code);

    // TODO: TO BE CHANGED INTO VECTOR2
    static std::pair<float, float> getMousePos();
};
} // namespace sc