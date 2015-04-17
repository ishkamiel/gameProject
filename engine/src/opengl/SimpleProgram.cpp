#include "opengl/SimpleProgram.h"

#include "Logger.h"

#include "opengl/SimpleFragmentShader.h"
#include "opengl/SimpleVertexShader.h"
#include "opengl/OpenglUtils.h"


#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace pdEngine {

SimpleProgram::SimpleProgram(void)
{}

void SimpleProgram::render(void) const
{
	glUseProgram(m_ProgramID);

	static glm::mat4 model;
	static float a = 0.01;
	static glm::mat4 rotation1 = {
		(float)cos(a), (float)-sin(a), 0, 0,
		(float)sin(a), (float)cos(a), 0, 0,
		0, 0, 1.f, 0,
		0, 0, 0, 1.f
	};

	static glm::mat4 rotation2 = {
		1, 0, 0, 0,
		0, (float)cos(a*2), (float)-sin(a*2), 0,
		0, (float)sin(a*2), (float)cos(a*2), 0,
		0, 0, 0, 1.f
	};

	model = model*rotation1 * rotation2;

	glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, "Model"), 1, GL_FALSE, &model[0][0]);
	//glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, "View"), 1,  GL_FALSE, identity);
	//glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, "Project"), 1, GL_FALSE, identity);

	glEnableVertexAttribArray(0);
	fatalOnOpenGLError("Failed to enable vertex attributes");

	glBindVertexArray(m_VAO);
	fatalOnOpenGLError("Failed to bind VAO for drawing");

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLvoid*)0);
	fatalOnOpenGLError("Failed to draw the thing");

	glBindVertexArray(0);
	glUseProgram(0);
}

void SimpleProgram::init(void)
{
	auto log = getLogger();

    m_ProgramID = glCreateProgram();

	log->debug("Compiling vertex shader");
	SimpleVertexShader vertexShader{};
	vertexShader.load();
	vertexShader.compile();

	log->debug("Compiling fragment shader");
	SimpleFragmentShader fragmentShader{};
	fragmentShader.load();
	fragmentShader.compile();

	log->debug("Linking OpenGL program");
	glAttachShader(m_ProgramID, vertexShader.getID());
	glAttachShader(m_ProgramID, fragmentShader.getID());
	glLinkProgram(m_ProgramID);

	GLint programSuccess = GL_TRUE;
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE) {
			log->fatal("Error linking opengGL program {0}", m_ProgramID);
	}

	fatalOnOpenGLError("Failed after OpenGL program linking");

	glUseProgram(m_ProgramID);

	static const GLfloat identity[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

	glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, "Model"), 1, GL_FALSE, identity);
	glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, "View"), 1,  GL_FALSE, identity);
	glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, "Project"), 1, GL_FALSE, identity);
	fatalOnOpenGLError("Failed to set uniforms");

	const glm::vec4 VERTICES[8] =
		{
			{ -.5f, -.5f,  .5f, 1 },
			{ -.5f,  .5f,  .5f, 1 },
			{  .5f,  .5f,  .5f, 1 },
			{  .5f, -.5f,  .5f, 1 },
			{ -.5f, -.5f, -.5f, 1 },
			{ -.5f,  .5f, -.5f, 1 },
			{  .5f,  .5f, -.5f, 1 },
			{  .5f, -.5f, -.5f, 1 },
		};

	const GLuint INDICES[36] =
		{
			0,2,1,  0,3,2,
			4,3,0,  4,7,3,
			4,1,5,  4,0,1,
			3,6,2,  3,7,6,
			1,6,5,  1,2,6,
			7,5,6,  7,4,5
		};

	glGenVertexArrays(1, &m_VAO);
	fatalOnOpenGLError("Failed to generate VAO");
	glBindVertexArray(m_VAO);
	fatalOnOpenGLError("Failed to bind VAO");

	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	fatalOnOpenGLError("Failed to enable vertex attributes");

    glGenBuffers(1, &m_VBO);
	fatalOnOpenGLError("Failed to generate VBO buffer objects");
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
	fatalOnOpenGLError("Failed to bind VBO to VAO");


	glGenBuffers(1, &m_IBO);
	fatalOnOpenGLError("Failed to generate IBO buffer object");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);
    fatalOnOpenGLError("ERROR: Could not bind the IBO to the VAO");

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(VERTICES[0]), (GLvoid*)0);
	fatalOnOpenGLError("ERROR: Could not set VAO attributes");

    glBindVertexArray(0);
	glUseProgram(0);
	log->info("OpenGL program initialized");
}

}