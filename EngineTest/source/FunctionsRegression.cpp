#include "stdafx.h"

#include "FunctionsRegression.h"

#include "functional/FunctionsTestSuit.h"

namespace tests
{
	FunctionsRegression::FunctionsRegression()
		:BaseRegression("Functions")
	{
		std::unique_ptr<engine::test::TestSuit> functionalTest(new tests::FunctionsTestSuit());
		addTestSuit(std::move(functionalTest));
	}
}
