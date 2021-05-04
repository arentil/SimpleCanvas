#include "Terrain.h"

#include <vector>

Terrain::Terrain(sc::AssetsContainer const& assets)
: sc::SCObject("Terrain", assets.Shaders.getShader("FlatColor"))
{
    _model = std::make_shared<sc::Model>();
}