// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "log/LogSink.h"

#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include <chrono>
#include <iomanip>
#include <ctime>

namespace Engine {
namespace Core {

LogSink::LogSink(const LogSink &sink) : mWrapper(sink.mWrapper->clone()) {}

LogSink &LogSink::operator=(LogSink sink) {
    // The signature already copy-constructed a new sink,
    // so we only need to move from the temporary to this object.
    mWrapper = std::move(sink.mWrapper);
    return *this;
}

bool LogSink::operator==(const LogSink &sink) const {
    return (mWrapper.get() == sink.mWrapper.get());
}

void LogSink::forward(const LogMessage::Meta &meta, const std::string &message) const {
    mWrapper->forward(meta, message);
}

LogSink makeConsoleSink() {
    return [](const LogMessage::Meta &meta, const std::string &message) {
        std::cout << meta.mLevel << message << "\n";
    };
}

namespace {
struct FileSink {
    FileSink(const std::string &filename) : mFile(std::make_shared<std::ofstream>(filename)) {
        if (!mFile->good()) {
            std::string message = "Failed to open file sink: ";
            message.append(filename);
            throw std::runtime_error(message);
        }
    }

    void operator()(const LogMessage::Meta &meta, const std::string &message) const {
        using namespace std::chrono;

        auto now = system_clock::now();
        auto time_t = system_clock::to_time_t(now);
        auto local_time = std::localtime(&time_t);

        (*mFile) << std::put_time(local_time, "[%H:%M:%S] ") << meta.mLevel << message << " ("
                 << meta.mFile << ":" << meta.mLine << ")\n";
    }

    std::shared_ptr<std::ofstream> mFile;
};
}

LogSink makeFileSink(const std::string &filename) { return FileSink(filename); }

}  // namespace Core
}  // namespace Engine
