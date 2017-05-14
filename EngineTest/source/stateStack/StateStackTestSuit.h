#pragma once

#include "engine/test/TestSuit.h"
#include "engine/test/TestCase.h"

namespace tests
{
	class StateStackTestSuit : public engine::test::TestSuit
	{
		ENGINE_TEST_SUIT(StateStackTestSuit);
	public:
		StateStackTestSuit() : engine::test::TestSuit("StateStack")
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