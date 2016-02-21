#pragma once

/// @file RendererConcept.h
/// @brief The concept for a renderer
///
/// This file defines a C++1z concept for a renderer.
/// It lays out what a renderer should look like.
/// If a renderer cannot satsify this concept, then it could cause errors.
///
/// @author Russell Greene

// for concepts definition
#include <boost/config.hpp>

#ifdef BOOST_HAS_CONCEPTS

namespace Engine
{
auto concept Renderer<typename T>
{
	Renderer();

	std::string getRendererInfo();
}
}

#endif  // BOOST_HAS_CONCEPTS
