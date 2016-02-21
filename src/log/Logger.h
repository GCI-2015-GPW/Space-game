// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

/// @file Logger.h
/// @brief Defines the logger.
///
/// Usage: after calling Logger::initLogger(), you can use any of the logger macros
/// @author Russell Greene
/// @author Aun-Ali Zaidi

#pragma once

#include "thread/ActiveObject.h"

#include <cstdint>
#include <functional>

namespace Engine
{
namespace Core
{
/// Defines the severity levels for logging
enum class eLogLevel : uint8_t
{
	DEBUG,	/// Debug messages, can be ignored by the user
	MESSAGE,  /// General info, by default the only level printed to stdout
	ERROR_,   /// Error message: possibly breaking issue
	WARNING,  /// Warning message, for example a config issue
	FATAL	 /// Fatal error, no possible recovery
};

/// @brief Stream operator for eLogLevel. This is so we can print a eLogLevel
///
/// @param stream stream to ouput level to
/// @param level the eLogLevel to print
///
/// @return the stream that has been used, after printing level
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

/// the global logger pointer. This needs to be initalized with Logger::initLogger and cleaned up
/// with Logger::cleanupLogger
extern Logger* gLogger_ptr;

/// @brief The logger class. For the global logger, just use the gLogLevel macro
class Logger
{
public:
	/// @brief initalizes the global logger
	static void initLogger() { gLogger_ptr = new Logger("Engine.log"); }
	/// @brief deletes and flushes the global logger
	static void cleanupLogger() { delete gLogger_ptr; }
	/// @brief constructs a loger
	///
	/// @param filename the filename for the log to be created
	Logger(const std::string& filename);

	/// @brief adds a sink to the Logger.
	///
	/// @param sink the sink to add.
	void add(const std::function<void(const std::string& message, eLogLevel level,
									  const std::string file, uint32_t lineNumber)> sink);

	/// @brief writs a new message. You would normally use the gLogLevel macros for that
	void write(const std::string& message, eLogLevel level, const std::string& file,
			   uint32_t lineNumber);

private:
	std::vector<std::function<void(const std::string& message, eLogLevel level,
								   const std::string file, uint32_t lineNumber)>> mSinks;

	std::unique_ptr<Thread::ActiveObject> mActive;
};
}
}

/// @brief A macro that automatically creates a thread-sensitive log.
///
/// All the contents are garunteed to be comitted in on line. Uses the global logger.
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

/// @brief same as gLogMessage
#define gLog gLogLevel(MESSAGE)

/// @brief uses gLogLevel with DEBUG severity
#define gLogDebug gLogLevel(DEBUG)
/// @brief uses gLogLevel with MESSAGE severity
#define gLogMessage gLogLevel(MESSAGE)
/// @brief uses gLogLevel with ERROR severity
#define gLogError gLogLevel(ERROR_)
/// @brief uses gLogLevel with WARNING severity
#define gLogWarning gLogLevel(WARNING)
/// @brief uses gLogLevel with FATAL severity
#define gLogFatal gLogLevel(FATAL)
