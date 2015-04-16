#include "renderer/OpenglRenderer.h"

#include "Logger.h"
#include "opengl/OpenglUtils.h"

namespace pdEngine {

OpenglRenderer::OpenglRenderer() {
}

OpenglRenderer::~OpenglRenderer() {
}

void OpenglRenderer::render(void) const {
    PD_debug("starting render");

    glClear(GL_COLOR_BUFFER_BIT);

    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_EQUAL);

    PD_debug("trying to render the thing");
    m_Thing.render();
}

void OpenglRenderer::printDebugMsg(const std::string& msg) const {
    PD_debug(msg);
}

void OpenglRenderer::init(void) {
    auto log = getLogger();

    // TODO:  log->info("Running OpenGL version: {}", glGetString(GL_VERSION));

    glClearColor(0.f, 0.f, 0.f, 1.f);
    fatalOnOpenGLError("Could not set OpenGL clear color");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    fatalOnOpenGLError("Could not set OpenGL depth testing options");

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    fatalOnOpenGLError("Could not set OpenGL culling options");

    m_Thing = SimpleProgram();
    m_Thing.init();

	log->info("Renderer initialization done");
}

}