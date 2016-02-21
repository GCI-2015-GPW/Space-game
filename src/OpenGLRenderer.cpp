#include "OpenGLRenderer.h"

#include "log/Logger.h"

std::string Engine::OpenGLRenderer::getRendererInfo() { return "OpenGL Renderer"; }
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
