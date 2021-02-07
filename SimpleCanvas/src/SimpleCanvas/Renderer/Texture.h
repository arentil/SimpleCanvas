#pragma once

namespace sc
{
class Texture
{
public:
    virtual uint32_t getWidth() const = 0;
    virtual uint32_t getHeight() const = 0;
    virtual void bind() const = 0;
};

class Texture2d;
using Texture2dPtr = std::shared_ptr<Texture2d>;


class Texture2d : public Texture
{
public:
    Texture2d(std::string const& filePath);
    virtual ~Texture2d();

    static Texture2dPtr create(std::string const& filePath);

    virtual uint32_t getWidth() const override { return _width; }
    virtual uint32_t getHeight() const override {return _height; }
    virtual void bind() const override;

private:
    std::string _filePath;
    uint32_t _width, _height;
    uint32_t _rendererId;
};
}