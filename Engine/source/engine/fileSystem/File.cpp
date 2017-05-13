#include <stdafx.h>
#include <engine/fileSystem/File.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/fileSystem/FilePath.h>

namespace
{
	std::unique_ptr<std::fstream> openFile(const engine::FilePath &filePath, engine::FileMode mode, engine::FileOpenMode openMode, bool append)
	{
		std::unique_ptr<std::fstream> result;
		std::ios_base::openmode m;
		switch(mode)
		{
			case engine::FileMode::Read:
				m |= std::ios_base::in;
				break;
			case engine::FileMode::Write:
				m |= std::ios_base::out;
				break;
			case engine::FileMode::ReadWrite:
				m |= std::ios_base::out;
				m |= std::ios_base::in;
				break;
		}
		switch(openMode)
		{
			case engine::FileOpenMode::Binary:
				m |= std::ios_base::binary;
				break;
		}
		if(append)
		{
			m |= std::ios_base::app;
		}
		return std::make_unique<std::fstream>(filePath.str().c_str(), m);
	}
}

namespace engine
{
	struct FilePrivate
	{
		FilePath path;
		FileMode mode;
		FileOpenMode openMode;
		bool append;
		std::unique_ptr<std::fstream> fstream;
		FilePrivate(const FilePath &path, FileMode mode, FileOpenMode openMode, bool append)
			:path(path), mode(mode), openMode(openMode), append(append)
		{ }
	};

	File::File(const FilePath &path, FileMode mode, FileOpenMode openMode, bool append)
		:_members(new FilePrivate(path, mode, openMode, append))
	{ 
		_members->fstream = openFile(path, mode, openMode, append);
	}

	File::~File()
	{
		delete _members;
	}

}