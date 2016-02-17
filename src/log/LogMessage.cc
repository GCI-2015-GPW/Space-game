// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "log/LogMessage.h"
#include "log/Logger.h"

using namespace Engine;
using namespace Core;

LogMessage::LogMessage(eLogLevel level, const std::string& file, int line,
                       Logger* owner)
    : mOwner(owner) {
  mMeta = {level, file, line};
}

LogMessage::~LogMessage() {
  if (mOwner && logLevel(mMeta.mLevel)) mOwner->flush(*this);
}

LogMessage::LogMessage(LogMessage&& message)
    : mMeta(std::move(message.mMeta)),
      mOwner(std::move(message.mOwner)),
      mBuffer(std::move(message.mBuffer)) {
  message.mOwner = nullptr;
}

LogMessage& LogMessage::operator<<(std::ostream& (*fn)(std::ostream& os)) {
  fn(mBuffer);
  return *this;
}
