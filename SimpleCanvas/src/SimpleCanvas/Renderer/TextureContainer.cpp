#include "TextureContainer.h"

namespace sc
{
void TexturesContainer::addTexture(std::string const& textureName, TexturePtr const& texture) 
{
    if (_textures.find(textureName) != _textures.end())
    {
        LOG_WARNING("%s() %s texture already exist! Skipping...", __FUNCTION__, textureName.c_str());
        return;
    }
    _textures.emplace(textureName, texture);
}

void TexturesContainer::addTexture2dFromFile(std::string const& textureName, std::string const& textureFilePath) 
{
    if (_textures.find(textureName) != _textures.end())
    {
        LOG_WARNING("%s() %s texture already exist! Skipping...", __FUNCTION__, textureName.c_str());
        return;
    }
    _textures.emplace(textureName, Texture2d::create(textureFilePath));
}

void TexturesContainer::addCubemapFromFile(std::string const& textureName, std::vector<std::string> const& cubemapFacesFilePaths) 
{
    if (_textures.find(textureName) != _textures.end())
    {
        LOG_WARNING("%s() %s cubemap already exist! Skipping...", __FUNCTION__, textureName.c_str());
        return;
    }
    _textures.emplace(textureName, Cubemap::create(cubemapFacesFilePaths));
}

TexturePtr TexturesContainer::getTexture(std::string const& textureName) const
{
    if (_textures.find(textureName) == _textures.end())
    {
        LOG_ERROR("%s() %s texture does not exist! Skipping...", __FUNCTION__, textureName.c_str());
        return nullptr;
    }

    return _textures.at(textureName);
}
} // namespace sc