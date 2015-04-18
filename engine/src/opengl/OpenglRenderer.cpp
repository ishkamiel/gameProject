#include "opengl/OpenglRenderer.h"

#include "Logger.h"

#include "opengl/OpenglUtils.h"

namespace pdEngine {

OpenglRenderer::OpenglRenderer() {
}

OpenglRenderer::~OpenglRenderer() {
}

void OpenglRenderer::v_Render(void) noexcept {
    glClear(GL_COLOR_BUFFER_BIT);

    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_EQUAL);

    m_Thing.render();
}

void OpenglRenderer::onUpdate(const TimeDelta& delta) noexcept
{
    (void)delta;
}

void OpenglRenderer::printDebugMsg(const std::string& msg) const {
    PD_debug(msg);
}

void OpenglRenderer::onInit(void) noexcept {
    auto log = getLogger();

    log->info("We are running opengl {}", epoxy_gl_version());
    fatalOnOpenGLError("OpenGL is in incorrect state");

    glClearColor(0.f, 0.f, 0.f, 1.f);



    m_Thing = SimpleProgram();
    m_Thing.init();

	log->info("Renderer initialization done");
}

}