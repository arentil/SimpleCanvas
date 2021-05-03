#include "Terrain.h"

#include <vector>

Terrain::Terrain(sc::Shader const& shader)
: sc::SCObject("Terrain", shader)
{
    _model = std::make_shared<sc::Model>();
}