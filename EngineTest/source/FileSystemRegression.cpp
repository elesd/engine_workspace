#include "stdafx.h"

#include "FileSystemRegression.h"

#include "fileSystem/FilePathTestSuit.h"
#include "fileSystem/SimpleFileTestSuit.h"

namespace tests
{
	FileSystemRegression::FileSystemRegression()
		:BaseRegression("FileSystemRegression")
	{
		{
			std::unique_ptr<engine::test::TestSuit> test(new tests::FilePathTestSuit());
			addTestSuit(std::move(test));
		}
		{
			std::unique_ptr<engine::test::TestSuit> test(new tests::SimpleFileTestSuit());
			addTestSuit(std::move(test));
		}
	}
}
