#include "Texture2d.h"

#include <cassert>

#include "Tools/stb_image.h"

namespace sc
{
namespace
{
std::string replaceSystemSlashes(std::string const& str)
{
    std::string result = str;

    char toFind;
    char replaceWith;
    #ifdef _WIN32
        toFind = '/';
        replaceWith = '\\';
    #else
        toFind = '\\';
        replaceWith = '/';
    #endif

    std::replace(result.begin(), result.end(), toFind, replaceWith);
    return result;
}
} // namespace

Texture2d::Texture2d(std::string const& filePath)
: _filePath(replaceSystemSlashes(filePath))
{
    int channels;
    stbi_set_flip_vertically_on_load(true);
    stbi_uc* data = stbi_load(_filePath.c_str(), &_width, &_height, &channels, 0);
    
    SC_ASSERT(data, "%s() stbi returned null texture!", __FUNCTION__);

    GLenum internalFormat = 0, dataFormat = 0;
    if (channels == 4)  // RGBA
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    }
    else if (channels == 3) // RGB
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

    SC_ASSERT(internalFormat & dataFormat);

    glCreateTextures(GL_TEXTURE_2D, 1, &textureId);
    glTextureStorage2D(textureId, 1, internalFormat, _width, _height);    // generate texture
    glTextureParameteri(textureId, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(textureId, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(textureId, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(textureId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureSubImage2D(textureId, 0, 0, 0, _width, _height, dataFormat, GL_UNSIGNED_BYTE, data); // fill texture with data

    stbi_image_free(data);
}

TexturePtr Texture2d::create(std::string const& filePath)
{
    return std::make_shared<Texture2d>(filePath);
}

std::string Texture2d::getFilePath() const
{
    return _filePath;
}

void Texture2d::bind() const
{
    glBindTexture(GL_TEXTURE_2D, textureId);
}
} // namespace sc