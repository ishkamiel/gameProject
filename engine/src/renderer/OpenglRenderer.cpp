#include "renderer/OpenglRenderer.h"
#include "renderer/ShaderProgram.h"
#include "renderer/OpenglUtils.h"

#include "Logger.h"

namespace pdEngine 
{
    OpenglRenderer::OpenglRenderer(std::string windowTitle)
        : windowTitle(windowTitle)
    {}

    OpenglRenderer::~OpenglRenderer()
    {
        if (window != nullptr)
            SDL_DestroyWindow(window);
    }

    void OpenglRenderer::onInit(void)
    {
        auto log = GET_LOGGER();

        //Use OpenGL 3.1 core 
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 ); 
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 ); 
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

        if (SDL_Init(0) != 0) {
            printf("Error initializing SDL:  %s\n", SDL_GetError());
            return fail();
        }

        if (SDL_VideoInit(0) != 0) {
            printf("Error initializing SDL video:  %s\n", SDL_GetError());
            return fail();
        }

        window = SDL_CreateWindow(windowTitle.c_str(),
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                window_width, window_height,
                SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

        //Create context
        glContext = SDL_GL_CreateContext(window);
        if (glContext == nullptr)
        {
            log->error("Failed to create OpenGL context. SDL Error: {0}", SDL_GetError());
            return fail();
        }

        // init GLEW
        glewExperimental = GL_TRUE;
        GLenum  glewError = glewInit();

        if (glewError != 0)
        {
            log->error("Failed to initialize GLEW: {0}", glewGetErrorString(glewError));
            return fail();
        }

        // Enable vSync
        if (SDL_GL_SetSwapInterval(1)  < 0)
        {
            log->warn("Cannot enable vSync. SDL error: {0}", SDL_GetError());
        }

        // init openGL
        if (!initOpengl())
        {
            log->error("Failed to initialize openGL");
            return fail();
        }
    }

    void OpenglRenderer::onUpdate(TimeDelta delta)
    {
        (void)delta;
    }

    void OpenglRenderer::render()
    {
        //Clear color buffer 
        glClear( GL_COLOR_BUFFER_BIT ); 

        //Render quad 
        if (gRenderQuad) { 
            //Bind program 
            glUseProgram( programID ); 

            //Enable vertex position 
            glEnableVertexAttribArray( gVertexPos2DLocation ); 

            //Set vertex data 
            glBindBuffer( GL_ARRAY_BUFFER, gVBO ); 
            glVertexAttribPointer( gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL ); 

            //Set index data and render 
            glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO ); 

            glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL ); 
            //glDrawArrays(GL_TRIANGLES, 0, 3);

            //Disable vertex position 
            glDisableVertexAttribArray( gVertexPos2DLocation ); 

            //Unbind program 
            glUseProgram(0); 
        }

        SDL_GL_SwapWindow(window);
    }

    void OpenglRenderer::printDebugMsg(std::string msg)
    {
        (void)msg;
    }

    bool OpenglRenderer::initOpengl(void)
    {
        auto log = GET_LOGGER();

        programID = glCreateProgram();

        log->debug("Compiling vertex shader");
        GLuint vertexShader = loadShaderFromString(GL_VERTEX_SHADER, 
                {
                "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
                });


        log->debug("Compiling fragment shader");
        GLuint fragmentShader = loadShaderFromString(GL_FRAGMENT_SHADER,
                {
                "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
                });

        // Link program
        glAttachShader(programID, vertexShader);
        glAttachShader(programID, fragmentShader);
        glLinkProgram(programID);

        // check program
        GLint programSuccess = GL_TRUE;
        glGetProgramiv(programID, GL_LINK_STATUS, &programSuccess);
        if (programSuccess != GL_TRUE)
        {
            log->error("Error linking opengGL program {0}", programID);
            printGLLog(programID);
            throw std::runtime_error("openGL linking error");
        }

        gVertexPos2DLocation = glGetAttribLocation(programID, "LVertexPos2D");
        if (gVertexPos2DLocation == -1)
        {
            log->error("LVertexPos2DLocation is not a valid glsl program variable");
            throw std::runtime_error("glsl error");
        }

        glClearColor(0.f, 0.f, 0.f, 1.f);

        // VBO data
        GLfloat vertexData[] = {
            -0.5f, -0.5f, 
            0.5f, -0.5f, 
            0.5f, 0.5f, 
            -0.5f, 0.5f };

        // IBO data 
        GLuint indexData[] = { 0, 1, 2, 3 };

        //Create VBO 
        glGenBuffers( 1, &gVBO ); 
        glBindBuffer( GL_ARRAY_BUFFER, gVBO ); 
        glBufferData( GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW ); 

        //Create IBO 
        glGenBuffers( 1, &gIBO ); 
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO ); 
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW );

        return true;
    }
}
