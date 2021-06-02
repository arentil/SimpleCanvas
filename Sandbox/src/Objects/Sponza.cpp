#include "Sponza.h"

Sponza::Sponza(sc::AssetsContainer const& assets) 
: sc::SCObject("Sponza", assets.Shaders.getShader("Texture"))
{
    _model = assets.Models.getModel("Sponza");

    Transform.Translation.y = -1.0f;
    Transform.Scale = scmath::Vec3(0.01f, 0.01f, 0.01f);
}