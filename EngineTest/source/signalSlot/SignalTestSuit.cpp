#include "stdafx.h"
#include "signalSlot/SignalTestSuit.h"

#include "engine/signalSlot/Signal.h"
#include "engine/signalSlot/SlotHolder.h"
#include "engine/signalSlot/ISignalManager.h"
#include "engine/signalSlot/SignalTask.h"


namespace
{
	struct CounterSignalManager : public engine::ISignalManager
	{
		void addTask(std::unique_ptr<engine::ISignalTask> task) override { nTasks++; };
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

	struct GeneralSlotHolder : engine::SlotHolder
	{


		engine::ISignalManager *getSignalManager() const override { return &TestEnvironment::signalManager; }
		void testSlot01() {}
		void testSlot02(int i){}
		void testSlot03(int i, float j){}
		void testSlot04(TestObject o){}
		void testSlot05(TestObject o, int j){}
	};

	struct GeneralSignalEmitter
	{
		engine::Signal<> testSignal01;
		engine::Signal<int> testSignal02;
		engine::Signal<int, float> testSignal03;
		engine::Signal<TestObject> testSignal04;
		engine::Signal<TestObject, int> testSignal05;
	};
}

namespace tests
{
	SignalTestSuit::SignalTestSuit()
		: engine::test::TestSuit("SignalTest")
	{}

	void SignalTestSuit::connectTest01()
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

	void SignalTestSuit::connectTest02()
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

	void SignalTestSuit::connectTest03()
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

	void SignalTestSuit::disconnectTest01()
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

	void SignalTestSuit::disconnectTest02()
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

	void SignalTestSuit::disconnectTest03()
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

	void SignalTestSuit::destructorTest01()
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

	void SignalTestSuit::destructorTest02()
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
