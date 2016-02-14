#include <iostream>
#include <SDL.h>
#include "OpenGL.h"

#include "Texture.h"

#define FPS 30
#define WIN_SIZE 300, 300

SDL_Window* window = NULL;
SDL_Renderer* sdlRenderer = NULL;
SDL_Texture *texture = NULL;

SDL_Event event;
bool running = true;

GLuint top, bottom, left, right, front, back;

void init_SDL(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    window = SDL_CreateWindow(
        "Space Game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIN_SIZE,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
    SDL_MaximizeWindow(window);
    sdlRenderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);
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
                resize(event.window.data1, event.window.data2);
            }
        }
    }
    
    auto tex = Texture::FromPNGFile("Cubes/1.png");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -2.0f);
    //glRotatef(ang++, 0.0f, 1.0f, 0.0f);
    //glRotatef(45, 1.0f, 0.0f, 0.0f);

    glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, front);
        glTexCoord2f(1, 1);
        glVertex3f(0.5, 0.5, 0.5);
        glTexCoord2f(0, 1);
        glVertex3f(-0.5, 0.5, 0.5);
        glTexCoord2f(0, 0);
        glVertex3f(-0.5, -0.5, 0.5);
        glTexCoord2f(1, 0);
        glVertex3f(0.5, -0.5, 0.5);
        glBindTexture(GL_TEXTURE_2D, 0);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, -0.5);

        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, -0.5);

        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, -0.5, -0.5);

        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, -0.5);
    glEnd();

    SDL_GL_SwapWindow(window);

    int ftime = SDL_GetTicks() - time;
    int wait = (1000 / FPS) - ftime;
    if(wait >= 0) {
        SDL_Delay(wait);
    }
}

int main() {
    init_SDL();
    InitOpenGL();

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    resize(w, h);

    while(running) {
        mainloop();
    }

    cleanup();
    
    return 0;
}
