#include "RendererOpengl.h"

#include "Logger.h"

namespace pdEngine 
{
    RendererOpengl::RendererOpengl(std::string windowTitle)
        : windowTitle(windowTitle)
    {}

    RendererOpengl::~RendererOpengl()
    {
        if (window != nullptr)
            SDL_DestroyWindow(window);
    }

    void RendererOpengl::onInit(void)
    {
        auto log = GET_LOGGER();

        //Use OpenGL 3.1 core 
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 ); 
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 ); 
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

    void RendererOpengl::onUpdate(TimeDelta delta)
    {
        (void)delta;
    }

    void RendererOpengl::render()
    {
        //Clear color buffer 
        glClear( GL_COLOR_BUFFER_BIT ); 

        //Render quad 
        if( gRenderQuad ) { 
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
            //Disable vertex position 
            glDisableVertexAttribArray( gVertexPos2DLocation ); 
            //Unbind program 
            glUseProgram(0); 
        }

        SDL_GL_SwapWindow(window);
    }

    void RendererOpengl::printDebugMsg(std::string msg)
    {
        (void)msg;
    }

    bool RendererOpengl::initOpengl(void)
    {
        auto log = GET_LOGGER();

        programID = glCreateProgram();

        log->debug("Compiling vertex shader");
        GLuint vertexShader = compileShader(GL_VERTEX_SHADER, 
                {
                "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
                });


        log->debug("Compiling fragment shader");
        GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER,
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
            printProgramLog(programID);
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








        if (false)
        {
            GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

            const GLchar* vertexShaderSource[] =
            {
                "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
            };

            glShaderSource(vertexShader, 1, vertexShaderSource, nullptr);
            glCompileShader(vertexShader);

            GLint vShaderCompiled = GL_FALSE;
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
            if (vShaderCompiled != GL_TRUE)
            {
                log->error("Unable to compile vertex shader {0}", vertexShader);
                printShaderLog(vertexShader);
                return false;
            }

            //glAttachShader(gProgramID, vertexShader);

            GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

            const GLchar* fragmentShaderSource[] = 
            {
                "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
            };

            glShaderSource(fragmentShader, 1, fragmentShaderSource, nullptr);
            glCompileShader(fragmentShader);
        }

        return true;
    }

    GLuint RendererOpengl::compileShader(const GLenum type, const GLchar source[])
    {
        auto log = GET_LOGGER();
        GLuint shader = glCreateShader(type);

        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);

        GLint compileOk = GL_FALSE;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compileOk);
        if (compileOk != GL_TRUE)
        {
            log->error("Unable to compile shader {0}", shader);
            printShaderLog(shader);
            throw std::runtime_error("shader compilation fail");
        }

        return shader;
    }


    void RendererOpengl::printProgramLog(GLuint program) 
    { 
        //Make sure name is shader 
        if( glIsProgram( program ) ) 
        { 
            //Program log length 
            int infoLogLength = 0; 
            int maxLength = infoLogLength; 

            //Get info string length 
            glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength ); 

            //Allocate string 
            char* infoLog = new char[ maxLength ]; 

            //Get info log 
            glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog ); 

            if( infoLogLength > 0 ) { 
                //Print Log 
                printf( "%s\n", infoLog ); 
            } 

            //Deallocate string 
            delete[] infoLog; 
        } 
        else 
        { 
            printf( "Name %d is not a program\n", program ); 
        } 
    } 

    void RendererOpengl::printShaderLog(GLuint shader) 
    { 
        //Make sure name is shader 
        if( glIsShader( shader ) ) 
        { 
            //Shader log length 
            int infoLogLength = 0; 
            int maxLength = infoLogLength; 

            //Get info string length 
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength ); 

            //Allocate string 
            char* infoLog = new char[ maxLength ]; 

            //Get info log 
            glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog ); 

            if( infoLogLength > 0 ) { 
                //Print Log 
                printf( "%s\n", infoLog ); 
            } 
            //Deallocate string 
            delete[] infoLog; 
        } 
        else 
        { 
            printf( "Name %d is not a shader\n", shader ); 
        } 
    }
}
