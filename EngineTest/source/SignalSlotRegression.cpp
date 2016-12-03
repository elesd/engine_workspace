#include "stdafx.h"

#include "SignalSlotRegression.h"

#include "signalSlot/SignalTest.h"
#include "signalSlot/SignalCallerTestSuite.h"
#include "signalSlot/SignalManagerTest.h"
#include "signalSlot/SignalTaksTest.h"

namespace tests
{
	SignalSlotRegression::SignalSlotRegression()
		:BaseRegression("SignalSlot")
	{
		std::unique_ptr<engine::test::TestSuite> signalTest(new tests::SignalTestSuite());
		addTestSuite(std::move(signalTest));
		std::unique_ptr<engine::test::TestSuite> signalTest2(new tests::SignalCallerTestSuite());
		addTestSuite(std::move(signalTest2));
		std::unique_ptr<engine::test::TestSuite> signalTest3(new tests::SignalManagerTest());
		addTestSuite(std::move(signalTest3));
		std::unique_ptr<engine::test::TestSuite> signalTest4(new tests::SignalTaskTest());
		addTestSuite(std::move(signalTest4));
	}
}
