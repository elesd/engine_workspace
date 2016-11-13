#pragma once

#include "engine/test/TestSuite.h"
#include "engine/test/TestCase.h"

namespace tests
{
	namespace signalSlot
	{
		class SignalManagerTest : public engine::test::TestSuite
		{
			ENGINE_TEST_SUITE(SignalManagerTest);
		public:
			SignalManagerTest(): engine::test::TestSuite("SignalManager")	{}
		private:
			ENGINE_TEST_CASE(addTaskTest01);
			ENGINE_TEST_CASE(addTaskTest02);
			ENGINE_TEST_CASE(addTaskTest03);
			ENGINE_TEST_CASE(expireTest01);
		};
	}
}