#pragma once

#include "engine/constraints/NonCopyable.h"

namespace engine
{
	class FilePath;

	enum class FileMode
	{
		Read,
		Write,
		ReadWrite
	};

	enum class FileOpenMode
	{
		Text,
		Binary
	};

	class SimpleFile : NonCopyable
	{
		friend class FileSystem;
	private:
		SimpleFile(const FilePath &path, FileMode mode, FileOpenMode openMode, bool append);
	public:
		SimpleFile(SimpleFile &&o);
		~SimpleFile();

		SimpleFile &operator=(SimpleFile &&o);
		operator bool() const { return isOk(); }

		std::string readLine();
		void writeLine(const std::string& line);
		void flush();
		std::vector<std::string> readLines();
		std::vector<char> readAll();

		size_t getSize() const;

		bool isOk() const;
		bool atEof() const;
	private:
		struct SimpleFilePrivate *_members = nullptr;
	};
}