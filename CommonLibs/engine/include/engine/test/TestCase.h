#pragma once

#include <engine/utils/DeclTypeToType.h>

#include <engine/test/ITestCase.h>

namespace engine
{
	namespace test
	{
		/**
		* Test case implementation for one test case.
		* @tparam TS: class for the test case implementation typically a test suite.
		* @tparam func: The test case it self.
		*/
		template<class TS, void (TS::*func)()>
		class TestCase : public ITestCase
		{
		public:
			/**Creates a test case.*/
			TestCase() = default;
			/**
			* Creates a test case for a test suit with a given name.
			* @param testSuite: Test suit class
			* @param name: Test case name
			*/
			TestCase(TS *testSuite, const std::string &name)
				: _testSuite(testSuite),
				name(name)
			{
				testSuite->addTestCase(this);
			}

			/**Execute the test case*/
			void execute() override
			{
				(_testSuite->*func)();
			}

			/**@return Returns the name of the test case*/
			const std::string &getName() const override { return name; }
		private:
			/**Test suit for the test case*/
			TS *_testSuite = nullptr;
			/**Name of the test case*/
			const std::string name;
		};

	}
}

/**
* Declare a class as a test suite
* @param test_suite: Name of the class
*/
#define ENGINE_TEST_SUITE(test_suite) static test_suite *getThisForTestCase(){ return (test_suite *)(nullptr); } \
		using testSuiteType = std::remove_pointer<engine::DeclTypeToType<decltype(getThisForTestCase())>::Value>::type;

/**
* Declare a test suite. Basically creates a special function for the test case.
* @param test_case: name of the test case.
*/
#define ENGINE_TEST_CASE(test_case) void test_case(); engine::test::TestCase<testSuiteType, &testSuiteType::test_case> tc_##test_case{this, #test_case};
