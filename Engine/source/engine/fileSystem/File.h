#pragma once

#include "engine/constraints/NonCopyable.h"
#include "engine/constraints/PIMPLMoveable.h"

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

	class File : NonCopyable,
		public PIMPLMoveable<File>
	{
		friend class FileSystem;
	private:
		File(const FilePath &path, FileMode mode, FileOpenMode openMode, bool append);
	public:
		~File();

		std::string readAll();
		std::vector<char> readAllData();

		size_t getSize() const;
	private:
		struct FilePrivate *_members = nullptr;
	};
}