#pragma once

#include <thread>
#include <mutex>

namespace engine
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

	public:
		/**Generates a next id*/
		static uint32_t generateNextId();
	};

	template<typename TAG>
	uint32_t IdGenerator<TAG>::counter = 0;

	template<typename TAG>
	uint32_t IdGenerator<TAG>::generateNextId() 
	{
		static std::mutex lock;
		std::lock_guard<std::mutex> guard(lock);
		return counter++; 
	}

}
