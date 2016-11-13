#include "stdafx.h"
#include "signalSlot/SignalTest.h"

#include "engine/signalSlot/Signal.h"
#include "engine/signalSlot/SlotHolder.h"
#include "engine/signalSlot/ISignalManager.h"
#include "engine/signalSlot/SignalTask.h"


namespace
{
	struct CounterSignalManager: public engine::signalSlot::ISignalManager
	{
		void addTask(std::unique_ptr<engine::signalSlot::ISignalTask> task) override { nTasks++; };
		void update() override{}
		size_t nTasks;
	};
/////////////////////////////////////////////////////////////////////////////////////////////
	struct TestEnvironment
	{
		static CounterSignalManager signalManager;
	};

	CounterSignalManager TestEnvironment::signalManager;
/////////////////////////////////////////////////////////////////////////////////////////////
	struct TestObject
	{
		int i;
	};

	struct GeneralSlotHolder : engine::signalSlot::SlotHolder
	{


		engine::signalSlot::ISignalManager *getSignalManager() const override { return &TestEnvironment::signalManager; }
		void testSlot01() {}
		void testSlot02(int i){}
		void testSlot03(int i, float j){}
		void testSlot04(TestObject o){}
		void testSlot05(TestObject o, int j){}
	};

	struct GeneralSignalEmitter
	{
		engine::signalSlot::Signal<> testSignal01;
		engine::signalSlot::Signal<int> testSignal02;
		engine::signalSlot::Signal<int, float> testSignal03;
		engine::signalSlot::Signal<TestObject> testSignal04;
		engine::signalSlot::Signal<TestObject, int> testSignal05;
	};
}

namespace tests
{
	namespace signalSlot
	{
		SignalTestSuite::SignalTestSuite()
			: engine::test::TestSuite("SignalTest")
		{}

		void SignalTestSuite::connectTest01()
		{
			TestEnvironment::signalManager.nTasks = 0;
			GeneralSlotHolder slotHolder;
			GeneralSignalEmitter signalEmitter;
			CONNECT_SIGNAL(&signalEmitter, testSignal01, &slotHolder, testSlot01);
			CONNECT_SIGNAL(&signalEmitter, testSignal02, &slotHolder, testSlot02);
			CONNECT_SIGNAL(&signalEmitter, testSignal03, &slotHolder, testSlot03);
			CONNECT_SIGNAL(&signalEmitter, testSignal04, &slotHolder, testSlot04);
			CONNECT_SIGNAL(&signalEmitter, testSignal05, &slotHolder, testSlot05);
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal01.slots.size() == 1));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal02.slots.size() == 1));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal03.slots.size() == 1));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal04.slots.size() == 1));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal05.slots.size() == 1));

			assertTrue(ASSERTION_PARAMETER(TestEnvironment::signalManager.nTasks == 0));
		}

		void SignalTestSuite::connectTest02()
		{
			TestEnvironment::signalManager.nTasks = 0;
			GeneralSlotHolder slotHolder;
			GeneralSignalEmitter signalEmitter;
			CONNECT_SIGNAL(&signalEmitter, testSignal01, &slotHolder, testSlot01);
			CONNECT_SIGNAL(&signalEmitter, testSignal02, &slotHolder, testSlot02);
			CONNECT_SIGNAL(&signalEmitter, testSignal03, &slotHolder, testSlot03);
			CONNECT_SIGNAL(&signalEmitter, testSignal04, &slotHolder, testSlot04);
			CONNECT_SIGNAL(&signalEmitter, testSignal05, &slotHolder, testSlot05);

			signalEmitter.testSignal01.emit();
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal01.slots.size() == 1));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal02.slots.size() == 1));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal03.slots.size() == 1));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal04.slots.size() == 1));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal05.slots.size() == 1));

			assertTrue(ASSERTION_PARAMETER(TestEnvironment::signalManager.nTasks == 1));
		}

		void SignalTestSuite::connectTest03()
		{
			TestEnvironment::signalManager.nTasks = 0;
			GeneralSlotHolder slotHolder;
			GeneralSignalEmitter signalEmitter;
			CONNECT_SIGNAL(&signalEmitter, testSignal01, &slotHolder, testSlot01);
			CONNECT_SIGNAL(&signalEmitter, testSignal02, &slotHolder, testSlot02);
			CONNECT_SIGNAL(&signalEmitter, testSignal03, &slotHolder, testSlot03);
			CONNECT_SIGNAL(&signalEmitter, testSignal04, &slotHolder, testSlot04);
			CONNECT_SIGNAL(&signalEmitter, testSignal05, &slotHolder, testSlot05);

			signalEmitter.testSignal01.emit();
			signalEmitter.testSignal02.emit(1);
			signalEmitter.testSignal03.emit(1, 1.0f);
			signalEmitter.testSignal04.emit(TestObject());
			signalEmitter.testSignal05.emit(TestObject(), 2);
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal01.slots.size() == 1));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal02.slots.size() == 1));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal03.slots.size() == 1));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal04.slots.size() == 1));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal05.slots.size() == 1));

			assertTrue(ASSERTION_PARAMETER(TestEnvironment::signalManager.nTasks == 5));
		}

		void SignalTestSuite::disconnectTest01()
		{
			TestEnvironment::signalManager.nTasks = 0;
			GeneralSlotHolder slotHolder;
			GeneralSignalEmitter signalEmitter;
			CONNECT_SIGNAL(&signalEmitter, testSignal01, &slotHolder, testSlot01);
			CONNECT_SIGNAL(&signalEmitter, testSignal02, &slotHolder, testSlot02);
			CONNECT_SIGNAL(&signalEmitter, testSignal03, &slotHolder, testSlot03);
			CONNECT_SIGNAL(&signalEmitter, testSignal04, &slotHolder, testSlot04);
			CONNECT_SIGNAL(&signalEmitter, testSignal05, &slotHolder, testSlot05);

			DISCONNECT_SIGNAL(&signalEmitter, testSignal01, &slotHolder, testSlot01);
			DISCONNECT_SIGNAL(&signalEmitter, testSignal02, &slotHolder, testSlot02);
			DISCONNECT_SIGNAL(&signalEmitter, testSignal03, &slotHolder, testSlot03);
			DISCONNECT_SIGNAL(&signalEmitter, testSignal04, &slotHolder, testSlot04);
			DISCONNECT_SIGNAL(&signalEmitter, testSignal05, &slotHolder, testSlot05);


			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal01.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal02.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal03.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal04.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal05.slots.size() == 0));

			assertTrue(ASSERTION_PARAMETER(TestEnvironment::signalManager.nTasks == 0));
		}

		void SignalTestSuite::disconnectTest02()
		{
			TestEnvironment::signalManager.nTasks = 0;
			GeneralSlotHolder slotHolder;
			GeneralSignalEmitter signalEmitter;
			CONNECT_SIGNAL(&signalEmitter, testSignal01, &slotHolder, testSlot01);
			CONNECT_SIGNAL(&signalEmitter, testSignal02, &slotHolder, testSlot02);
			CONNECT_SIGNAL(&signalEmitter, testSignal03, &slotHolder, testSlot03);
			CONNECT_SIGNAL(&signalEmitter, testSignal04, &slotHolder, testSlot04);
			CONNECT_SIGNAL(&signalEmitter, testSignal05, &slotHolder, testSlot05);

			DISCONNECT_SIGNAL(&signalEmitter, testSignal01, &slotHolder, testSlot01);

			signalEmitter.testSignal01.emit();
			signalEmitter.testSignal02.emit(1);
			signalEmitter.testSignal03.emit(1, 1.0f);
			signalEmitter.testSignal04.emit(TestObject());
			signalEmitter.testSignal05.emit(TestObject(), 2);



			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal01.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal02.slots.size() == 1));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal03.slots.size() == 1));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal04.slots.size() == 1));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal05.slots.size() == 1));

			assertTrue(ASSERTION_PARAMETER(TestEnvironment::signalManager.nTasks == 4));
		}

		void SignalTestSuite::disconnectTest03()
		{
			TestEnvironment::signalManager.nTasks = 0;
			GeneralSlotHolder slotHolder;
			GeneralSignalEmitter signalEmitter;
			CONNECT_SIGNAL(&signalEmitter, testSignal01, &slotHolder, testSlot01);
			CONNECT_SIGNAL(&signalEmitter, testSignal02, &slotHolder, testSlot02);
			CONNECT_SIGNAL(&signalEmitter, testSignal03, &slotHolder, testSlot03);
			CONNECT_SIGNAL(&signalEmitter, testSignal04, &slotHolder, testSlot04);
			CONNECT_SIGNAL(&signalEmitter, testSignal05, &slotHolder, testSlot05);

			DISCONNECT_SIGNAL(&signalEmitter, testSignal01, &slotHolder, testSlot01);
			DISCONNECT_SIGNAL(&signalEmitter, testSignal02, &slotHolder, testSlot02);
			DISCONNECT_SIGNAL(&signalEmitter, testSignal03, &slotHolder, testSlot03);
			DISCONNECT_SIGNAL(&signalEmitter, testSignal04, &slotHolder, testSlot04);
			DISCONNECT_SIGNAL(&signalEmitter, testSignal05, &slotHolder, testSlot05);

			signalEmitter.testSignal01.emit();
			signalEmitter.testSignal02.emit(1);
			signalEmitter.testSignal03.emit(1, 1.0f);
			signalEmitter.testSignal04.emit(TestObject());
			signalEmitter.testSignal05.emit(TestObject(), 2);


			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal01.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal02.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal03.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal04.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal05.slots.size() == 0));

			assertTrue(ASSERTION_PARAMETER(TestEnvironment::signalManager.nTasks == 0));
		}

		void SignalTestSuite::destructorTest01()
		{
			TestEnvironment::signalManager.nTasks = 0;
			GeneralSignalEmitter signalEmitter;
			{
				GeneralSlotHolder slotHolder;
				CONNECT_SIGNAL(&signalEmitter, testSignal01, &slotHolder, testSlot01);
				CONNECT_SIGNAL(&signalEmitter, testSignal02, &slotHolder, testSlot02);
				CONNECT_SIGNAL(&signalEmitter, testSignal03, &slotHolder, testSlot03);
				CONNECT_SIGNAL(&signalEmitter, testSignal04, &slotHolder, testSlot04);
				CONNECT_SIGNAL(&signalEmitter, testSignal05, &slotHolder, testSlot05);


				signalEmitter.testSignal01.emit();
				signalEmitter.testSignal02.emit(1);
				signalEmitter.testSignal03.emit(1, 1.0f);
				signalEmitter.testSignal04.emit(TestObject());
				signalEmitter.testSignal05.emit(TestObject(), 2);
			}

			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal01.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal02.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal03.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal04.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal05.slots.size() == 0));

			assertTrue(ASSERTION_PARAMETER(TestEnvironment::signalManager.nTasks == 5));
		}

		void SignalTestSuite::destructorTest02()
		{
			TestEnvironment::signalManager.nTasks = 0;
			GeneralSignalEmitter signalEmitter;
			{
				GeneralSlotHolder slotHolder;
				CONNECT_SIGNAL(&signalEmitter, testSignal01, &slotHolder, testSlot01);
				CONNECT_SIGNAL(&signalEmitter, testSignal02, &slotHolder, testSlot02);
				CONNECT_SIGNAL(&signalEmitter, testSignal03, &slotHolder, testSlot03);
				CONNECT_SIGNAL(&signalEmitter, testSignal04, &slotHolder, testSlot04);
				CONNECT_SIGNAL(&signalEmitter, testSignal05, &slotHolder, testSlot05);
			}
			signalEmitter.testSignal01.emit();
			signalEmitter.testSignal02.emit(1);
			signalEmitter.testSignal03.emit(1, 1.0f);
			signalEmitter.testSignal04.emit(TestObject());
			signalEmitter.testSignal05.emit(TestObject(), 2);

			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal01.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal02.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal03.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal04.slots.size() == 0));
			assertTrue(ASSERTION_PARAMETER(signalEmitter.testSignal05.slots.size() == 0));

			assertTrue(ASSERTION_PARAMETER(TestEnvironment::signalManager.nTasks == 0));
		}
	}
}
