#include <iostream>
#include <fstream>

#include <SDL.h>
#include "OpenGL.h"

#include "Texture.h"
#include "Shader.h"

#define FPS 30
#define WIN_SIZE 300, 300

SDL_Window* window = NULL;
SDL_GLContext maincontext;
SDL_Texture *texture = NULL;

GLuint VertexArrayID;
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f,  1.0f, 0.0f,
};
GLuint vertexbuffer;
Shader program;

SDL_Event event;
bool running = true;

void init_SDL(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); 

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetSwapInterval(1);

    window = SDL_CreateWindow(
        "Space Game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIN_SIZE,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    SDL_MaximizeWindow(window);

    maincontext = SDL_GL_CreateContext(window);
}

void cleanup(){
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

void mainloop(){
    int time = SDL_GetTicks();

    SDL_PumpEvents();
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            running = false;
        }
        if(event.type == SDL_WINDOWEVENT) {
            if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                glViewport(0, 0, event.window.data1, event.window.data2);
            }
        }
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program.name);
    
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);

    SDL_GL_SwapWindow(window);

    int ftime = SDL_GetTicks() - time;
    int wait = (1000 / FPS) - ftime;
    if(wait >= 0) {
        SDL_Delay(wait);
    }
}

int main() {
    init_SDL();
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    // load source
    auto loadSource = [](const std::string& path)
        {
            std::string ret;
            
            std::string line;
            
            std::ifstream file{path};
            
            if(file)
            {
                while(std::getline(file, line))
                {
                    ret.append(line);
                    ret.push_back('\n');
                }
            }
            
            return ret;
        };
    std::string vertexSoure = loadSource("shaders/testvert.glsl");
    std::string fragSource = loadSource("shaders/testfrag.glsl");
    program = Shader{vertexSoure, fragSource};
    
    
    
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    glViewport(0, 0, w, h);

    while(running) {
        mainloop();
    }

    cleanup();
    
    return 0;
}
