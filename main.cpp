#include <iostream>
#include <SDL.h>
#include "OpenGL.h"

using namespace std;

#define FPS 30
#define WIN_SIZE 300, 300

SDL_Window* window = NULL;
SDL_Renderer* sdlRenderer = NULL;

SDL_Event event;
bool running = true;

void init_SDL(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cerr << "Unable to initialize SDL: " << SDL_GetError() << endl;
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
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_GL_SwapWindow(window);

    int ftime = SDL_GetTicks() - time;
    int wait = (1000 / FPS) - ftime;
    if(wait >= 0) {
        SDL_Delay(wait);
    }
}

int main() {
    InitOpenGL();
    init_SDL();    

    

    while(running) {
        mainloop();
    }

    cleanup();
    
    return 0;
}
