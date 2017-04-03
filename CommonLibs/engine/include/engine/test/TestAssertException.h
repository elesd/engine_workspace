#pragma once

namespace engine
{
	namespace test
	{
		class TestAssertException
		{
		public:
			TestAssertException(const std::string &message, const std::string &file, const uint32_t line);
			~TestAssertException();	

			TestAssertException(const TestAssertException &o);
			TestAssertException(TestAssertException &&o);

			const std::string &getMessage() const;
			const std::string &getFile() const;
			uint32_t getLine() const;
		private:
			struct TestAssertExceptionPrivate *_member = nullptr;
		};
	}
}