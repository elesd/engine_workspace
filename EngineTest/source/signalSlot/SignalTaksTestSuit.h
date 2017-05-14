#pragma once

#include "engine/test/TestCase.h"
#include "engine/test/TestSuit.h"

namespace tests
{
	class SignalTaskTest : public engine::test::TestSuit
	{
		ENGINE_TEST_SUIT(SignalTaskTest);
	public:
		SignalTaskTest() : engine::test::TestSuit("SignalTask")	{}
	private:
		ENGINE_TEST_CASE(expiredTest01);
		ENGINE_TEST_CASE(expiredTest02);
		ENGINE_TEST_CASE(operatorTest01);
		ENGINE_TEST_CASE(operatorTest02);
	};
}