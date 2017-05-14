#pragma once

#include "engine/test/TestSuit.h"
#include "engine/test/TestCase.h"

namespace tests
{
	class FilePathTestSuit : public engine::test::TestSuit
	{
		ENGINE_TEST_SUIT(FilePathTestSuit);
	public:
		FilePathTestSuit() : engine::test::TestSuit("FilePath")
		{
		}

		ENGINE_TEST_CASE(normalizeTest01);
		ENGINE_TEST_CASE(normalizeTest02);
		ENGINE_TEST_CASE(normalizeTest03);
		ENGINE_TEST_CASE(normalizeTest04);
		ENGINE_TEST_CASE(normalizeTest05);
		ENGINE_TEST_CASE(normalizeTest06);
		
		ENGINE_TEST_CASE(fileNameTest01);
		ENGINE_TEST_CASE(fileNameTest02);
		ENGINE_TEST_CASE(fileNameTest03);
		ENGINE_TEST_CASE(fileNameTest04);
		ENGINE_TEST_CASE(fileNameTest05);
		ENGINE_TEST_CASE(fileNameTest06);
		ENGINE_TEST_CASE(fileNameTest07);

		ENGINE_TEST_CASE(fileExtensionTest01);
		ENGINE_TEST_CASE(fileExtensionTest02);
		ENGINE_TEST_CASE(fileExtensionTest03);
		ENGINE_TEST_CASE(fileExtensionTest04);
		ENGINE_TEST_CASE(fileExtensionTest05);
		ENGINE_TEST_CASE(fileExtensionTest06);

		ENGINE_TEST_CASE(dirNameTest01);
		ENGINE_TEST_CASE(dirNameTest02);
		ENGINE_TEST_CASE(dirNameTest03);
		ENGINE_TEST_CASE(dirNameTest04);
	};
}