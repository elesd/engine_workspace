#pragma once

namespace engine
{
	namespace test
	{
		class ITestCase;

		/**
		* Test suite implementation.
		* A test suite contains the test cases and collects the run results of it.
		*/
		class TestSuit
		{
		public:
			/**Length of the output lines*/
			static const size_t lineLength;
		protected:
			/**
			* Creates a test suite with the name of it
			* @param name: Name of the test suite
			*/
			TestSuit(const std::string &name);
			/**Copyable for childs*/
			TestSuit(const TestSuit &);
			/**Moveable for childs*/
			TestSuit(TestSuit &&);

		public:
			/**PIMPL*/
            virtual ~TestSuit();
			/**Add a test case for the suite*/
			void addTestCase(ITestCase *testCase);
			/**Run all the test cases*/
			void run() const;
			/**Sets the output stream.*/
			void setStream(std::ostream *);
			
			/**@return Returns the number of Not ok test cases*/
			uint32_t getNumOfNok() const;

			/**@return Returns the number of test cases*/
			uint32_t getNumOfTestCases() const;
			/**@return Returns a number between 0 and 1 which represents the test suite exectution result.*/
			float getPercentageResult() const;
		protected:
			/**Assertion true base implementation*/
			void assertTrue(bool value, const std::string &message, const std::string &file, const uint32_t line);
		private:
			/**PIMPL*/
			struct TestSuitPrivate *_members = nullptr;
		};
	}
}

/**
* Creates parameter for assert functions of test cases based on the condition.
*/
#define ASSERTION_PARAMETER(condition) condition, #condition, __FILE__, __LINE__
