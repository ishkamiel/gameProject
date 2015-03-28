#include "DemoSDL.h"
#include "renderer/SDLRenderer.h"

namespace pdEngineDemo
{
    DemoSDL::DemoSDL()
    {}

    DemoSDL::~DemoSDL()
    {}

    pdEngine::Renderer_sptr DemoSDL::createRenderer()
    {
        return std::make_shared<pdEngine::SDLRenderer>();
    }
}
