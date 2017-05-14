#include <stdafx.h>

#include <engine/test/TestSuit.h>


#include <engine/test/ITestCase.h>
#include <engine/test/TestAssertException.h>
#include <engine/test/GameAssertException.h>


namespace engine
{
	namespace test
	{
		struct TestSuitPrivate
		{
			std::list<ITestCase*> testCases;
			std::string name;
			std::ostream *out = nullptr;
			uint32_t nNok = 0;
		};

		const size_t TestSuit::lineLength = 50;

		TestSuit::TestSuit(const std::string &name)
		{
			_members = new TestSuitPrivate();
			_members->out = &std::cout;
			_members->name = name;
		}

		TestSuit::TestSuit(const TestSuit &o)
		{
			_members = new TestSuitPrivate(*o._members);
		}
		TestSuit::TestSuit(TestSuit &&o)
		{
			_members = o._members;
			o._members = nullptr;
		}

		TestSuit::~TestSuit()
		{
			delete _members;
		}

		void TestSuit::setStream(std::ostream *os)
		{
			_members->out = os;
		}


		void TestSuit::run() const
		{
			_members->nNok = 0;
			std::ostream &os = *_members->out;
			os << "Suite: " << _members->name << std::endl;
			for(ITestCase *tc : _members->testCases)
			{
				try
				{
					os << std::setfill('_') << std::setw(TestSuit::lineLength);

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

		void TestSuit::addTestCase(ITestCase *tc)
		{
			_members->testCases.emplace_back(tc);
		}

		void TestSuit::assertTrue(bool value, const std::string &message, const std::string &file, const uint32_t line)
		{
			if(!value)
			{
				throw TestAssertException(message, file, line);
			}
		}

		uint32_t TestSuit::getNumOfNok() const
		{
			return _members->nNok;
		}

		uint32_t TestSuit::getNumOfTestCases() const
		{
			return uint32_t(_members->testCases.size());
		}

		float TestSuit::getPercentageResult() const
		{
			float percentage = 1.0f - (float(_members->nNok) / _members->testCases.size());
			return percentage;
		}
	}
}
