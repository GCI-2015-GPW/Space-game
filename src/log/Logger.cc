// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "log/Logger.h"
#include "log/LogSink.h"

using namespace Engine;
using namespace Core;

Logger::Logger(const std::string& filename)
{
	mActive = Thread::ActiveObject::create();

	add(makeConsoleSink());
	add(makeFileSink(filename));
}

LogMessage Logger::operator()(
	eLogLevel level,
	const std::string& filename,
	int line
)
{
	return LogMessage(level, filename, line, this);
}

void Logger::add(const LogSink& sink)
{
	mSinks.push_back(sink); // TODO: Check for duplicates.
}

void Logger::remove(const LogSink& sink)
{
	auto it = std::find(mSinks.begin(), mSinks.end(), sink);

	if (it == mSinks.end())
		throw std::runtime_error("Tried to remove a sink that was not added yet!\n");

	mSinks.erase(it);
}

void Logger::flush(const LogMessage& message) const
{
	/*
	// Single-threaded version

	auto msg = message.mBuffer.str();

	for (auto&& sink: mSinks)
		sink.forward(message.mMeta, msg);
	*/

	// Multi-threaded version

	auto&& sinks = mSinks;
	auto&& meta = message.mMeta;
	auto msg = message.mBuffer.str();

	mActive->send([=] {
		for (auto&& sink : sinks)
			sink.forward(meta, msg);
	});
}

Logger gLogger("Engine.log");
