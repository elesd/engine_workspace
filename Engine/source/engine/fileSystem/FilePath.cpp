#include <stdafx.h>

#include <engine/fileSystem/FilePath.h>

namespace
{
	void removeBackSlashes(std::string &path)
	{
		size_t offset = path.find('\\', 0);
		while(offset != std::string::npos)
		{
			path[offset] = '/';
			offset = path.find('\\', offset);
		}
	}

	void removeRedundancy(std::string &path)
	{
		size_t offset = path.find("//", 0);
		while(offset != std::string::npos)
		{
			path.erase(offset);
			offset = path.find("//", std::max(int32_t(offset - 1), 0));
		}
	}

	std::vector<std::string> splitPath(const std::string &path)
	{
		std::vector<std::string> result;
		
		size_t offset = path.find('/', 0);
		result.push_back(path.substr(0, offset));
		
		while(offset != std::string::npos)
		{
			size_t newOffset = path.find('/', offset);
			if(newOffset != std::string::npos)
			{
				result.push_back(path.substr(offset, newOffset - offset));
			}
			else
			{
				result.push_back(path.substr(offset));
			}
			offset = newOffset;
		}
		return result;
	}
}

namespace engine
{
	struct FilePathPrivate
	{
		std::string path;
	};

	FilePath::FilePath(const std::string &path)
		: _members(new FilePathPrivate({path}))
	{
		normalize();
	}

	FilePath::~FilePath()
	{
		delete _members;
	}

	void FilePath::normalize()
	{
		removeBackSlashes(_members->path);
		removeRedundancy(_members->path);
	}

	const std::string &FilePath::str() const
	{
		return _members->path;
	}

	void FilePath::append(const std::string &path)
	{
		_members->path += "/" + path;
		normalize();
	}

	std::string FilePath::getFileName() const
	{
		std::vector<std::string> parts = splitPath(_members->path);
		return parts.empty() ? "" : parts.back();
	}

	std::string FilePath::getFileExtension() const
	{
		std::string fileName = getFileName();
		size_t pos = fileName.find_last_of('.');
		if(pos == std::string::npos || pos == fileName.size() - 1)
		{
			return "";
		}

		std::string extension = fileName.substr(pos + 1);
		return extension;
	}

	std::string FilePath::getDirName() const
	{
		size_t pos = _members->path.find_last_of('/');
		if(pos == std::string::npos || pos == 0)
		{
			return ".";
		}
		
		return _members->path.substr(0, pos - 1);
	}

}