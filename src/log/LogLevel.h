// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#ifndef ENGINE_LOG_LOGLEVEL_H_
#define ENGINE_LOG_LOGLEVEL_H_

#include <ostream>

namespace Engine {
namespace Core {
enum class eLogLevel {
    DEBUG,
    MESSAGE,
    WARNING,
    ERROR_,  // The underscore is required due to the presence of a pre-existing
             // macro called 'ERROR'.
    FATAL
};

void setLogLevel(eLogLevel level, bool enabled);
bool logLevel(eLogLevel level);
}
}

std::ostream &operator<<(std::ostream &os, const Engine::Core::eLogLevel &level);

#endif  // ENGINE_LOG_LOGLEVEL_H_
