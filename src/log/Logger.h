// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.
#pragma once

#ifndef ENGINE_LOG_LOGGER_H_
#define ENGINE_LOG_LOGGER_H_

#include "log/LogMessage.h"
#include "thread/ActiveObject.h"

namespace Engine
{
namespace Core
{
class LogSink;
class LogMessage;

class Logger;

extern Logger *gLogger_ptr;

class Logger
{
public:
    static void initLogger() { gLogger_ptr = new Logger("Engine.log"); }
    Logger(const std::string &filename);

    LogMessage operator()(eLogLevel level, const std::string &filename, int line);

    void add(const LogSink &sink);
    void remove(const LogSink &sink);

    void flush(const LogMessage &message) const;

private:
    std::vector<LogSink> mSinks;
    std::unique_ptr<Thread::ActiveObject> mActive;
};
}
}

#define gLogLevel(level) \
    (*::Engine::Core::gLogger_ptr)(::Engine::Core::eLogLevel::level, __FILE__, __LINE__)

#define gLog gLogLevel(MESSAGE)

#define gLogDebug gLogLevel(DEBUG)
#define gLogMessage gLogLevel(MESSAGE)
#define gLogError gLogLevel(ERROR_)
#define gLogWarning gLogLevel(WARNING)
#define gLogFatal gLogLevel(FATAL)

#endif  // ENGINE_LOG_LOGGER_H_
