#include "DemoOpengl.h"
#include "renderer/OpenglRenderer.h"

namespace pdEngineDemo
{
    DemoOpengl::DemoOpengl()
    {}

    DemoOpengl::~DemoOpengl()
    {}

    pdEngine::Renderer_sptr DemoOpengl::createRenderer()
    {
        return std::make_shared<pdEngine::OpenglRenderer>();
    }
}
