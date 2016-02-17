// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "log/LogLevel.h"

#include <atomic>

namespace Engine {
	namespace Core {
		namespace {
			std::atomic<bool> gLogLevelState[5]{
				{ true },	// DEBUG
				{ true },	// MESSAGE
				{ true },	// WARNING
				{ true },	// ERROR_
				{ true }	// FATAL
			};

			int selectLogState(eLogLevel level)
			{
				//FIXME: Inline this?

				switch (level) {
				case eLogLevel::DEBUG:		return 0;
				case eLogLevel::MESSAGE:	return 1;
				case eLogLevel::WARNING:	return 2;
				case eLogLevel::ERROR_:		return 3;
				case eLogLevel::FATAL:		return 4;

				default:
					throw std::runtime_error("Unsupported loglevel!\n");
				}
			}
		}

		void setLogLevel(eLogLevel level, bool enabled)
		{
			int lvl = selectLogState(level);
			gLogLevelState[lvl].store(enabled, std::memory_order_release);
		}

		bool logLevel(eLogLevel level)
		{
			int lvl = selectLogState(level);
			return gLogLevelState[lvl].load(std::memory_order_acquire);
		}
	}
}

std::ostream& operator << (std::ostream& os, const Engine::Core::eLogLevel& level)
{
	using Engine::Core::eLogLevel;

	// Chosen so you'll have an easy time spotting them in the actual log.

	switch (level) {
	case eLogLevel::DEBUG:		os << " [DEBUG]: ";  break;
	case eLogLevel::MESSAGE:	os << "[STDOUT]: ";  break; // This should be the standard output.
	case eLogLevel::WARNING:	os << "*WARNING* ";  break;
	case eLogLevel::ERROR_:		os << "< ERROR > ";  break;
	case eLogLevel::FATAL:		os << "<## FATAL ##> "; break;
	default:
		os << "Unknown";
	}

	return os;
}
