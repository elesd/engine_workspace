#include "stdafx.h"

#include "StateStackRegression.h"

#include "stateStack/StateBaseTestSuite.h"
#include "stateStack/StateStackTestSuite.h"

namespace tests
{
	StateStackRegression::StateStackRegression()
		:BaseRegression("StateStack")
	{
		std::unique_ptr<engine::test::TestSuite> stateBaseTest(new tests::stateStack::StateBaseTestSuite());
		addTestSuite(std::move(stateBaseTest));
		std::unique_ptr<engine::test::TestSuite> stateStackTest(new tests::stateStack::StateStackTestSuite());
		addTestSuite(std::move(stateStackTest));
	}
}
