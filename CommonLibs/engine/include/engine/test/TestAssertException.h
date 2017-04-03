#pragma once

namespace engine
{
	namespace test
	{
		/**
		* Exception for assertion for test cases run.
		*/
		class TestAssertException
		{
		public:
			/**
			* Create an exception for test cases.
			* @param message: the assertion which is failed in a string format.
			* @param file: The file where the assertion is located
			* @param line: The line where the assertion is located
			*/
			TestAssertException(const std::string &message, const std::string &file, const uint32_t line);
			/**PIMPL*/
			~TestAssertException();	

			/**Copyable*/
			TestAssertException(const TestAssertException &o);
			/**Moveable*/
			TestAssertException(TestAssertException &&o);

			/**@return Returns the assertion which is failed.*/
			const std::string &getMessage() const;
			/**@return Returns the file where the assertion located*/
			const std::string &getFile() const;
			/**@return Returns the line where the assertion located*/
			uint32_t getLine() const;
		private:
			/**PIMPL*/
			struct TestAssertExceptionPrivate *_member = nullptr;
		};
	}
}