#ifndef OPENGL_H
#define OPENGL_H

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#endif/*__APPLE__*/

void InitOpenGL();

void resize(int, int);

GLuint Surface2Texture(SDL_Surface*);

#endif
