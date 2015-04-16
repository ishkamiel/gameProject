#include "opengl/SimpleProgram.h"
#include "opengl/SimpleFragmentShader.h"
#include "opengl/SimpleVertexShader.h"

#include "Logger.h"

namespace pdEngine {

SimpleProgram::SimpleProgram(void)
{}

void SimpleProgram::render(void)
{
	glUseProgram(s_ProgramID);

	glEnableVertexAttribArray(s_VertexPosition);
	glEnableVertexAttribArray(s_ModelPosition);

	glBindBuffer(GL_ARRAY_BUFFER, gVBO);

	glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof (GLfloat), NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);

	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);
	glDisableVertexAttribArray(gVertexPos2DLocation);

	glUseProgram(0);
}

void SimpleProgram::init(void)
{


        if (!s_InitDone)
        {
                s_InitOpenGLProgram();
        }
}

void pdEngine::SimpleProgram::s_InitOpenGLProgram(void v) {

}

static void SimpleProgram::s_InitOpenGLProgram(void) {
        auto log = getLogger();

        s_ProgramID = glCreateProgram();

        log->debug("Compiling vertex shader");
        SimpleVertexShader vertexShader{};
        vertexShader.load();
        vertexShader.compile();

        log->debug("Compiling fragment shader");
        SimpleFragmentShader fragmentShader{};
        fragmentShader.load();
        fragmentShader.compile();

        log->debug("Linking OpenGL program");
        glAttachShader(s_ProgramID, vertexShader.getID());
        glAttachShader(s_ProgramID, fragmentShader.getID());
        glLinkProgram(s_ProgramID);

        GLint programSuccess = GL_TRUE;
        glGetProgramiv(s_ProgramID, GL_LINK_STATUS, &programSuccess);
        if (programSuccess != GL_TRUE) {
                log->fatal("Error linking opengGL program {0}", m_programID);
                throw OpenglException(m_programID);
        }

        log->debug("Retrieving OpenGL program attributes");
        s_VertexPosition = glGetAttribLocation(s_ProgramID, "Vertex");
        s_ModelPosition = glGetAttribLocation(s_ProgramID, "Model");

        if (s_VertexPosition == -1 || s_ModelPosition == -1)
        {
                log->fatal("LVertexPos2DLocation is not a valid glsl program variable");
        }

        //glClearColor(0.f, 0.f, 0.f, 1.f);

        GLfloat vertexData[] = {
                -0.5f, -0.5f,
                0.5f, -0.5f,
                0.5f, 0.5f,
                -0.5f, 0.5f
        };

        GLuint indexData[] = {0, 1, 2, 3};

        glGenBuffers(1, &s_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
        glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

        glGenBuffers(1, &s_IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

        log->info("OpenGL program initialized");
}

}