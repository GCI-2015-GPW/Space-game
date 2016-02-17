// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "thread/ActiveObjects.h"

using namespace Engine;
using namespace Thread;

ActiveObject::ActiveObject():
	mIsDone(false)
{
}

ActiveObject::~ActiveObject()
{
	send([this] { mIsDone = true; });

	mThread.join();
}

std::unique_ptr<ActiveObject> ActiveObject::create()
{
	std::unique_ptr<ActiveObject> result(new ActiveObject); // This constructor is private, so make_unique would require some hasle to get to work.

	result->mThread = boost::thread(&ActiveObject::run, result.get());

	return result;
}

void ActiveObject::send(Callback message)
{
	mMessageQueue.push_back(std::move(message));
}

void ActiveObject::run()
{
	while (!mIsDone)
	{
		Callback fn;

		//mMessageQueue.wait_pull_front(fn);

		fn();
	}
}
