#pragma once

#include "Application.h"

namespace pdEngineDemo
{
    class DemoApplication : public pdEngine::Application
    {
    public:
        DemoApplication();
        ~DemoApplication();

    private:
        virtual void v_preInit(void) noexcept override;
        virtual void v_postInit(void) noexcept override;
    };
}

