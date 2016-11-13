#include "stdafx.h"

#include "signalSlot/SlotHolderTest.h"

#include "engine/signalSlot/SlotHolder.h"
#include "engine/signalSlot/Signal.h"
#include "engine/signalSlot/ISignalManager.h"


namespace
{
	class TestSignalManager: public engine::signalSlot::ISignalManager
	{
	public:
		void addTask(std::unique_ptr<engine::signalSlot::ISignalTask> task) override
		{
			(*task)();
			nTasks++;
		}
		void update() override
		{}
		uint32_t nTasks = 0;
	};

	struct TestEnvironment
	{
		static TestSignalManager signalManager;
		static void init() { signalManager.nTasks = 0; }
	};

	TestSignalManager TestEnvironment::signalManager;


	class TestHolder: public engine::signalSlot::SlotHolder
	{
	public:
		engine::signalSlot::Signal<int> testSignal;
		void testFunction(int){ nCalls++; }

		engine::signalSlot::ISignalManager *getSignalManager() const override { return &TestEnvironment::signalManager; }
		uint32_t nCalls = 0;
	};
	class TestEmitter
	{
	public:
		engine::signalSlot::Signal<int> testSignal;
	};
}

namespace tests
{
	namespace signalSlot
	{
		void SlotHolderTest::addTest01()
		{
			TestEnvironment::init();
			TestHolder object;
			object.assignSignal(&object.testSignal);
			object.testSignal.emit(2);
			assertTrue(ASSERTION_PARAMETER(object.nCalls == 1));
		}

		void SlotHolderTest::addTest02()
		{
			TestEnvironment::init();
			TestHolder object;
			object.assignSignal(&object.testSignal);
			object.assignSignal(&object.testSignal);
			object.testSignal.emit(2);
			assertTrue(ASSERTION_PARAMETER(object.nCalls == 1));
		}
		void SlotHolderTest::removeTest01()
		{
			TestEnvironment::init();
			TestHolder object;
			object.assignSignal(&object.testSignal);
			object.removeSignal(&object.testSignal);
			object.testSignal.emit(2);
			assertTrue(ASSERTION_PARAMETER(object.nCalls == 0));
		}

		void SlotHolderTest::removeTest02()
		{
			TestEnvironment::init();
			TestHolder object;
			object.assignSignal(&object.testSignal);
			object.assignSignal(&object.testSignal);
			object.testSignal.emit(2);
			object.removeSignal(&object.testSignal);
			object.testSignal.emit(2);
			assertTrue(ASSERTION_PARAMETER(object.nCalls == 1));
		}

		void SlotHolderTest::removeTest03()
		{
			TestEnvironment::init();
			TestHolder object;
			object.assignSignal(&object.testSignal);
			object.removeSignal(&object.testSignal);
			bool hasException = false;
			try
			{
				object.removeSignal(&object.testSignal);
			}
			catch(engine::test::GameAssertException &)
			{
				hasException = true;
			}
			assertTrue(ASSERTION_PARAMETER(!hasException));
		}

		void SlotHolderTest::destructorTest()
		{
			TestEnvironment::init();
			TestEmitter emitter;
			{
				TestHolder holder;
				holder.assignSignal(&emitter.testSignal);
			}
			emitter.testSignal.emit(2);

			assertTrue(ASSERTION_PARAMETER(TestEnvironment::signalManager.nTasks == 0));
		}

	}
}
