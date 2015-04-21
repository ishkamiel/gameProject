#pragma once

#include "actors/ActorComponent.h"

namespace pdEngine
{

class RenderComponent : public ActorComponent
{
const static ActorComponentId s_componentId = 1; // unique ID for this component type

public:
    inline virtual ActorComponentId v_getComponentId(void) const noexcept override;

    virtual void v_postInit(void) noexcept override;

    virtual void v_render(void) noexcept = 0;

};

// Implementations

ActorComponentId RenderComponent::v_getComponentId(void) const noexcept
{
	return RenderComponent::s_componentId;
}

}

