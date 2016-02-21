#pragma once

/// @file RendererConcept.h
/// @author Russell Greene
/// @brief The concept for a renderer
/// 
/// This file defines a C++1z concept for a renderer. 
/// It lays out what a renderer should look like. 
/// If a renderer cannot satsify this concept, then it could cause errors.


// for concepts definition
#include <boost/config.hpp>


#ifdef BOOST_HAS_CONCEPTS

namespace Engine
{

auto concept Renderer<typename T> {
    Renderer();
    
    std::string getRendererString();
    
    
}

}

#endif // BOOST_HAS_CONCEPTS
