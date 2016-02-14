#ifndef OPENGL_H
#define OPENGL_H

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#   define glGenVertexArrays glGenVertexArraysAPPLE
#   define glBindVertexArray glBindVertexArrayAPPLE
#   define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#endif/*__APPLE__*/

#include <SDL.h>

#endif
