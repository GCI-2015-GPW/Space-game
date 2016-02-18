// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "log/Logger.h"

#include <fstream>

namespace Engine
{
namespace Core
{
Logger::Logger(const std::string& filename)
{
	mActive = Thread::ActiveObject::create();

	add([](const std::string& message, eLogLevel level, const std::string file, uint32_t lineNumber)
		{
			if (level == eLogLevel::MESSAGE)
				{
					std::cout << "MESSAGE [" << file << ":" << lineNumber << "] " << message
							  << std::endl;
				}

		});
	auto file = std::make_shared<std::ofstream>(filename);
	add([file](const std::string& message, eLogLevel level, const std::string fileName,
			   uint32_t lineNumber)
		{
			*file << level << "[" << fileName << ":" << lineNumber << "] " << message << std::endl;
		});
}

void Logger::add(const std::function<void(const std::string& message, eLogLevel level,
										  const std::string file, uint32_t lineNumber)> sink)
{
	mSinks.push_back(sink);
}

void Logger::write(const std::string& message, eLogLevel level, const std::string& file,
				   uint32_t lineNumber)
{
	mActive->send([
		this,
		message = std::string{std::move(message)},
		level,
		file = std::string{std::move(file)},
		lineNumber
	]
				  {
					  for (auto&& sink : mSinks) sink(message, level, file, lineNumber);
				  });
}

Logger* gLogger_ptr = nullptr;

}  // namespace Core
}  // namespace Engine
