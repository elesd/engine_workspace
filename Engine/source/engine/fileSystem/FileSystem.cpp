#include <stdafx.h>
#include <engine/fileSystem/FileSystem.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/fileSystem/SimpleFile.h>

namespace engine
{
	struct FileSystemPrivate
	{
		FileSystemSettings settings;
		FileSystemPrivate(const FileSystemSettings &settings) : settings(settings) {}
	};

	FileSystem::FileSystem(const FileSystemSettings &settings)
		:_members(new FileSystemPrivate(settings))
	{

	}

	FileSystem::~FileSystem()
	{
		delete _members;
	}

	SimpleFile FileSystem::OpenFileSimple(const FilePath &path, FileMode mode, FileOpenMode openMode, bool append) const
	{
		SimpleFile file(path, mode, openMode, append);
		return std::move(file);
	}

	bool FileSystem::IsFileExists(const FilePath &path) const
	{
		SimpleFile file(path, FileMode::Read, FileOpenMode::Binary, false);
		return file.isOk();
	}
}