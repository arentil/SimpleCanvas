#pragma once

#include "Texture.h"

namespace sc
{
class Texture2d : public Texture
{
public:
    Texture2d(std::string const& filePath);
    virtual ~Texture2d() = default;

    static TexturePtr create(std::string const& filePath);

    uint32_t getWidth() const { return _width; }
    uint32_t getHeight() const {return _height; }
    std::string getFilePath() const;
    virtual void bind() const override;

private:
    std::string const _filePath;
    int _width, _height;
};
}