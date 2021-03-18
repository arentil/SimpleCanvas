#pragma once

#include <memory>

namespace sc
{
class Cubemap;
using CubemapPtr = std::shared_ptr<Cubemap>;

class Cubemap
{
public:
    Cubemap(std::vector<std::string> const& facesFilePaths);
    virtual ~Cubemap();

    void bind();

protected:
    uint32_t _rendererId;
};
} // namespace sc