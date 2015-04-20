#pragma once

#include "opengl/ShaderProgram.h"

namespace pdEngine
{

class SimpleFragmentShader : public ShaderProgram
{
public:
    SimpleFragmentShader();
    virtual ~SimpleFragmentShader();

    virtual bool compile(void) override;
};

}

