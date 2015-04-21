#pragma once

#include "actors/RenderComponent.h"

namespace pdEngine
{

class SimpleMarker : public RenderComponent
{
	const static ActorComponentId s_componentId;

public:
	SimpleMarker();

	virtual ~SimpleMarker();

	virtual void v_render() noexcept = 0;
};

}
