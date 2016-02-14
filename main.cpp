#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "OpenGL.h"


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

    int rmask, gmask, bmask, amask;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xFF000000;
        gmask = 0x00FF0000;
        bmask = 0x0000FF00;
        amask = 0x000000FF;
    #else
        rmask = 0x000000FF;
        gmask = 0x0000FF00;
        bmask = 0x00FF0000;
        amask = 0xFF000000;
    #endif

    SDL_Surface *surface = SDL_CreateRGBSurface(0, 64, 64, 32,
                                   rmask, gmask, bmask, amask);

    if(surface == NULL) {
        std::cerr << "CreateRGBSurface failed: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_Surface *image = IMG_Load("Cubes/1.png");
    if(!image) {
        std::cerr << "Load image failed: " << IMG_GetError() << std::endl;
        exit(1);
    }

    SDL_Rect rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = 64;
    rect.h = 64;

    SDL_BlitSurface(image, &rect, surface, NULL);
    top = Surface2Texture(surface);

    rect.x = 64;
    SDL_BlitSurface(image, &rect, surface, NULL);
    bottom = Surface2Texture(surface);

    rect.x = 64*2;
    SDL_BlitSurface(image, &rect, surface, NULL);
    left = Surface2Texture(surface);

    rect.x = 64*3;
    SDL_BlitSurface(image, &rect, surface, NULL);
    right = Surface2Texture(surface);

    rect.x = 64*4;
    SDL_BlitSurface(image, &rect, surface, NULL);
    front = Surface2Texture(surface);

    rect.x = 64*5;
    SDL_BlitSurface(image, &rect, surface, NULL);
    back = Surface2Texture(surface);

    SDL_FreeSurface(surface);
    SDL_FreeSurface(image);

    while(running) {
        mainloop();
    }

    cleanup();
    
    return 0;
}
