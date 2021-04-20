#pragma once

namespace sc
{
class Model;

class ObjLoader
{
public:
    static Model loadObjFromFile(std::string const& objFilePath);
};
} // namespace sc