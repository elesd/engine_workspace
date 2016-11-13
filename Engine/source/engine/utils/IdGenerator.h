#pragma once

namespace engine
{
	namespace utils
	{
		template<typename TAG>
		class IdGenerator
		{
			static uint32_t counter;

		public:
			static uint32_t generateNextId();
		};

		template<typename TAG>
		uint32_t IdGenerator<TAG>::counter = 0;

		template<typename TAG>
		uint32_t IdGenerator<TAG>::generateNextId() { return counter++; }
	}
}
