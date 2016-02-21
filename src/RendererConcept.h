// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

/// @file RendererConcept.h
/// @brief The concept for a renderer
///
/// This file defines a C++1z concept for a renderer.
/// It lays out what a renderer should look like.
/// If a renderer cannot satsify this concept, then it could cause errors.
///
/// @author Russell Greene

#pragma once

// for concepts definition
#include <boost/config.hpp>

#ifdef BOOST_HAS_CONCEPTS

namespace Engine
{
auto concept Renderer<typename T>
{
	Renderer();

	std::string getRendererInfo();

	// we need a shader class
	Shader<typename T::Shader>;

	// and a model class
	Model<typename T::Model>;
}

auto concept Shader<typename T>
{
	Shader();

	Shader(const std::string& vertSource, const std::string& fragSource,
		   const std::string& geomSource = "");
}

auto concept Model<typename T> { Model(); }
}

#endif  // BOOST_HAS_CONCEPTS
