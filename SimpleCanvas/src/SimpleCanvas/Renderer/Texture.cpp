#include "Texture.h"

#include <glad/glad.h>

namespace sc
{
Texture2d::Texture2d(std::string const& filePath)
{

}

Texture2dPtr Texture2d::create(std::string const& filePath)
{
    return std::make_shared<Texture2d>(filePath);
}

void Texture2d::bind() const
{

}
} // namespace sc