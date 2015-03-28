#ifndef PDDEMO_DEMOAPPLICATION_H_
#define PDDEMO_DEMOAPPLICATION_H_

#include "Application.h"

namespace pdEngineDemo
{
    class DemoSDL : public pdEngine::Application
    {
    public:
        DemoSDL();
        ~DemoSDL();
    protected:
        virtual pdEngine::Renderer_sptr createRenderer() override;
    };
}

#endif /* PDDEMO_DEMOAPPLICATION_H_ */
