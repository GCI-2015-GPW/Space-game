#ifndef OPENGL_H
#define OPENGL_H

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#   define glGenVertexArrays glGenVertexArraysAPPLE
#   define glBindVertexArray glBindVertexArrayAPPLE
#   define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#endif/*__APPLE__*/

#include <SDL.h>
#include <SDL_opengl.h>

#endif
