#pragma once

#include <memory>

#include "Texture.h"

namespace sc
{
class Cubemap : public Texture
{
public:
    Cubemap(std::vector<std::string> const& facesFilePaths);
    virtual ~Cubemap() = default;

    virtual void bind() const override;
    static TexturePtr create(std::vector<std::string> const& facesFilePaths);
};
} // namespace sc