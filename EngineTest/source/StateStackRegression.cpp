#include "stdafx.h"

#include "StateStackRegression.h"

#include "stateStack/StateBaseTestSuit.h"
#include "stateStack/StateStackTestSuit.h"

namespace tests
{
	StateStackRegression::StateStackRegression()
		:BaseRegression("StateStack")
	{
		std::unique_ptr<engine::test::TestSuit> stateBaseTest(new tests::StateBaseTestSuit());
		addTestSuit(std::move(stateBaseTest));
		std::unique_ptr<engine::test::TestSuit> stateStackTest(new tests::StateStackTestSuit());
		addTestSuit(std::move(stateStackTest));
	}
}
