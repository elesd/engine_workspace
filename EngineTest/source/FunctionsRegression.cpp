#include "stdafx.h"

#include "FunctionsRegression.h"

#include "functional/FunctionsTestSuite.h"

namespace tests
{
	FunctionsRegression::FunctionsRegression()
		:BaseRegression("Functions")
	{
		std::unique_ptr<engine::test::TestSuite> functionalTest(new tests::functions::FunctionsTestSuite());
		addTestSuite(std::move(functionalTest));
	}
}
