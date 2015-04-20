#pragma once

#include "opengl/ShaderProgram.h"

namespace pdEngine
{
class SimpleVertexShader : public ShaderProgram
{
public:
    SimpleVertexShader ();
    virtual ~SimpleVertexShader();

    virtual bool compile(void) override;
};
}

