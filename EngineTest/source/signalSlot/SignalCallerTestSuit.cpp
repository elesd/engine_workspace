#include "stdafx.h"

#include "signalSlot/SignalCallerTestSuit.h"

#include "engine/signalSlot/SignalCaller.h"

namespace
{
	struct SpecialType
	{
		int i;
		float k;
	};
	struct TestObject
	{
		void testFunction01()
		{
			callId = 1;
		}

		void testFunction02(int, int)
		{
			callId = 2;
		}

		void testFunction03(const SpecialType &, int)
		{
			callId = 3;
		}

		void testFunction04(SpecialType, int)
		{
			callId = 4;
		}


		uint32_t callId = 0;
	};
}

namespace tests
{
	void SignalCallerTestSuit::createCallableTest01()
	{
		TestObject o1;
		auto func = engine::SignalCaller<>::createCallable(&o1, &TestObject::testFunction01);
		func();
		assertTrue(ASSERTION_PARAMETER(o1.callId == 1));
	}

	void SignalCallerTestSuit::createCallableTest02()
	{
		TestObject o1;
		auto func = engine::SignalCaller<int, int>::createCallable(&o1, &TestObject::testFunction02);
		func(2, 3);
		assertTrue(ASSERTION_PARAMETER(o1.callId == 2));
	}

	void SignalCallerTestSuit::createCallableTest03()
	{
		TestObject o1;
		auto func = engine::SignalCaller<const SpecialType &, int>::createCallable(&o1, &TestObject::testFunction03);
		func(SpecialType(), 3);
		assertTrue(ASSERTION_PARAMETER(o1.callId == 3));
	}

	void SignalCallerTestSuit::createCallableTest04()
	{
		TestObject o1;
		auto func = engine::SignalCaller<SpecialType, int>::createCallable(&o1, &TestObject::testFunction04);
		func(SpecialType(), 3);
		assertTrue(ASSERTION_PARAMETER(o1.callId == 4));
	}

	void SignalCallerTestSuit::operatorTest01()
	{
		TestObject o1;
		auto func = engine::SignalCaller<>::createCallable(&o1, &TestObject::testFunction01);
		engine::SignalCaller<> caller(func);
		caller({});
		assertTrue(ASSERTION_PARAMETER(o1.callId == 1));
	}

	void SignalCallerTestSuit::operatorTest02()
	{
		TestObject o1;
		auto func = engine::SignalCaller<int, int>::createCallable(&o1, &TestObject::testFunction02);
		engine::SignalCaller<int, int> caller(func);
		caller(std::make_tuple(2, 2));
		assertTrue(ASSERTION_PARAMETER(o1.callId == 2));
	}

	void SignalCallerTestSuit::operatorTest03()
	{
		TestObject o1;
		auto func = engine::SignalCaller<const SpecialType &, int>::createCallable(&o1, &TestObject::testFunction03);
		engine::SignalCaller<const SpecialType &, int> caller(func);
		caller(std::make_tuple(SpecialType(), 2));
		assertTrue(ASSERTION_PARAMETER(o1.callId == 3));
	}

	void SignalCallerTestSuit::operatorTest04()
	{
		TestObject o1;
		auto func = engine::SignalCaller<SpecialType, int>::createCallable(&o1, &TestObject::testFunction04);
		engine::SignalCaller<SpecialType, int> caller(func);
		caller(std::make_tuple(SpecialType(), 2));
		assertTrue(ASSERTION_PARAMETER(o1.callId == 4));
	}
}
