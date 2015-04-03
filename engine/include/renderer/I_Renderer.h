#ifndef PDENGINE_RENDERER_H_
#define PDENGINE_RENDERER_H_

#include <memory>
#include <string>

namespace pdEngine
{
    class I_Renderer;
    using Renderer_sptr = std::shared_ptr<I_Renderer>;

    class I_Renderer
    {
    public:
		virtual void init(void);
        virtual void render(void) const;
        virtual void printDebugMsg(const std::string&) const;
    };
}
#endif /* PDENGINE_RENDERER_H_ */
