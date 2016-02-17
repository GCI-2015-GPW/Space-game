// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#ifndef ENGINE_THREAD_ACTIVEOBJECTS_H_
#define ENGINE_THREAD_ACTIVEOBJECTS_H_

#include <memory>
#include <functional>
#include <thread>

#include <thread>

#include <boost/thread/concurrent_queues/sync_deque.hpp>

namespace Engine
{
namespace Thread
{
/**
        Based on Sutters, this is an Active Object.
        Allows threadsafe execution of void() functions in an object (by
   internally queuing calls)
        The object maintians its own (Os-level!) thread, so don't overuse this.
*/
typedef std::function<void()> Callback;

class ActiveObject
{
private:
    ActiveObject();  // Only allow creation via the factory method.

public:
    ActiveObject(const ActiveObject &) = delete;
    ActiveObject &operator=(const ActiveObject &) = delete;

    ~ActiveObject();

    static std::unique_ptr<ActiveObject> create();  // Factory Method.
                                                    /**
                                                            In practice, call this with [=] lambda's -- by copying the data
                                                            we ensure that the data to be worked on is still live by the time
                                                            the active object gets to actually process it.
                                                
                                                            [NOTE] if the callback calls non-const methods the lambda will have to
                                                       be mutable... -_-
                                                    */
    void send(Callback message);

private:
    void run();  // Thread Method

    bool mIsDone;
    boost::sync_deque<Callback> mMessageQueue;

    std::thread mThread;
};
}
}

#endif
