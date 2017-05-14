#include "stdafx.h"

#include "signalSlot/SignalTaksTestSuit.h"

#include "engine/signalSlot/SignalCaller.h"

#include "engine/signalSlot/SignalTask.h"

namespace
{
	struct TestObject
	{
		void testFunction()
		{
			nCalls++;
		}
		uint32_t nCalls = 0;
	};
}

namespace tests
{
	void SignalTaskTest::expiredTest01()
	{
		TestObject object;
		std::function<void()> callable = engine::SignalCaller<>::createCallable(&object, &TestObject::testFunction);

		std::shared_ptr<engine::SignalCaller<>> caller(new engine::SignalCaller<>(callable));

		std::weak_ptr<engine::SignalCaller<>> callerPtr = caller;

		engine::SignalTask<> task(callerPtr, {});
		assertTrue(ASSERTION_PARAMETER(!task.isExpired()));
	}

	void SignalTaskTest::expiredTest02()
	{
		TestObject object;
		std::function<void()> callable = engine::SignalCaller<>::createCallable(&object, &TestObject::testFunction);
		std::weak_ptr<engine::SignalCaller<>> callerPtr;

		{
			std::shared_ptr<engine::SignalCaller<>> caller(new engine::SignalCaller<>(callable));

			callerPtr = caller;
		}

		engine::SignalTask<> task(callerPtr, {});

		assertTrue(ASSERTION_PARAMETER(task.isExpired()));
	}

	void SignalTaskTest::operatorTest01()
	{
		TestObject object;
		std::function<void()> callable = engine::SignalCaller<>::createCallable(&object, &TestObject::testFunction);

		std::shared_ptr<engine::SignalCaller<>> caller(new engine::SignalCaller<>(callable));

		std::weak_ptr<engine::SignalCaller<>> callerPtr = caller;

		engine::SignalTask<> task(callerPtr, {});
		task();
		assertTrue(ASSERTION_PARAMETER(object.nCalls == 1));
	}

	void SignalTaskTest::operatorTest02()
	{
		TestObject object;
		std::function<void()> callable = engine::SignalCaller<>::createCallable(&object, &TestObject::testFunction);
		std::weak_ptr<engine::SignalCaller<>> callerPtr;

		{
			std::shared_ptr<engine::SignalCaller<>> caller(new engine::SignalCaller<>(callable));

			callerPtr = caller;
		}

		engine::SignalTask<> task(callerPtr, {});
		bool hasException = false;
		try
		{
			task();
		}
		catch(engine::test::GameAssertException &)
		{
			hasException = true;
		}
		assertTrue(ASSERTION_PARAMETER(hasException));
	}
}
