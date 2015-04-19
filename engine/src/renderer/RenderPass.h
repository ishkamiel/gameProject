#ifndef RENDERPASS_H_
#define RENDERPASS_H_

#include <cstdint>

namespace pdEngine
{

enum class RenderPass : std::uint8_t
    {
        First = 0,
        Static = 1,
        Actor= 2,
        Sky = 3,
        NotRendered = 4,
        Last = 5
    };

}

#endif /* RENDERPASS_H_ */
