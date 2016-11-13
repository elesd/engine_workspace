#include "stdafx.h"

#include "engine/test/TestSuite.h"


#include "engine/test/ITestCase.h"
#include "engine/test/TestAssertException.h"
#include "engine/test/GameAssertException.h"


namespace engine
{
	namespace test
	{
		struct TestSuitePrivate
		{
			std::list<ITestCase*> testCases;
			std::string name;
			std::ostream *out = nullptr;
			uint32_t nNok = 0;
		};

		const size_t TestSuite::lineLength = 50;

		TestSuite::TestSuite(const std::string &name)
		{
			_members = new TestSuitePrivate();
			_members->out = &std::cout;
			_members->name = name;
		}

		TestSuite::TestSuite(const TestSuite &o)
		{
			_members = new TestSuitePrivate(*o._members);
		}
		TestSuite::TestSuite(TestSuite &&o)
		{
			_members = o._members;
			o._members = nullptr;
		}

		TestSuite::~TestSuite()
		{
			delete _members;
		}

		void TestSuite::setStream(std::ostream *os)
		{
			_members->out = os;
		}


		void TestSuite::run() const
		{
			_members->nNok = 0;
			std::ostream &os = *_members->out;
			os << "Suite: " << _members->name << std::endl;
			for(ITestCase *tc : _members->testCases)
			{
				try
				{
					os << std::setfill('_') << std::setw(TestSuite::lineLength);

					os << tc->getName().c_str() << ": " << std::flush;
					tc->execute();
					os << "[ OK ]" << std::endl;
					os << std::setfill(' ') << std::setw(0);
				}
				catch(GameAssertException &ex)
				{
					std::ostream &os = *_members->out;
					os << "[ NOK ]" << std::endl;
					os << std::setfill(' ') << std::setw(0);
					os << "  File:    " << ex.getFile().c_str() << std::endl;
					os << "  Line:    " << ex.getLine() << std::endl;
					os << "  Details: " << ex.getMessage().c_str() << std::endl;
					os << "  Type: " << ((ex.getType() == GameAssertException::Type::Hard) ? "Hard" : "Normal") << std::endl;
					_members->nNok++;
				}
				catch(TestAssertException &ex)
				{
					std::ostream &os = *_members->out;
					os << "[ NOK ]" << std::endl;
					os << std::setfill(' ') << std::setw(0);
					os << "  File:    " << ex.getFile().c_str() << std::endl;
					os << "  Line:    " << ex.getLine() << std::endl;
					os << "  Details: " << ex.getMessage().c_str() << std::endl;
					_members->nNok++;
				}
			}
			float percentage = getPercentageResult();
			percentage *= 100.0f;
			os << _members->name << "-Result: " << percentage << "% [" << _members->testCases.size() << " / " << (_members->testCases.size() - _members->nNok) << "]" << std::endl;
		}

		void TestSuite::addTestCase(ITestCase *tc)
		{
			_members->testCases.emplace_back(tc);
		}

		void TestSuite::assertTrue(bool value, const std::string &message, const std::string &file, const uint32_t line)
		{
			if(!value)
			{
				throw TestAssertException(message, file, line);
			}
		}

		uint32_t TestSuite::getNumOfNok() const
		{
			return _members->nNok;
		}

		uint32_t TestSuite::getNumOfTestCases() const
		{
			return uint32_t(_members->testCases.size());
		}

		float TestSuite::getPercentageResult() const
		{
			float percentage = 1.0f - (float(_members->nNok) / _members->testCases.size());
			return percentage;
		}
	}
}
