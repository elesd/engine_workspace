#pragma once

namespace engine
{
	namespace test
	{
		class GameAssertException
		{
		public:
			enum class Type
			{
				Hard,
				Normal
			};
		public:
			GameAssertException(Type type, const std::string &message, const std::string &file, const uint32_t line);
			~GameAssertException();

			GameAssertException(const GameAssertException &o);
			GameAssertException(GameAssertException &&o);

			Type getType() const;
			const std::string &getMessage() const;
			const std::string &getFile() const;
			uint32_t getLine() const;
		private:
			struct GameAssertExceptionPrivate *_member = nullptr;

		};
	}
}