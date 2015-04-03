#include "renderer/OpenglRenderer.h"

#include "Logger.h"
#include "Utils.h"
#include "renderer/SimpleVertexShader.h"
#include "renderer/SimpleFragmentShader.h"
#include "renderer/OpenglUtils.h"
#include "exceptions/OpenglException.h"

namespace pdEngine {

OpenglRenderer::OpenglRenderer() {
}

OpenglRenderer::~OpenglRenderer() {
}

void OpenglRenderer::render(void) const {
    //Clear color buffer 
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_programID);
    glEnableVertexAttribArray(gVertexPos2DLocation);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof (GLfloat), NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);

    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
    glDisableVertexAttribArray(gVertexPos2DLocation);

    glUseProgram(0);
}

void OpenglRenderer::printDebugMsg(const std::string& msg) const {
    DLOG(msg);
}

void OpenglRenderer::init(void) {
    auto log = getLogger();

    m_programID = glCreateProgram();

    log->debug("Compiling vertex shader");
    SimpleVertexShader vertexShader{};
    vertexShader.load();
    vertexShader.compile();

    log->debug("Compiling fragment shader");

    SimpleFragmentShader fragmentShader{};
    fragmentShader.load();
    fragmentShader.compile();

    // Link program
    glAttachShader(m_programID, vertexShader.getID());
    glAttachShader(m_programID, fragmentShader.getID());
    glLinkProgram(m_programID);

    // check program
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &programSuccess);
    if (programSuccess != GL_TRUE) {
		throw OpenglException(m_programID);
        //log->error("Error linking opengGL program {0}", m_programID);
        //printGLLog(m_programID);
        //throw std::runtime_error("openGL linking error");
    }

    gVertexPos2DLocation = glGetAttribLocation(m_programID, "LVertexPos2D");
    if (gVertexPos2DLocation == -1) {
        log->error("LVertexPos2DLocation is not a valid glsl program variable");
        throw std::runtime_error("glsl error");
    }

    glClearColor(0.f, 0.f, 0.f, 1.f);

    // VBO data
    GLfloat vertexData[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f
    };

    // IBO data 
    GLuint indexData[] = {0, 1, 2, 3};

    //Create VBO 
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof (GLfloat), vertexData, GL_STATIC_DRAW);

    //Create IBO 
    glGenBuffers(1, &gIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof (GLuint), indexData, GL_STATIC_DRAW);

	log->info("Renderer initialization done");
}

}