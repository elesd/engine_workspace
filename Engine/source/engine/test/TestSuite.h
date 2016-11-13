#pragma once

namespace engine
{
	namespace test
	{
		class ITestCase;

		class TestSuite
		{
		public:
			static const size_t lineLength;
		protected:
			TestSuite(const std::string &name);
			TestSuite(const TestSuite &o);
			TestSuite(TestSuite &&o);

		public:

            virtual ~TestSuite();
			void addTestCase(ITestCase *testCase);
			void run() const;
			void setStream(std::ostream *os);
			uint32_t getNumOfNok() const;
			uint32_t getNumOfTestCases() const;
			float getPercentageResult() const;
		protected:
			void assertTrue(bool value, const std::string &message, const std::string &file, const uint32_t line);
		private:
			struct TestSuitePrivate *_members = nullptr;
		};
	}
}

#define ASSERTION_PARAMETER(condition) condition, #condition, __FILE__, __LINE__
