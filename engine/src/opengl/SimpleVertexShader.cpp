#include "opengl/SimpleVertexShader.h"

#include <GL/glew.h> 
#include <GL/glu.h> 
#include <SDL_opengl.h> 


namespace pdEngine {

SimpleVertexShader::SimpleVertexShader() {
}

SimpleVertexShader::~SimpleVertexShader() {
}

bool SimpleVertexShader::compile(void) {
    return compileBuffer(GL_VERTEX_SHADER,{
        "#version 400\n"
		"layout(location=0) in vec4 Vertex;\n"
        "uniform mat4 View;\n"
        "uniform mat4 Project;\n"
		"uniform mat4 Model;\n"
        "void main() {\n"
        "	gl_Position = Project * View * Model * Vertex;\n"
        "}"
    });
}

}
