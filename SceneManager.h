#pragma once

#include <Manager.h>

#include <glm/vec3.hpp>

#include <boost/signals2.hpp>


// COMPONENTS
struct CLocation
{
    glm::vec3 value;
};

struct CVelocity
{
    
};

using SceneManager_t = 
    Manager<
        decltype(make_type_tuple<CLocation, CVelocity>)
    >;

template<>
struct ManagerData<SceneManager_t>
{
    boost::signals2::signal<void(float)> tick;
};
