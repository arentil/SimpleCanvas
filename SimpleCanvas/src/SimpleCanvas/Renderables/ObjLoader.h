#include "Model.h"

namespace sc
{
class ObjLoader
{
public:
    ObjLoader() = default;

    Model loadObjFromFile(std::string const& objFilePath) const;
};
} // namespace sc