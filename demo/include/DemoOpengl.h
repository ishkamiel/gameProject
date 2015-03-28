#ifndef PDDEMO_DEMOOPENGL_H_
#define PDDEMO_DEMOOPENGL_H_

#include "Application.h"

namespace pdEngineDemo
{
    class DemoOpengl : public pdEngine::Application
    {
    public:
        DemoOpengl();
        ~DemoOpengl();
    protected:
        virtual pdEngine::Renderer_sptr createRenderer() override;
    };
}

#endif /* PDDEMO_DEMOOPENGL_H_ */
