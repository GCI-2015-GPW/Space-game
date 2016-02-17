#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

#include "log/Logger.h"

GLFWwindow *window;
GLuint vertexArray;
GLuint vertexLocBuffer;
GLuint program;

int main()
{
    Engine::Core::Logger::initLogger();
    // init glfw
    if (int err = glfwInit() == 0)
	{
	    std::cerr << "Failed to initalize glfw with error code: " << err << std::endl;
	    std::terminate();
	}

    // set glfw hints
    /////////////////

    // context version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // MSAA
    glfwWindowHint(GLFW_SAMPLES, 8);

    // To make MacOS happy
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // use core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create the window
    window = glfwCreateWindow(1280, 720, "Space! I'm in space!", nullptr, nullptr);
    if (!window)
	{
	    std::cerr << "Window creation failed!" << std::endl;
	    std::terminate();
	}

    // make this thread control the window
    glfwMakeContextCurrent(window);

    // use core profile
    glewExperimental = true;

    // init GLEW (loads the opengl functions)
    if (int err = glewInit() != GLEW_OK)
	{
	    std::cerr << "Error initalizing glew: " << glewGetErrorString(err) << std::endl;
	    std::terminate();
	}

    // init opengl resources
    ////////////////////////

    glClearColor(.3f, .3f, .3f, 1.f);

    // vertex array
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    // make shaders

    // load shader source
    auto loadFile = [](const std::string &path)
    {
	std::ifstream file{path};

	std::string ret;
	std::string line;

	if (file.is_open())
	    {
		while (std::getline(file, line))
		    {
			ret.append(line);
			ret.push_back('\n');
		    }
	    }
	else
	    {
		gLogWarning << "Cannot open file: " << path;
	    }
	return ret;

    };
    std::string vertexSource = loadFile("shaders/testvert.glsl");
    std::string fragSource = loadFile("shaders/testfrag.glsl");

    // generate names
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!vertexShader || !fragShader)
	{
	    gLogError << "Couldn't make a shader!";
	}

    // insert the source
    const char *vertSourceCStr = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertSourceCStr, nullptr);

    const char *fragSourceCStr = fragSource.c_str();
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

    // make location buffer
    glGenBuffers(1, &vertexLocBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexLocBuffer);
    float locs[] = {-1.f, -1.f, 0.f, 0.f, 1.f, 0.f, 1.f, -1.f, 0.f};
    glBufferData(GL_ARRAY_BUFFER, sizeof(locs), locs, GL_STATIC_DRAW);

    gLog << "Finished Initializing!";

    while (!glfwWindowShouldClose(window))
	{
	    glClear(GL_COLOR_BUFFER_BIT);

	    glUseProgram(program);

	    glBindVertexArray(vertexArray);

	    glEnableVertexAttribArray(0);
	    glBindBuffer(GL_ARRAY_BUFFER, vertexLocBuffer);
	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	    glDrawArrays(GL_TRIANGLES, 0, 3);
	    glDisableVertexAttribArray(0);

	    glfwSwapBuffers(window);
	    glfwPollEvents();
	}
}
