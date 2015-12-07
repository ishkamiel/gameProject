#include "DemoApplication.h"
#include "actors/ActorFactory.h"

namespace pdEngineDemo
{

DemoApplication::DemoApplication() {}
DemoApplication::~DemoApplication() {}

void DemoApplication::v_preInit(void) noexcept
{
}

void DemoApplication::v_postInit(void) noexcept
{
	// auto actorFactory = std::make_unique<pdEngine::ActorFactory>();
	// actorFactory->addComponentCreator()
}

}
