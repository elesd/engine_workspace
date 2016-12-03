#pragma once

#include "engine/test/TestCase.h"
#include "engine/test/TestSuite.h"

namespace tests
{
	class SignalTaskTest : public engine::test::TestSuite
	{
		ENGINE_TEST_SUITE(SignalTaskTest);
	public:
		SignalTaskTest() : engine::test::TestSuite("SignalTask")	{}
	private:
		ENGINE_TEST_CASE(expiredTest01);
		ENGINE_TEST_CASE(expiredTest02);
		ENGINE_TEST_CASE(operatorTest01);
		ENGINE_TEST_CASE(operatorTest02);
	};
}