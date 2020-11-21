#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace sc
{
namespace
{
static int LAYER_COUNTER = 0;
static std::string defaultLayerName() 
{ 
	return "Layer" + std::to_string(LAYER_COUNTER); 
	LAYER_COUNTER++; 
}
} // namespace

class SC_API Layer
{
public:
	Layer(std::string const& pName = defaultLayerName());

	virtual void attach() {};
	virtual void detach() {};
	virtual void update() {};
	virtual void onEvent(Event &event) {};

	inline const std::string& getName() const { return name; }

protected:
	std::string name;
};
} // namespace sc