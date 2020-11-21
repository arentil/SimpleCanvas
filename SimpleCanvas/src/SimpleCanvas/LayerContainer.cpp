#include "LayerContainer.h"

namespace sc 
{
LayerContainer::LayerContainer()
{
	layerInsert = layers.begin();
}

LayerContainer::~LayerContainer()
{
	for (Layer * layer : layers)
		delete layer;
}

void LayerContainer::pushLayer(Layer * layer)
{
	layerInsert = layers.emplace(layerInsert, layer);
}

void LayerContainer::pushOverlay(Layer * overlay)
{
	layers.emplace_back(overlay);
}

void LayerContainer::popLayer(Layer * layer)
{
	auto it = std::find(layers.begin(), layers.end(), layer);	// find by address of an object
	if (it != layers.end())
	{
		layers.erase(it);
		layerInsert--;
	}
}

void LayerContainer::popOverlay(Layer * overlay)
{
	auto it = std::find(layers.begin(), layers.end(), overlay);	// find by address of an object
	if (it != layers.end())
		layers.erase(it);
}
} // namespace sc