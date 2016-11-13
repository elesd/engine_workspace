#include <stdafx.h>

#include "engine/test/TestAssertException.h"

namespace engine
{
	namespace test
	{
		struct TestAssertExceptionPrivate
		{
			std::string message;
			std::string file;
			uint32_t line;
		};
		TestAssertException::TestAssertException(const std::string &message, const std::string &file, const uint32_t line)
		{
			_member = new TestAssertExceptionPrivate{message, file, line};
		}

		TestAssertException::~TestAssertException()
		{
			delete _member;
		}

		TestAssertException::TestAssertException(const TestAssertException &o)
		{
			_member = new TestAssertExceptionPrivate(*o._member);
		}

		TestAssertException::TestAssertException(TestAssertException &&o)
		{
			_member = o._member;
			o._member = nullptr;
		}

		const std::string &TestAssertException::getMessage() const
		{
			return _member->message;
		}

		const std::string &TestAssertException::getFile() const
		{
			return _member->file;
		}

		uint32_t TestAssertException::getLine() const
		{
			return _member->line;
		}
	}
}
