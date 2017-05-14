#include "stdafx.h"

#include "SignalSlotRegression.h"

#include "signalSlot/SignalTestSuit.h"
#include "signalSlot/SignalCallerTestSuit.h"
#include "signalSlot/SignalManagerTestSuit.h"
#include "signalSlot/SignalTaksTestSuit.h"

namespace tests
{
	SignalSlotRegression::SignalSlotRegression()
		:BaseRegression("SignalSlot")
	{
		std::unique_ptr<engine::test::TestSuit> signalTest(new tests::SignalTestSuit());
		addTestSuit(std::move(signalTest));
		std::unique_ptr<engine::test::TestSuit> signalTest2(new tests::SignalCallerTestSuit());
		addTestSuit(std::move(signalTest2));
		std::unique_ptr<engine::test::TestSuit> signalTest3(new tests::SignalManagerTest());
		addTestSuit(std::move(signalTest3));
		std::unique_ptr<engine::test::TestSuit> signalTest4(new tests::SignalTaskTest());
		addTestSuit(std::move(signalTest4));
	}
}
