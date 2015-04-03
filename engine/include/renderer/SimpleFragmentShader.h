#ifndef SIMPLEFRAGMENTSHADER_H_
#define SIMPLEFRAGMENTSHADER_H_

#include "renderer/ShaderProgram.h"

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


#endif /* SIMPLEFRAGMENTSHADER_H_ */
