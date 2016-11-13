#pragma once

#include "engine/test/TestSuite.h"
#include "engine/test/TestCase.h"

namespace tests
{
	namespace signalSlot
	{
		class SlotHolderTest: public engine::test::TestSuite
		{
			ENGINE_TEST_SUITE(SlotHolderTest);
		public:
			SlotHolderTest(): engine::test::TestSuite("SignalHolder") {};
		private:
			ENGINE_TEST_CASE(addTest01);
			ENGINE_TEST_CASE(addTest02);
			ENGINE_TEST_CASE(removeTest01);
			ENGINE_TEST_CASE(removeTest02);
			ENGINE_TEST_CASE(removeTest03);

			ENGINE_TEST_CASE(destructorTest);
		};
	}
}