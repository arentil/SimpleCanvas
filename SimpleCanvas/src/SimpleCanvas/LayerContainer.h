#pragma once

#include "Core.h"
#include "Layer.h"

namespace sc 
{
class LayerContainer
{
public:
	LayerContainer();
	~LayerContainer();

	void pushLayer(Layer * layer);
	void pushOverlay(Layer * overlay);
	void popLayer(Layer * layer);
	void popOverlay(Layer * overlay);

	std::vector<Layer *>::iterator begin() { return layers.begin(); }
	std::vector<Layer *>::iterator end() { return layers.end(); }

private:
	std::vector<Layer *> layers;
	std::vector<Layer *>::iterator layerInsert;
};
} // namespace sc