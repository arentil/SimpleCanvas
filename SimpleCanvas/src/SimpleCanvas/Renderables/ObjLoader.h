#pragma once

#include "Model.h"

namespace sc
{
class ObjLoader
{
public:
    static Model loadObjFromFile(std::string const& objFilePath);
};
} // namespace sc