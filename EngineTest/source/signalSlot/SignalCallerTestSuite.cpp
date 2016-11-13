#include "stdafx.h"

#include "signalSlot/SignalCallerTestSuite.h"

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
	namespace signalSlot
	{
		void SignalCallerTestSuite::createCallableTest01()
		{
			TestObject o1;
			auto func = engine::signalSlot::SignalCaller<>::createCallable(&o1, &TestObject::testFunction01);
			func();
			assertTrue(ASSERTION_PARAMETER(o1.callId == 1));
		}

		void SignalCallerTestSuite::createCallableTest02()
		{
			TestObject o1;
			auto func = engine::signalSlot::SignalCaller<int, int>::createCallable(&o1, &TestObject::testFunction02);
			func(2, 3);
			assertTrue(ASSERTION_PARAMETER(o1.callId == 2));
		}

		void SignalCallerTestSuite::createCallableTest03()
		{
			TestObject o1;
			auto func = engine::signalSlot::SignalCaller<const SpecialType &, int>::createCallable(&o1, &TestObject::testFunction03);
			func(SpecialType(), 3);
			assertTrue(ASSERTION_PARAMETER(o1.callId == 3));
		}

		void SignalCallerTestSuite::createCallableTest04()
		{
			TestObject o1;
			auto func = engine::signalSlot::SignalCaller<SpecialType, int>::createCallable(&o1, &TestObject::testFunction04);
			func(SpecialType(), 3);
			assertTrue(ASSERTION_PARAMETER(o1.callId == 4));
		}

		void SignalCallerTestSuite::operatorTest01()
		{
			TestObject o1;
			auto func = engine::signalSlot::SignalCaller<>::createCallable(&o1, &TestObject::testFunction01);
			engine::signalSlot::SignalCaller<> caller(func);
			caller({});
			assertTrue(ASSERTION_PARAMETER(o1.callId == 1));
		}

		void SignalCallerTestSuite::operatorTest02()
		{
			TestObject o1;
			auto func = engine::signalSlot::SignalCaller<int, int>::createCallable(&o1, &TestObject::testFunction02);
			engine::signalSlot::SignalCaller<int, int> caller(func);
			caller(std::make_tuple(2, 2));
			assertTrue(ASSERTION_PARAMETER(o1.callId == 2));
		}

		void SignalCallerTestSuite::operatorTest03()
		{
			TestObject o1;
			auto func = engine::signalSlot::SignalCaller<const SpecialType &, int>::createCallable(&o1, &TestObject::testFunction03);
			engine::signalSlot::SignalCaller<const SpecialType &, int> caller(func);
			caller(std::make_tuple(SpecialType(), 2));
			assertTrue(ASSERTION_PARAMETER(o1.callId == 3));
		}

		void SignalCallerTestSuite::operatorTest04()
		{
			TestObject o1;
			auto func = engine::signalSlot::SignalCaller<SpecialType, int>::createCallable(&o1, &TestObject::testFunction04);
			engine::signalSlot::SignalCaller<SpecialType, int> caller(func);
			caller(std::make_tuple(SpecialType(), 2));
			assertTrue(ASSERTION_PARAMETER(o1.callId == 4));
		}
	}
}
