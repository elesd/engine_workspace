#pragma once

#include <thread>
#include <mutex>

namespace engine
{
	namespace utils
	{

		template<typename T>
		struct CountedObject
		{
		public:
			static uint64_t getObjectCount() const 
			{
				std::lock_guard<std::mutex> lock(countProtector);
				return count; 
			}
		private:
			static uint64_t count;
		protected:
			CountedObject()
			{
				std::lock_guard<std::mutex> lock(countProtector);
				count++;
			}

			virtual ~CountedObject()
			{
				std::lock_guard<std::mutex> lock(countProtector);
				count--;
			}
		private:
			std::mutex countProtector;
		};

		template<typename T>
		uint64_t CountedObject<T>::count = 0;
	}
}
