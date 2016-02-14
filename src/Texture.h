#pragma once

#include "OpenGL.h"

#include <string>

class Texture
{
public:
    
    Texture(const Texture& other) = delete;
    Texture(Texture&& other)
    {
        name = other.name;
        other.name = 0;
    }
    
    ~Texture();
    
    Texture& operator=(const Texture& other) = delete;
    Texture& operator=(Texture&& other)
    {
        name = other.name;
        other.name = 0;
        
        return *this;
    }
    
    static Texture FromDDSFile(const std::string& path);
    static Texture FromPNGFile(const std::string& path);
    
    // Reads from memory. 
    // data - the data for the image
    // width and height - the dimensions
    // channelConfig  - one of GL_ALPHA, GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA
    // type - one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_4_4_4_4, and GL_UNSIGNED_SHORT_5_5_5_1
    static Texture FromMemory(GLubyte* data, size_t width, size_t height, GLenum channelConfig, GLenum type);
    
    
    
    explicit Texture(GLuint name_) : name{name_} {}
    
    GLuint name;
};
