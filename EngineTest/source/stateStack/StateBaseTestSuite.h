#pragma once

#include "engine/test/TestSuite.h"
#include "engine/test/TestCase.h"

namespace tests
{
	namespace stateStack
	{
		class StateBaseTestSuite: public engine::test::TestSuite
		{
			ENGINE_TEST_SUITE(StateBaseTestSuite);
		public:
			StateBaseTestSuite(): engine::test::TestSuite("StateBase")
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
}