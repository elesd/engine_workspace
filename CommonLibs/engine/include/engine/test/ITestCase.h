#pragma once

namespace engine
{
	namespace test
	{
		class ITestCase
		{
		protected:
			ITestCase() = default;
			virtual ~ITestCase() = default;

		public:
			virtual void execute() = 0;
			virtual const std::string &getName() const = 0;
		};
	}
}