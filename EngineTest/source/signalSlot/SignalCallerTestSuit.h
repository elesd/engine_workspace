#pragma once

#include "engine/test/TestSuit.h"
#include "engine/test/TestCase.h"

namespace tests
{
	class SignalCallerTestSuit : public engine::test::TestSuit
	{
		ENGINE_TEST_SUIT(SignalCallerTestSuit);
	public:
		SignalCallerTestSuit() : engine::test::TestSuit("SignalCaller")
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