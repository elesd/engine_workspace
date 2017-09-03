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
			path.erase(offset, 1);
			offset = path.find("//", (std::max)(int32_t(offset - 1), 0));
		}
	}

	std::vector<std::string> splitPath(const std::string &path)
	{
		std::vector<std::string> result;
		
		size_t offset = path.find('/', 0);
		result.push_back(path.substr(0, offset));
		
		while(offset != std::string::npos)
		{
			size_t newOffset = path.find('/', offset + 1);
			if(newOffset != std::string::npos)
			{
				result.push_back(path.substr(offset + 1, newOffset - offset));
			}
			else
			{
				result.push_back(path.substr(offset + 1));
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
		FilePathPrivate(const std::string &path) :path(path) {}
	};

	FilePath::FilePath()
		: _members(new FilePathPrivate(""))
	{

	}

	FilePath::FilePath(const std::string &path)
		: _members(new FilePathPrivate(path))
	{
		normalize();
	}

	FilePath::FilePath(const FilePath &o)
		: _members(new FilePathPrivate(o._members->path))
	{

	}

	FilePath::FilePath(FilePath &&o)
		:_members(o._members)
	{
		o._members = nullptr;
	}

	FilePath::~FilePath()
	{
		delete _members;
	}

	FilePath &FilePath::operator=(const FilePath &o)
	{
		delete _members;
		_members = new FilePathPrivate(o._members->path);
		return *this;
	}

	FilePath &FilePath::operator=(FilePath &&o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
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
		if(pos == std::string::npos)
		{
			return ".";
		}
		if(pos == 0)
		{
			return "/";
		}
		
		return _members->path.substr(0, pos);
	}

}