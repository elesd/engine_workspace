#pragma once

#include "engine/test/TestSuite.h"
#include "engine/test/TestCase.h"


namespace tests
{
	struct SignalTestSuite : public engine::test::TestSuite
	{
		SignalTestSuite();
		ENGINE_TEST_SUITE(SignalTestSuite);

		ENGINE_TEST_CASE(connectTest01);
		ENGINE_TEST_CASE(connectTest02);
		ENGINE_TEST_CASE(connectTest03);

		ENGINE_TEST_CASE(disconnectTest01);
		ENGINE_TEST_CASE(disconnectTest02);
		ENGINE_TEST_CASE(disconnectTest03);

		ENGINE_TEST_CASE(destructorTest01);
		ENGINE_TEST_CASE(destructorTest02);
	};
}