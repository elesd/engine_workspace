#pragma once

#include "engine/utils/DeclTypeToType.h"

#include "engine/test/ITestCase.h"

namespace engine
{
	namespace test
	{

		template<class TS, void (TS::*func)()>
		class TestCase : public ITestCase
		{
		public:
			TestCase() {}
			TestCase(TS *testSuite, const std::string &name)
				: _testSuite(testSuite),
				name(name)
			{
				testSuite->addTestCase(this);
			}

			void execute() override
			{
				(_testSuite->*func)();
			}

			const std::string &getName() const override { return name; }
		private:
			TS *_testSuite = nullptr;
			const std::string name;
		};

	}
}


#define ENGINE_TEST_SUITE(test_suite) static test_suite *getThisForTestCase(){ return (test_suite *)(nullptr); } \
		using testSuiteType = std::remove_pointer<engine::DeclTypeToType<decltype(getThisForTestCase())>::Value>::type;
#define ENGINE_TEST_CASE(test_case) void test_case(); engine::test::TestCase<testSuiteType, &testSuiteType::test_case> tc_##test_case{this, #test_case};
