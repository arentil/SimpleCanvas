#include "Texture.h"

#include <cassert>

#include <glad/glad.h>
#include "Utils/stb_image.h"


namespace sc
{
Texture2d::Texture2d(std::string const& filePath)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
    assert(data);
    _width = width;
    _height = height;

    glCreateTextures(GL_TEXTURE_2D, 1, &_rendererId);
    glTextureStorage2D(_rendererId, 1, GL_RGB8, _width, _height);

    glTextureParameteri(_rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(_rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureSubImage2D(_rendererId, 0, 0, 0, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

Texture2d::~Texture2d()
{
    glDeleteTextures(1, &_rendererId);
}

Texture2dPtr Texture2d::create(std::string const& filePath)
{
    return std::make_shared<Texture2d>(filePath);
}

void Texture2d::bind(uint32_t slot) const
{
    glBindTextureUnit(slot, _rendererId);
}
} // namespace sc