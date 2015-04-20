#pragma once

#include "renderer/I_Renderer.h"

namespace pdEngine {

class I_Window {
public:
	virtual ~I_Window() {}
    virtual void openWindow(void) =0;
	virtual Renderer_sptr createRenderer() =0;
	virtual void swapFrame(void) =0;

	virtual void setTitle(const std::string&) noexcept =0;
};

using Window_sptr = std::shared_ptr<I_Window>;
}

