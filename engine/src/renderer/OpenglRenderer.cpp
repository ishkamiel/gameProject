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
    DLOG(msg);
}

void OpenglRenderer::init(void) {
    auto log = getLogger();

    log->info("We are running opengl {}", epoxy_gl_version());
    fatalOnOpenGLError("OpenGL is in incorrect state");

    glClearColor(0.f, 0.f, 0.f, 1.f);



    m_Thing = SimpleProgram();
    m_Thing.init();

	log->info("Renderer initialization done");
}

}