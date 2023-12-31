#include <stdafx.h>

#include <engine/test/BaseRegression.h>

#include <engine/test/TestSuit.h>

namespace engine
{
	namespace test
	{
		struct BaseRegressionPrivate
		{
			std::list<TestSuit*> TestSuits;
			std::ostream *out = nullptr;
			std::string name;
			uint32_t nExecutedTC = 0;
			uint32_t nNokTC = 0;
		};

		BaseRegression::BaseRegression(const std::string &name)
		{
			_members = new BaseRegressionPrivate();
			_members->out = &std::cout;
			_members->name = name;
		}

		BaseRegression::~BaseRegression()
		{
			if(_members)
			{
				for(TestSuit *suite : _members->TestSuits)
				{
					delete suite;
				}
				delete _members;
			}
		}

		BaseRegression::BaseRegression(BaseRegression &&o)
		{
			_members = o._members;
			o._members = nullptr;
		}

		const std::string &BaseRegression::getName() const
		{
			return _members->name;
		}

		void BaseRegression::addTestSuit(std::unique_ptr<TestSuit> &&TestSuit)
		{
			TestSuit->setStream(_members->out);
			_members->TestSuits.emplace_back(TestSuit.release());
		}

		void BaseRegression::setStream(std::ostream *os)
		{
			_members->out = os;
			for(TestSuit *TestSuits : _members->TestSuits)
			{
				TestSuits->setStream(os);
			}
		}

		void BaseRegression::run() const
		{
			(*_members->out) << std::string(TestSuit::lineLength, '#') << std::endl;
			(*_members->out) << "Regression: " << _members->name << std::endl;
			_members->nExecutedTC = 0;
			_members->nNokTC = 0;
			for(TestSuit *TestSuit : _members->TestSuits)
			{
				TestSuit->run();
				_members->nExecutedTC += TestSuit->getNumOfTestCases();
				_members->nNokTC += TestSuit->getNumOfNok();
			}
			float percentage = 1.0f - float(_members->nNokTC) / _members->nExecutedTC;
			percentage *= 100.0f;
			(*_members->out) << std::string(TestSuit::lineLength, '-') << std::endl;
			(*_members->out) << _members->name << "-Regression Result: " << percentage << "%  [" << _members->nExecutedTC << " / " << (_members->nExecutedTC - _members->nNokTC) << " ]" << std::endl;
			(*_members->out) << std::string(TestSuit::lineLength, '#') << std::endl;

		}

		uint32_t BaseRegression::getNumOfExecutedTC() const
		{
			return _members->nExecutedTC;
		}

		uint32_t BaseRegression::getNumOfNokTC() const
		{
			return _members->nNokTC;
		}
	}
}