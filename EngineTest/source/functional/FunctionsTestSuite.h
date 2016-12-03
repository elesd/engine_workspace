#pragma once

#include "engine/test/TestSuite.h"
#include "engine/test/TestCase.h"

namespace tests
{
	class FunctionsTestSuite : public engine::test::TestSuite
	{
		ENGINE_TEST_SUITE(FunctionsTestSuite);
	public:
		FunctionsTestSuite() : engine::test::TestSuite("Functions")
		{		}

		ENGINE_TEST_CASE(equalToTest01);
		ENGINE_TEST_CASE(equalToTest02);

		ENGINE_TEST_CASE(rawPointerEqualToTest01);
		ENGINE_TEST_CASE(rawPointerEqualToTest02);

		ENGINE_TEST_CASE(uniquePointerEqualToTest01);
		ENGINE_TEST_CASE(uniquePointerEqualToTest02);

		ENGINE_TEST_CASE(smartPointerEqualToTest01);
		ENGINE_TEST_CASE(smartPointerEqualToTest02);

		ENGINE_TEST_CASE(weakPointerEqualToTest01);
		ENGINE_TEST_CASE(weakPointerEqualToTest02);
	};
}