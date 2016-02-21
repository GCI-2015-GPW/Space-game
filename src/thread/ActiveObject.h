// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

/// @file ActiveObject.h
///
/// Defines the ActiveObject class

#pragma once

#include <memory>
#include <functional>
#include <thread>

#include <thread>

#include <boost/thread/concurrent_queues/sync_deque.hpp>

namespace Engine
{
namespace Thread
{
/// @brief A generic callback, with possible state
typedef std::function<void()> Callback;


/// @brief Allows threadsafe execution of void() functions in an object
///
/// Allows threadsafe execution of void() functions in an object (by
/// internally queuing calls)
/// The object maintians its own (Os-level!) thread, so don't overuse this.
/// Based on <a href="http://www.drdobbs.com/parallel/prefer-using-active-objects-instead-of-n/225700095">Sutter's implementation</a>
class ActiveObject
{
private:
	ActiveObject();  // Only allow creation via the factory method.

public:
	ActiveObject(const ActiveObject &) = delete;
	ActiveObject &operator=(const ActiveObject &) = delete;

	~ActiveObject();

	/// @brief Factory method
	static std::unique_ptr<ActiveObject> create();  // Factory Method.
	
	
	/// @brief Queues up an item
	///
	/// In practice, call this with a lambda, but be very careful about lifetimes.
	void send(Callback message);

private:
	void run();  // Thread Method

	bool mIsDone;
	boost::sync_deque<Callback> mMessageQueue;

	std::thread mThread;
};
}
}
