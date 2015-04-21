#pragma once

#include "actors/ActorComponent.h"

namespace pdEngine
{

class RenderComponent : public ActorComponent
{
const static ActorComponentId s_componentId; // unique ID for this component type

public:
    virtual ActorComponentId v_getComponentId(void) const noexcept override;

    virtual void v_postInit() noexcept override;

    virtual void v_render() noexcept = 0;

};

// Implementations

ActorComponentId RenderComponent::v_getComponentId(void) const noexcept
{
	return s_componentId;
}

}

