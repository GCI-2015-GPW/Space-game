// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "OpenGLRenderer.h"

#include "log/Logger.h"

#include <GLFW/glfw3.h>

std::string Engine::OpenGLRenderer::getRendererInfo() { return "OpenGL Renderer"; }

// Shader implementation
////////////////////////
Engine::OpenGLRenderer::Shader::Shader(const std::string& vertSource, const std::string& fragSource,
									   const std::string& geomSource)
{
	// generate names
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (!vertexShader || !fragShader)
		{
			gLogError << "Couldn't make a shader!";
		}

	// insert the source
	const char* vertSourceCStr = vertSource.c_str();
	glShaderSource(vertexShader, 1, &vertSourceCStr, nullptr);

	const char* fragSourceCStr = fragSource.c_str();
	glShaderSource(fragShader, 1, &fragSourceCStr, nullptr);

	// compile
	glCompileShader(vertexShader);
	glCompileShader(fragShader);

	// make sure it compiled correctly
	GLint infoLogLength = 0;
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 1)
		{
			auto message = std::string(infoLogLength + 1, ' ');
			glGetShaderInfoLog(vertexShader, infoLogLength, nullptr, &message[0]);
			gLogError << "Could not compile vertex shader: " << message;
		}

	glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 1)
		{
			auto message = std::string(infoLogLength + 1, ' ');
			glGetShaderInfoLog(fragShader, infoLogLength, nullptr, &message[0]);
			gLogError << "Could not compile fragment shader: " << message;
		}

	// link into a program
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	// make sure it linked correctly
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 1)
		{
			auto message = std::string(infoLogLength + 1, ' ');
			glGetProgramInfoLog(program, infoLogLength, nullptr, &message[0]);
			gLogError << "Could not link shader: " << message;
		}

	// delete the sources so they will delete when the program is deleted
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

// Window implementation
////////////////////////

Engine::OpenGLRenderer::Window::Window()
{
	// initalize 
	if(auto err = glfwInit() == 0)
	{
		gLogError << "Error encountered when initalizing GLFW. Error code: " << err;
	}
	
	// set context hints
	{
		// context version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		// MSAA
		glfwWindowHint(GLFW_SAMPLES, 8);

		// To make MacOS happy
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		// use core profile
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	
	// create window
	window = glfwCreateWindow(1280, 720, "Title", nullptr, nullptr);
	
	// make the gl commands use this window on this thread
	glfwMakeContextCurrent(window);
	
	// you need this for a core profile
	glewExperimental = true;
	
	// initalize GLEW (load the OpenGL functions)
	if(auto err = glewInit() != GLEW_OK)
	{
		using namespace std::literals;
		
		gLogError << "Error initalizing GLEW: " << glewGetErrorString(err);
	}
	
}

void Engine::OpenGLRenderer::Window::setTitle(const std::string& newTitle)
{
	glfwSetWindowTitle(window, newTitle.c_str());
}

void Engine::OpenGLRenderer::Window::setSize(const glm::uvec2& newSize)
{
	glfwSetWindowSize(window, newSize.x, newSize.y);
}


void Engine::OpenGLRenderer::Window::update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}
