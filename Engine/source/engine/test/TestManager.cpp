#include "stdafx.h"

#include "engine/test/TestManager.h"
//////////////////////////////////////
#include "engine/test/BaseRegression.h"
#include "engine/test/TestSuite.h"

namespace engine
{
	namespace test
	{
		struct TestManagerPrivate
		{
			std::list<BaseRegression> regressions;
			std::ostream &outStream = std::cout;
		};
		
		TestManager::TestManager()
			: _members(new TestManagerPrivate())
		{	}

		TestManager::TestManager(TestManager &&o)
			:_members(o._members)
		{
			o._members = nullptr;
		}

		TestManager &TestManager::operator=(TestManager &&o)
		{
			_members = o._members;
			o._members = nullptr;
			return *this;
		}

		TestManager::~TestManager()
		{
			delete _members;
		}

		void TestManager::addRegression(BaseRegression &&regression)
		{
			_members->regressions.push_back(std::move(regression));
		}

		void TestManager::setOutput(std::ostream &os)
		{
			for(BaseRegression &regression : _members->regressions)
			{
				regression.setStream(&os);
			}
			
		}

		void TestManager::run()
		{
			uint32_t nTestCases = 0;
			uint32_t nNok = 0;
			for(BaseRegression &regression : _members->regressions)
			{
				regression.run();
				nTestCases += regression.getNumOfExecutedTC();
				nNok += regression.getNumOfNokTC();
			}
			float percentage = 1.0f - float(nNok) / nTestCases;
			percentage *= 100.0f;
			_members->outStream << std::string(TestSuite::lineLength, '#') << std::endl;
			_members->outStream << "Summary:" << std::endl;
			for(BaseRegression &regression : _members->regressions)
			{
				uint32_t localTests = regression.getNumOfExecutedTC();
				uint32_t localNoks = regression.getNumOfNokTC();
				float localPercentate = 1.0f - float(localNoks) / localTests;
				localPercentate *= 100.0f;
				_members->outStream << "  - " << regression.getName() << ": " << localPercentate << "%  [" << localTests << " / " << (localTests - localNoks) << " ]" << std::endl;
			}
			_members->outStream << std::string(TestSuite::lineLength, '-') << std::endl;
			_members->outStream << "Overall result: " << percentage << "%  [" << nTestCases << " / " << (nTestCases - nNok) << " ]" << std::endl;
			_members->outStream << std::string(TestSuite::lineLength, '#') << std::endl;
		}
	}
}