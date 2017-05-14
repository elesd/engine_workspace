#pragma once

#include "engine/test/TestSuit.h"
#include "engine/test/TestCase.h"

namespace tests
{
	class StateBaseTestSuit : public engine::test::TestSuit
	{
		ENGINE_TEST_SUIT(StateBaseTestSuit);
	public:
		StateBaseTestSuit() : engine::test::TestSuit("StateBase")
		{		}

		ENGINE_TEST_CASE(initTest01);

		ENGINE_TEST_CASE(resumeTest);

		ENGINE_TEST_CASE(pauseTest);

		ENGINE_TEST_CASE(exitDuringResum);
		ENGINE_TEST_CASE(changeDuringResum);
		ENGINE_TEST_CASE(exitDuringPause);
		ENGINE_TEST_CASE(changeDuringPause);
	};
}