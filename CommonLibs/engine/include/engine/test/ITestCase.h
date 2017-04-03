#pragma once

namespace engine
{
	namespace test
	{
		/**
		* Interface for a test case.
		*/
		class ITestCase
		{
		protected:
			/**Default constructable*/
			ITestCase() = default;
			/**Due to public inheritance*/
			virtual ~ITestCase() = default;

		public:
			/**Execute the given test case*/
			virtual void execute() = 0;
			/**@return Returns the name of the test case.*/
			virtual const std::string &getName() const = 0;
		};
	}
}