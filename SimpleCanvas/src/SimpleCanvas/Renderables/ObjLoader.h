#pragma once

namespace sc
{
class Model;
using ModelPtr = std::shared_ptr<Model>;

class ObjLoader
{
public:
    static ModelPtr loadObjFromFile(std::string const& objFilePath);
};
} // namespace sc