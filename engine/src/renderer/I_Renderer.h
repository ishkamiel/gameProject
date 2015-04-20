#pragma once

#include "tasks/Task.h"
#include "math/Matrix4.h"

#include <memory>
#include <string>

namespace pdEngine {

class I_Renderer  : public Task
{
public:
	virtual ~I_Renderer(void) {};

    virtual void onInit(void) noexcept override = 0;
    virtual void onUpdate(const TimeDelta&) noexcept override = 0;

    virtual void v_Render(void) noexcept = 0;

    virtual void printDebugMsg(const std::string&) const = 0;

    virtual void setView(const Matrix4&) noexcept = 0;
    virtual void setProjection(const Matrix4&) noexcept = 0;
};

using Renderer_sptr = std::shared_ptr<I_Renderer>;
}
