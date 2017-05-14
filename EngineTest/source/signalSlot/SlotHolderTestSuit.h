#pragma once

#include "engine/test/TestSuit.h"
#include "engine/test/TestCase.h"

namespace tests
{
	class SlotHolderTest : public engine::test::TestSuit
	{
		ENGINE_TEST_SUIT(SlotHolderTest);
	public:
		SlotHolderTest() : engine::test::TestSuit("SignalHolder") {};
	private:
		ENGINE_TEST_CASE(addTest01);
		ENGINE_TEST_CASE(addTest02);
		ENGINE_TEST_CASE(removeTest01);
		ENGINE_TEST_CASE(removeTest02);
		ENGINE_TEST_CASE(removeTest03);

		ENGINE_TEST_CASE(destructorTest);
	};
}