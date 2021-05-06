#include "Sponza.h"

Sponza::Sponza(sc::AssetsContainer const& assets) 
: sc::SCObject("Sponza", assets.Shaders.getShader("Texture"))
{
    _model = assets.Models.getModel("Sponza");
    //_modelMatrix = scmath::Mat4::translate(0.0f, -1.0f, 0.0f) * scmath::Mat4::scale(0.01f, 0.01f, 0.01f);
}