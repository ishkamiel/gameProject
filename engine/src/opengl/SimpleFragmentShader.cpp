#include "opengl/SimpleFragmentShader.h"

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
        "#version 400\n"
        "out vec4 fColor;\n"
        "void main()\n"
        "{\n"
        "	fColor = vec4( 1.0, 1.0, 1.0, 1.0 );\n"
        "}"
    });
}
}
