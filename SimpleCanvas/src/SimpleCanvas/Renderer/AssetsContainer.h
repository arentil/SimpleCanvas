#pragma once

#include "TextureContainer.h"
#include "Shader.h"
#include "Renderables/Model.h"

namespace sc
{
struct AssetsContainer
{
    ShadersContainer Shaders;
    ModelsContainer Models;
    TexturesContainer Textures;
};
} // namespace sc