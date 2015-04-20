#include "opengl/OpenglRenderer.h"

#include "math/Frustum.h"
#include "math/Matrix4.h"
#include "opengl/OpenglUtils.h"
#include "opengl/SimpleFragmentShader.h"
#include "opengl/SimpleVertexShader.h"
#include "renderer/CameraNode.h"
#include "Logger.h"
#include "Utils.h"

namespace pdEngine {

OpenglRenderer::OpenglRenderer() {
}

OpenglRenderer::~OpenglRenderer() {
    safeDelete(m_Scene);
}

void OpenglRenderer::v_Render(void) noexcept {
    glClear(GL_COLOR_BUFFER_BIT);

    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_EQUAL);

    m_Scene->onRender();
    m_Thing.render();
}

void OpenglRenderer::onUpdate(const TimeDelta& delta) noexcept
{
    m_Scene->onUpdate(delta);
}

void OpenglRenderer::printDebugMsg(const std::string& msg) const {
    PD_debug(msg);
}

void OpenglRenderer::onInit(void) noexcept {
    Task::onInit();
    auto log = getLogger();

    log->info("We are running opengl {}", epoxy_gl_version());
    fatalOnOpenGLError("OpenGL is in incorrect state");

    loadShaderProgram();

    glClearColor(0.f, 0.f, 0.f, 1.f);

    m_Scene = new Scene(this);

    auto camera = std::make_shared<CameraNode>(
        Matrix4(),
        Frustum(90, 4.f/3.f, 0.f, 100.f));

    //m_Thing = SimpleProgram();
    //m_Thing.init();

	log->info("Renderer initialization done");
}

void OpenglRenderer::loadShaderProgram(void) noexcept
{
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

    log->debug("Linking OpenGL program");
    glAttachShader(m_programID, vertexShader.getID());
    glAttachShader(m_programID, fragmentShader.getID());
    glLinkProgram(m_programID);

    GLint programSuccess = GL_TRUE;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &programSuccess);
    if (programSuccess != GL_TRUE) {
        log->fatal("Error linking opengGL program {0}", m_programID);
    }

	m_modelUniformLocation = glGetUniformLocation(m_programID, "Model");
	m_viewUniformLocation = glGetUniformLocation(m_programID, "View");
	m_projectUniformLocation = glGetUniformLocation(m_programID, "Project");

    fatalOnOpenGLError("Failed after OpenGL program linking");
}

void OpenglRenderer::setView(const Matrix4& view) noexcept
{
    //glUseProgram(m_programID);
	glUniformMatrix4fv(m_viewUniformLocation, 1, GL_FALSE, &view[0][0]);
    //glUseProgram(0);
}

void OpenglRenderer::setProjection(const Matrix4& proj) noexcept
{
    //glUseProgram(m_programID);
    glUniformMatrix4fv(m_projectUniformLocation, 1, GL_FALSE, &proj[0][0]);
    //glUseProgram(0);
}

}