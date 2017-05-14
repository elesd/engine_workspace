#pragma once

#include "engine/test/TestSuit.h"
#include "engine/test/TestCase.h"

namespace tests
{
	class FunctionsTestSuit : public engine::test::TestSuit
	{
		ENGINE_TEST_SUIT(FunctionsTestSuit);
	public:
		FunctionsTestSuit() : engine::test::TestSuit("Functions")
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