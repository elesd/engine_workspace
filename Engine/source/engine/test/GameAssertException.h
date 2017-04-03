#pragma once

namespace engine
{
	namespace test
	{
		/**
		* Exception for ASSERT replacement during test engine run.
		*/
		class GameAssertException
		{
		public:
			/**Type for assertions*/
			enum class Type
			{
				Hard,
				Normal
			};
		public:
			/**
			* Create an exception instead of assert.
			* @param type: Type of the assert
			* @param message: the assertion which is failed in a string format.
			* @param file: The file where the assertion is located
			* @param line: The line where the assertion is located
			*/
			GameAssertException(Type type, const std::string &message, const std::string &file, const uint32_t line);
			/**PIMPL*/
			~GameAssertException();

			/**Copyable*/
			GameAssertException(const GameAssertException &o);
			/**Moveable*/
			GameAssertException(GameAssertException &&o);

			/**@return Returns the type of the assert*/
			Type getType() const;
			/**@return Returns The assertion which is failed*/
			const std::string &getMessage() const;
			/**@return Returns the file where the assertion located*/
			const std::string &getFile() const;
			/**@return Returns the line where the assertion located*/
			uint32_t getLine() const;
		private:
			/**PIMPL*/
			struct GameAssertExceptionPrivate *_member = nullptr;

		};
	}
}