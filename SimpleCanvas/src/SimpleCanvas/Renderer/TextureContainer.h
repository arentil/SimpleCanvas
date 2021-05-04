#pragma once

#include "Texture.h"
#include "Texture2d.h"
#include "Cubemap.h"

namespace sc
{
class TexturesContainer
{
public:
    TexturesContainer() = default;

    void addTexture(std::string const& textureName, TexturePtr const& texture);
    void addTexture2dFromFile(std::string const& textureName, std::string const& textureFilePath);
    void addCubemapFromFile(std::string const& textureName, std::vector<std::string> const& cubemapFacesFilePaths);
    TexturePtr getTexture(std::string const& textureName) const;

private:
    std::unordered_map<std::string, TexturePtr> _textures;
};
}