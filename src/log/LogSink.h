// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#pragma once

#ifndef ENGINE_LOG_LOGSINK_H_
#define ENGINE_LOG_LOGSINK_H_

#include "log/LogMessage.h"

#include <memory>

namespace Engine {
	namespace Core {
		class LogSink {
		public:
			template <typename T>
			LogSink(T impl);
			LogSink(const LogSink& sink);
			LogSink& operator= (LogSink sink);

			bool operator == (const LogSink& sink) const;

			void forward (
				const LogMessage::Meta& meta,
				const std::string& message
			) const;

		private:
			struct Concept {
				virtual ~Concept() = default;
				virtual Concept* clone() const = 0;

				virtual void forward(
					const LogMessage::Meta& meta,
					const std::string& message
				) const = 0;
			};

			template <typename T>
			struct Model : Concept {
				Model(T impl);

				virtual Concept* clone() const override;

				virtual void forward(
					const LogMessage::Meta& meta,
					const std::string& message
				) const override;

				T mImpl;
			};

			std::unique_ptr<Concept> mWrapper;
		};

		LogSink makeConsoleSink();
		LogSink makeFileSink(const std::string& filename);

		template <typename T>
		LogSink::LogSink(T impl):
			mWrapper(new Model<T>(std::move(impl)))
		{
		}

		template <typename T>
		LogSink::Model<T>::Model(T impl):
			mImpl(std::move(impl))
		{
		}

		template <typename T>
		LogSink::Concept* LogSink::Model<T>::clone() const
		{
			return new Model<T>(mImpl);
		}

		template <typename T>
		void LogSink::Model<T>::forward(
			const LogMessage::Meta& meta,
			const std::string& message
		) const
		{
			mImpl(meta, message);
		}
	}
}


#endif // ENGINE_LOG_LOGSINK_H_
