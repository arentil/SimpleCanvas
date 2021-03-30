#pragma once

namespace sc
{
class Texture2d;
using Texture2dPtr = std::shared_ptr<Texture2d>;

class Texture2d
{
public:
    Texture2d(std::string const& filePath);
    virtual ~Texture2d();

    static Texture2dPtr create(std::string const& filePath);

    uint32_t getWidth() const { return _width; }
    uint32_t getHeight() const {return _height; }
    std::string getFilePath() const;
    void bind(uint32_t slot = 0) const;

protected:
    std::string const _filePath;
    uint32_t _width, _height;
    uint32_t _rendererId;
};
}