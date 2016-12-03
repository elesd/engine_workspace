#pragma once

#include "engine/test/TestSuite.h"
#include "engine/test/TestCase.h"

namespace tests
{
	class StateStackTestSuite : public engine::test::TestSuite
	{
		ENGINE_TEST_SUITE(StateStackTestSuite);
	public:
		StateStackTestSuite() : engine::test::TestSuite("StateStack")
		{		}

		ENGINE_TEST_CASE(pushStateTestOnePush);
		ENGINE_TEST_CASE(pushStateTestTwoPushes);

		ENGINE_TEST_CASE(popStateTestOnePop);
		ENGINE_TEST_CASE(popStateTestTwoPops);
		ENGINE_TEST_CASE(popStateTestUnderflow);

		ENGINE_TEST_CASE(changeStateTest);
		ENGINE_TEST_CASE(changeStateTestDouble);

		ENGINE_TEST_CASE(exitStateTest);
		ENGINE_TEST_CASE(exitStateTestDouble);

		ENGINE_TEST_CASE(exitStateAndChangeState);
	};
}