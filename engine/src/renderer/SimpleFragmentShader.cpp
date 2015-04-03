#include "renderer/SimpleFragmentShader.h"

#include <GL/glew.h> 
#include <GL/glu.h> 
#include <SDL_opengl.h> 


namespace pdEngine
{

SimpleFragmentShader::SimpleFragmentShader() {}
SimpleFragmentShader::~SimpleFragmentShader() {}

bool SimpleFragmentShader::compile(void)
{
    return compileBuffer(GL_FRAGMENT_SHADER,
            {
            "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
            });
}
}
