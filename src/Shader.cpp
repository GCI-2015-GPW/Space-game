
#include "Shader.h"

#include <iostream>

Shader::Shader(const std::string& vertexSource, const std::string& fragSource)
{
    // generate names
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    if(!vertexShader || !fragShader)
    {
        throw std::runtime_error("Error: couldn't make a shader!");
    }
    
    
    // insert the source
    const char* vertSourceCStr = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertSourceCStr, nullptr);
    
    const char* fragSourceCStr = fragSource.c_str();
    glShaderSource(fragShader, 1, &fragSourceCStr, nullptr);
    
    // compile 
    glCompileShader(vertexShader);
    glCompileShader(fragShader);
    
    // make sure it compiled correctly
    GLint infoLogLength = 0;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 1) 
    {
        auto message = std::string(infoLogLength + 1, ' ');
        glGetShaderInfoLog(vertexShader, infoLogLength, nullptr, &message[0]);
        std::cout << "Error: could not compile vertex shader: " << message;
    }
    
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 1) 
    {
        auto message = std::string(infoLogLength + 1, ' ');
        glGetShaderInfoLog(fragShader, infoLogLength, nullptr, &message[0]);
        std::cout << "Error: could not compile fragment shader: " << message;
    }
    
    // link into a program
    name = glCreateProgram();
    glAttachShader(name, vertexShader);
    glAttachShader(name , fragShader);
    glLinkProgram(name);
    
    // make sure it linked correctly
    glGetProgramiv(name, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 1)
    {
        auto message = std::string(infoLogLength + 1, ' ');
        glGetProgramInfoLog(name, infoLogLength, nullptr, &message[0]);
        std::cout << "Error: could not link shader: " << message;
    }
    
    // delete the sources so they will delete when the program is deleted
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
    
}

Shader::~Shader()
{
    glDeleteProgram(name);
}

