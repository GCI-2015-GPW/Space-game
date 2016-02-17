// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ENGINE_LOG_LOGMESSAGE_H_
#define ENGINE_LOG_LOGMESSAGE_H_

#include "log/LogLevel.h"

#include <string>
#include <sstream>
#include <ostream>
#include <vector>

namespace Engine
{
namespace Core
{
class Logger;
class LogSink;

class LogMessage
{
private:
    friend class Logger;
    friend class LogSink;

    LogMessage(eLogLevel level, const std::string &file, int line, Logger *owner);

public:
    ~LogMessage();

    LogMessage(LogMessage &&message);

    template <typename T>
    LogMessage &operator<<(const T &message);
    LogMessage &operator<<(std::ostream &(*fn)(std::ostream &os));

    struct Meta
    {
	eLogLevel mLevel;
	std::string mFile;
	int mLine;
    };

private:
    Meta mMeta;
    Logger *mOwner;  // The spawning object is guaranteed to outlive this one, so
		     // it's fine to use a raw pointe here.
    std::ostringstream mBuffer;
};

template <typename T>
LogMessage &LogMessage::operator<<(const T &message)
{
    mBuffer << message;
    return *this;
}

}  // namespace Core
}  // namespace Engine

#endif  // ENGINE_LOG_LOGMESSAGE_H_
