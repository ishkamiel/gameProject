/* 
 * File:   SimpleVertexShader.h
 * Author: ishkamiel
 *
 * Created on April 3, 2015, 9:15 AM
 */

#ifndef SIMPLEVERTEXSHADER_H
#define	SIMPLEVERTEXSHADER_H

#include "renderer/ShaderProgram.h"

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


#endif	/* SIMPLEVERTEXSHADER_H */

