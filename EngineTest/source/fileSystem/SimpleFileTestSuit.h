#pragma once

#include "engine/test/TestSuit.h"
#include "engine/test/TestCase.h"

namespace tests
{
	class SimpleFileTestSuit : public engine::test::TestSuit
	{
		ENGINE_TEST_SUIT(SimpleFileTestSuit);
	public:
		SimpleFileTestSuit() : engine::test::TestSuit("SimpleFile")
		{
		}

		ENGINE_TEST_CASE(openFileTest01);
		ENGINE_TEST_CASE(openFileTest02);

		ENGINE_TEST_CASE(readLineTest01);
		ENGINE_TEST_CASE(readLineTest02);
		ENGINE_TEST_CASE(readLineTest03);
		ENGINE_TEST_CASE(readLineTest04);

		ENGINE_TEST_CASE(readLinesTest01);
		ENGINE_TEST_CASE(readLinesTest02);
		ENGINE_TEST_CASE(readLinesTest03);


		ENGINE_TEST_CASE(readAllTest01);
		ENGINE_TEST_CASE(readAllTest02);
		ENGINE_TEST_CASE(readAllTest03);

		ENGINE_TEST_CASE(getSizeTest01);
		ENGINE_TEST_CASE(getSizeTest02);
		ENGINE_TEST_CASE(getSizeTest03);
	};
}