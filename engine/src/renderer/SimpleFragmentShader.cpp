#include "renderer/SimpleFragmentShader.h"

#include <GL/glew.h> 
#include <GL/glu.h> 
#include <SDL_opengl.h> 


namespace pdEngine {

SimpleFragmentShader::SimpleFragmentShader() {
}

SimpleFragmentShader::~SimpleFragmentShader() {
}

bool SimpleFragmentShader::compile(void) {
    return compileBuffer(GL_FRAGMENT_SHADER,{
        "#version 140\n"
        "out vec4 LFragment;\n"
        "void main()\n"
        "{\n"
        "	LFragment = vec4( 1.0, 1.0, 1.0, 1.0 );\n"
        "}"
    });
}
}
