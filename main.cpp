#include <iostream>
#include <SDL2/SDL.h>
#include <OpenGL.h>

using namespace std;

#define FPS 30
#define WIN_SIZE 300, 300

int main() {

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cerr << "Unable to initialize SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    InitOpenGL();

    SDL_Window *window = SDL_CreateWindow(
        "Space Game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIN_SIZE,
        SDL_WINDOW_OPENGL
    );
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);

    SDL_Event event;
    bool running = true;

    while(running) {
        int time = SDL_GetTicks();

        SDL_PumpEvents();
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
        }

        glClearColor(1, 1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_GL_SwapWindow(window);

        int ftime = SDL_GetTicks() - time;
        int wait = (1000 / FPS) - ftime;
        if(wait >= 0) {
            SDL_Delay(wait);
        }
    }

    SDL_Quit();
    return 0;
}
