#pragma once

#include <glad/glad.h>

namespace sc
{
class Texture;
using TexturePtr = std::shared_ptr<Texture>;

class Texture
{
public:
    virtual ~Texture()
    {
        glDeleteTextures(1, &textureId);
    }

    virtual void bind() const = 0;

protected:
    uint32_t textureId;
};
}