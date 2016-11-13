#include "stdafx.h"

#include "engine/test/GameAssertException.h"

namespace engine
{
	namespace test
	{
		struct GameAssertExceptionPrivate
		{
			GameAssertException::Type type;
			std::string assertion;
			std::string file;
			uint32_t line;
		};
		GameAssertException::GameAssertException(Type type, const std::string &assertion, const std::string &file, const uint32_t line)
		{
			_member = new GameAssertExceptionPrivate{type, assertion, file, line};
		}

		GameAssertException::~GameAssertException()
		{
			delete _member;
		}

		GameAssertException::GameAssertException(const GameAssertException &o)
		{
			_member = new GameAssertExceptionPrivate(*o._member);
		}

		GameAssertException::GameAssertException(GameAssertException &&o)
		{
			_member = o._member;
			o._member = nullptr;
		}

		GameAssertException::Type GameAssertException::getType() const
		{
			return _member->type;
		}

		const std::string &GameAssertException::getMessage() const
		{
			return _member->assertion;
		}

		const std::string &GameAssertException::getFile() const
		{
			return _member->file;
		}

		uint32_t GameAssertException::getLine() const
		{
			return _member->line;
		}
	}
}