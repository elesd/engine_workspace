#include "stdafx.h"

#include "FunctionsRegression.h"

#include "functional/FunctionsTestSuite.h"

namespace tests
{
	FunctionsRegression::FunctionsRegression()
		:BaseRegression("Functions")
	{
		std::unique_ptr<engine::test::TestSuite> functionalTest(new tests::FunctionsTestSuite());
		addTestSuite(std::move(functionalTest));
	}
}
