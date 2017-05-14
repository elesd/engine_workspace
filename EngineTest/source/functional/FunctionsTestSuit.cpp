#include "stdafx.h"

#include "functional/FunctionsTestSuit.h"
#include "engine/functional/functions.h"

namespace tests
{
	void FunctionsTestSuit::equalToTest01()
	{
		engine::EqualTo<int> equalityCheck(2);
		bool equals = equalityCheck(2);
		assertTrue(ASSERTION_PARAMETER(equals));
	}

	void FunctionsTestSuit::equalToTest02()
	{
		engine::EqualTo<int> equalityCheck(2);
		bool equals = equalityCheck(3);
		assertTrue(ASSERTION_PARAMETER(!equals));
	}

	void FunctionsTestSuit::rawPointerEqualToTest01()
	{
		int a = 2;
		int *i = &a;
		engine::PointerEqualTo<int> equalityCheck(i);
		bool equals = equalityCheck(i);
		assertTrue(ASSERTION_PARAMETER(equals));
	}

	void FunctionsTestSuit::rawPointerEqualToTest02()
	{
		int a = 2;
		int *i = &a;
		int *j = nullptr;
		engine::PointerEqualTo<int> equalityCheck(i);
		bool equals = equalityCheck(j);
		assertTrue(ASSERTION_PARAMETER(!equals));
	}

	void FunctionsTestSuit::uniquePointerEqualToTest01()
	{

		int *i = new int();
		std::unique_ptr<int> uniqueI(i);
		engine::PointerEqualTo<int> equalityCheck(i);
		bool equals = equalityCheck(uniqueI);
		assertTrue(ASSERTION_PARAMETER(equals));
	}

	void FunctionsTestSuit::uniquePointerEqualToTest02()
	{
		int *i = new int();

		int *j = nullptr;
		std::unique_ptr<int> uniqueI(j);
		engine::PointerEqualTo<int> equalityCheck(i);
		bool equals = equalityCheck(uniqueI);
		assertTrue(ASSERTION_PARAMETER(!equals));
	}

	void FunctionsTestSuit::smartPointerEqualToTest01()
	{
		int *i = new int();

		std::shared_ptr<int> uniqueI(i);
		engine::PointerEqualTo<int> equalityCheck(i);
		bool equals = equalityCheck(uniqueI);
		assertTrue(ASSERTION_PARAMETER(equals));
	}

	void FunctionsTestSuit::smartPointerEqualToTest02()
	{
		int *i = new int();

		int *j = nullptr;
		std::shared_ptr<int> uniqueI(j);
		engine::PointerEqualTo<int> equalityCheck(i);
		bool equals = equalityCheck(uniqueI);
		assertTrue(ASSERTION_PARAMETER(!equals));
	}

	void FunctionsTestSuit::weakPointerEqualToTest01()
	{
		int *i = new int();

		std::shared_ptr<int> uniqueI(i);
		std::weak_ptr<int> weak(uniqueI);
		engine::PointerEqualTo<int> equalityCheck(i);
		bool equals = equalityCheck(weak);
		assertTrue(ASSERTION_PARAMETER(equals));
	}

	void FunctionsTestSuit::weakPointerEqualToTest02()
	{
		int *i = new int();

		int *j = nullptr;
		std::shared_ptr<int> uniqueI(j);
		std::weak_ptr<int> weak(uniqueI);
		engine::PointerEqualTo<int> equalityCheck(i);
		bool equals = equalityCheck(weak);
		assertTrue(ASSERTION_PARAMETER(!equals));
	}
}

