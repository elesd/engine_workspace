#pragma once

#include "engine/test/TestSuite.h"
#include "engine/test/TestCase.h"

namespace tests
{
	class SignalCallerTestSuite : public engine::test::TestSuite
	{
		ENGINE_TEST_SUITE(SignalCallerTestSuite);
	public:
		SignalCallerTestSuite() : engine::test::TestSuite("SignalCaller")
		{		}

		ENGINE_TEST_CASE(createCallableTest01);
		ENGINE_TEST_CASE(createCallableTest02);
		ENGINE_TEST_CASE(createCallableTest03);
		ENGINE_TEST_CASE(createCallableTest04);

		ENGINE_TEST_CASE(operatorTest01);
		ENGINE_TEST_CASE(operatorTest02);
		ENGINE_TEST_CASE(operatorTest03);
		ENGINE_TEST_CASE(operatorTest04);

	};
}