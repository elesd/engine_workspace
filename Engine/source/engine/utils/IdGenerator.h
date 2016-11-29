#pragma once

#include <thread>
#include <mutex>

namespace engine
{
	namespace utils
	{
		/**
		* Helper class for id generation based on tag.
		* Thread safe.
		*/
		template<typename TAG>
		class IdGenerator
		{
			/**Counter for unique id*/
			static uint32_t counter;

			/**mutex for counter*/
			static std::mutex counterMutex;
		public:
			/**Generates a next id*/
			static uint32_t generateNextId();
		};

		template<typename TAG>
		uint32_t IdGenerator<TAG>::counter = 0;

		template<typename TAG>
		uint32_t IdGenerator<TAG>::generateNextId() { std::lock_guard<std::mutex> lock(counterMutex); guard return counter++; }

		template<typename TAG>
		uint32_t IdGenerator<TAG>::counterMutex;
	}
}
