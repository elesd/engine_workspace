#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class SimpleFile;
	class FilePath;
	enum class FileMode;
	enum class FileOpenMode;

	struct FileSystemSettings
	{
		std::string workingDirectory;
	};
	

	class FileSystem : NonCopyable,
		NonMoveable
	{
		friend class FileSystemBuilder;
	private:
		FileSystem(const FileSystemSettings &settings);
	public:
		~FileSystem();

		SimpleFile OpenFile(const FilePath &path, FileMode mode, FileOpenMode openMode) const;
		bool IsFileExists() const;
	};
}