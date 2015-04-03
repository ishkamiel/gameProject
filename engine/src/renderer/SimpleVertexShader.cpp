#include "renderer/SimpleVertexShader.h"

#include <GL/glew.h> 
#include <GL/glu.h> 
#include <SDL_opengl.h> 


namespace pdEngine
{

SimpleVertexShader::SimpleVertexShader() {}
SimpleVertexShader::~SimpleVertexShader() {}

bool SimpleVertexShader::compile(void)
{
    GLchar source[] =
    {
        "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
    };


    return compileBuffer(GL_VERTEX_SHADER, source);
}
}
