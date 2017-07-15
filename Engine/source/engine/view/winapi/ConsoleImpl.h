#pragma once

#include <engine/view/Console.h>

namespace engine
{
	namespace winapi
	{
		class ConsoleImpl
			: public Console
		{
		public:
			~ConsoleImpl() override {};

		private:
			void printImpl(const std::string& str) const override;
		};
	}
}