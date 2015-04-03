#ifndef PDENGINE_RENDERER_H_
#define PDENGINE_RENDERER_H_

#include <memory>
#include <string>

namespace pdEngine {

class I_Renderer {
public:
    virtual void init(void) = 0;
    virtual void render(void) const = 0;
    virtual void printDebugMsg(const std::string&) const = 0;
};

using Renderer_sptr = std::shared_ptr<I_Renderer>;
}
#endif /* PDENGINE_RENDERER_H_ */
