// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

/// @file OpenGLRenderer.h
/// @author Russell Greene
/// @brief The OpenGL implementation for the renderer.
///
/// Defines OpenGLRenderer

#pragma once

#include "RendererConcept.h"

#include <GL/glew.h>

#include <string>

struct GLFWwindow;

namespace Engine
{
/// @brief Implements the Renderer concept defined in RendererConcept.h
class OpenGLRenderer
{
public:
	/// @brief gets a string describing the renderer
	///
	/// @return A string the details the renderer
	static std::string getRendererInfo();

	/// @brief The shader object for the OpenGLRenderer.
	///
	/// Implements the Shader concept in RendererConcept.h
	struct Shader
	{
		/// @brief Constructs the shader from source
		///
		/// @param vertSource The source code for the vertex shader
		/// @param fragSource The source code for the fragment shader
		/// @param geomSource The soruce code for the geometry shader
		Shader(const std::string& vertSource, const std::string& fragSource,
			   const std::string& geomSource = "");

		/// @brief The OpenGL program to use. Should not be used in cross-renderer situations.
		GLuint program;
	};

	/// @brief The model object for the OpenGLRenderer
	///
	/// Implements the Model concept in RendererConcept.h
	struct Model
	{
		Model() = default;
	};
	
	
	/// @brief The window object for the OpenGLRenderer
	///
	/// Implements the Window concept in RendererConcept.h
	struct Window
	{
		Window();
		/// @brief set the title
		///
		/// @param newTitle the new title for the window
		void setTitle(const std::string& newTitle);

		/// @brief sets the size
		///
		/// @param newSize the new size for the window
		void setSize(const glm::uvec2& newSize);
		
		/// @brief swaps the buffers for the window
		void update();
		
		/// @brief the native GLFW window class. Not to be used in a cross-API situation.
		GLFWwindow* window;
	};
};
}
