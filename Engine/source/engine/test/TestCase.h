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
			* @param TestSuit: Test suit class
			* @param name: Test case name
			*/
			TestCase(TS *TestSuit, const std::string &name)
				: _TestSuit(TestSuit),
				name(name)
			{
				TestSuit->addTestCase(this);
			}

			/**Execute the test case*/
			void execute() override
			{
				(_TestSuit->*func)();
			}

			/**@return Returns the name of the test case*/
			const std::string &getName() const override { return name; }
		private:
			/**Test suit for the test case*/
			TS *_TestSuit = nullptr;
			/**Name of the test case*/
			const std::string name;
		};

	}
}

/**
* Declare a class as a test suite
* @param test_suite: Name of the class
*/
#define ENGINE_TEST_SUIT(test_suite) static test_suite *getThisForTestCase(){ return (test_suite *)(nullptr); } \
		using TestSuitType = std::remove_pointer<engine::DeclTypeToType<decltype(getThisForTestCase())>::Value>::type;

/**
* Declare a test suite. Basically creates a special function for the test case.
* @param test_case: name of the test case.
*/
#define ENGINE_TEST_CASE(test_case) void test_case(); engine::test::TestCase<TestSuitType, &TestSuitType::test_case> tc_##test_case{this, #test_case};
