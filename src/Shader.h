#pragma once

#include "OpenGL.h"

#include <string>

struct Shader
{
    Shader() : name{0} {}
    Shader(const std::string& vertexSource, const std::string& fragSource);
    
    Shader(const Shader& other) = delete;
    Shader(Shader&& other)
    {
        name = other.name;
        other.name = 0;
    }
    
    ~Shader();
    
    Shader& operator=(const Shader& other) = delete;
    Shader& operator=(Shader&& other) 
    {
        name = other.name;
        other.name = 0;
        
        return *this;
    }
    
    bool isValid()
    {
        return name;
    }
    
    
    GLuint name;
};
