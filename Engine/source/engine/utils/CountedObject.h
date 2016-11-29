#pragma once

#include <thread>
#include <mutex>

namespace engine
{
	namespace utils
	{
		/**
		* Base class to check object creation.
		* Thread safe.
		* @tparam T: The class which creation will counted.
		*/
		template<typename T>
		struct CountedObject
		{
		public:
			/**
			* @return Retuns how much object is still alive from the given class.
			*/
			static uint64_t getObjectCount() const 
			{
				std::lock_guard<std::mutex> lock(countProtector);
				return count; 
			}
		private:
			/** Number of active instance*/
			static uint64_t count;
		protected:
			/**
			* Constructor for counting
			*/
			CountedObject()
			{
				std::lock_guard<std::mutex> lock(countProtector);
				count++;
			}
			/**
			* Destructor for counting
			*/
			virtual ~CountedObject()
			{
				std::lock_guard<std::mutex> lock(countProtector);
				count--;
			}
		private:
			/**Mutex to lock the counter*/
			std::mutex countProtector;
		};

		template<typename T>
		uint64_t CountedObject<T>::count = 0;
	}
}
