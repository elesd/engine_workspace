#include <stdafx.h>
#include <engine/fileSystem/SimpleFile.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/exceptions/RuntimeErrors.h>

#include <engine/fileSystem/FilePath.h>

namespace
{
	class PositionGuard
	{
	public:
		PositionGuard(std::fstream &fstream)
			:fstream(fstream), originalPos(fstream.tellg())
		{		}
		~PositionGuard()
		{
			fstream.seekg(originalPos);
		}

	private:
		std::fstream &fstream;
        std::streamoff originalPos;
	};

	std::unique_ptr<std::fstream> openFile(const engine::FilePath &filePath, engine::FileMode mode, engine::FileOpenMode openMode, bool append)
	{
		std::unique_ptr<std::fstream> result;
		std::ios_base::openmode m = static_cast<std::ios_base::openmode>(0);
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
            default:
                break;
		}
		if(append)
		{
			m |= std::ios_base::app;
		}
		return std::make_unique<std::fstream>(filePath.str().c_str(), m);
	}
	void clearFailBit(std::fstream *fstream)
	{
		std::ios_base::iostate state = std::ios_base::goodbit;
		if(fstream->bad())
		{
			state |= std::ios_base::badbit;
		}
		if(fstream->eof())
		{
			state |= std::ios_base::eofbit;
		}
		// Don't check fail
		fstream->clear(state);
	}
}

namespace engine
{
	struct SimpleFilePrivate
	{
		FilePath path;
		FileMode mode;
		FileOpenMode openMode;
		bool append;
		std::unique_ptr<std::fstream> fstream;
		SimpleFilePrivate(const FilePath &path, FileMode mode, FileOpenMode openMode, bool append)
			:path(path), mode(mode), openMode(openMode), append(append)
		{ }
	};

	SimpleFile::SimpleFile(const FilePath &path, FileMode mode, FileOpenMode openMode, bool append)
		:_members(new SimpleFilePrivate(path, mode, openMode, append))
	{
		_members->fstream = openFile(path, mode, openMode, append);
	}

	SimpleFile::SimpleFile(SimpleFile &&o)
		:_members(o._members)
	{
		o._members = nullptr;
	}

	SimpleFile::~SimpleFile()
	{
		delete _members;
	}

	SimpleFile &SimpleFile::operator=(SimpleFile &&o)
	{
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	std::vector<char> SimpleFile::readAll()
	{
		if(isOk() == false)
		{
			throw IOError("readAll failed with file because of previous errors", _members->path.str());
		}
		size_t size = getSize();
		std::vector<char> buff(1);
		if(size == 0)
		{
			// read one byte to set the eof bit 
			_members->fstream->read(buff.data(), 1);
			buff.resize(0);
		}
		else
		{
			buff.resize(size);
			_members->fstream->read(buff.data(), size);
		}

		if(_members->fstream->bad())
		{
			throw IOError("Read all failed with file", _members->path.str());
		}
		if(_members->fstream->fail() && atEof())
		{
			clearFailBit(_members->fstream.get());
		}
		return buff;
	}

	std::string SimpleFile::readLine()
	{
		if(isOk() == false)
		{
			throw IOError("Read line failed with file because of previous errors", _members->path.str());
		}

		if(atEof())
			return "";
		std::string line = "";
		static const size_t bufferSize = 1024;
		std::vector<char> buff(bufferSize);
		_members->fstream->getline(buff.data(), bufferSize);
		line = buff.data();
		// If no line ending was found
		while(_members->fstream->fail())
		{
			// if it because of eof
			if(atEof())
			{
				return line;
			}
			if(_members->fstream->bad())
			{
				throw IOError("Read line failed with file", _members->path.str());
			}
			clearFailBit(_members->fstream.get());
			_members->fstream->getline(buff.data(), bufferSize);
			line += buff.data();
		}
		if(_members->fstream->bad())
		{
			throw IOError("Read line failed with file", _members->path.str());
		}
		else if(_members->fstream->fail() && atEof())
		{
			// fail can be normal at end of the file.
			clearFailBit(_members->fstream.get());
		}
		return line;
	}

	void SimpleFile::writeLine(const std::string& line)
	{
		if(isOk() == false)
		{
			throw IOError("write line failed with file because of previous errors", _members->path.str());
		}
		(*_members->fstream) << line << std::endl;
	}

	std::vector<std::string> SimpleFile::readLines()
	{
		if(isOk() == false)
		{
			throw IOError("readLines failed with file because of previous errors", _members->path.str());
		}		std::vector<std::string> result;
		while(!_members->fstream->eof())
		{
			result.push_back(readLine());
		}
		return result;
	}

	bool SimpleFile::atEof() const
	{
		return _members->fstream->eof();
	}

	bool SimpleFile::isOk() const
	{
		return atEof() || _members->fstream->good();
	}

	size_t SimpleFile::getSize() const
	{
		if(isOk() == false)
		{
			throw IOError("getSize failed with file because of previous errors", _members->path.str());
		}
		PositionGuard guard(*_members->fstream);
		_members->fstream->seekg(0, std::ios_base::end);
		size_t size = size_t(_members->fstream->tellg());
		return size;
	}

}
