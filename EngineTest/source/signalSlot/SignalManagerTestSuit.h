#pragma once

#include "engine/test/TestSuit.h"
#include "engine/test/TestCase.h"

namespace tests
{
	class SignalManagerTest : public engine::test::TestSuit
	{
		ENGINE_TEST_SUIT(SignalManagerTest);
	public:
		SignalManagerTest() : engine::test::TestSuit("SignalManager")	{}
	private:
		ENGINE_TEST_CASE(addTaskTest01);
		ENGINE_TEST_CASE(addTaskTest02);
		ENGINE_TEST_CASE(addTaskTest03);
		ENGINE_TEST_CASE(expireTest01);
	};
}