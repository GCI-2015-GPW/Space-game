// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.
#pragma once

#ifndef ENGINE_LOG_LOGGER_H_
#define ENGINE_LOG_LOGGER_H_

#include "thread/ActiveObject.h"

namespace Engine
{
namespace Core
{
enum class eLogLevel
{
	DEBUG,
	MESSAGE,
	ERROR_,
	WARNING,
	FATAL
};

template <typename Stream>
Stream& operator<<(Stream& stream, eLogLevel level)
{
	switch (level)
		{
			case eLogLevel::DEBUG:
				stream << "DEBUG";
				break;
			case eLogLevel::MESSAGE:
				stream << "MESSAGE";
				break;
			case eLogLevel::ERROR_:
				stream << "ERROR";
				break;
			case eLogLevel::WARNING:
				stream << "WARNING";
				break;
			case eLogLevel::FATAL:
				stream << "FATAL";
				break;
			default:
				stream << "UNRECOGNIZED eLogLevel";
		}

	return stream;
}

class Logger;

extern Logger* gLogger_ptr;

class Logger
{
public:
	static void initLogger() { gLogger_ptr = new Logger("Engine.log"); }
	static void cleanupLogger() { delete gLogger_ptr; }
	Logger(const std::string& filename);

	void add(const std::function<void(const std::string& message, eLogLevel level,
									  const std::string file, uint32_t lineNumber)> sink);

	void write(const std::string& message, eLogLevel level, const std::string& file,
			   uint32_t lineNumber);

private:
	std::vector<std::function<void(const std::string& message, eLogLevel level,
								   const std::string file, uint32_t lineNumber)>> mSinks;

	std::unique_ptr<Thread::ActiveObject> mActive;
};
}
}

#define gLogLevel(level)                                                                        \
	for (struct                                                                                 \
		 {                                                                                      \
			 ::std::ostringstream message;                                                      \
			 bool hasRan = false;                                                               \
		 } ____data;                                                                            \
		 !____data.hasRan; [&____data]()                                                        \
		 {                                                                                      \
			 ____data.hasRan = true;                                                            \
			 ::Engine::Core::gLogger_ptr->write(                                                \
				 ____data.message.str(), ::Engine::Core::eLogLevel::level, __FILE__, __LINE__); \
		 }())                                                                                   \
	____data.message

#define gLog gLogLevel(MESSAGE)

#define gLogDebug gLogLevel(DEBUG)
#define gLogMessage gLogLevel(MESSAGE)
#define gLogError gLogLevel(ERROR_)
#define gLogWarning gLogLevel(WARNING)
#define gLogFatal gLogLevel(FATAL)

#endif  // ENGINE_LOG_LOGGER_H_
