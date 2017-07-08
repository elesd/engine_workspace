#pragma once

namespace engine
{
	class FilePath
	{
	public:
		explicit FilePath(const std::string &path);
		FilePath(const FilePath &o);
		FilePath(FilePath &&o);
		~FilePath();
		FilePath &operator=(const FilePath &o);
		FilePath &operator=(FilePath &&o);

		void normalize();

		const std::string &str() const;
		void append(const std::string &path);
		std::string getFileName() const;
		std::string getFileExtension() const;
		std::string getDirName() const;
	private:
		struct FilePathPrivate *_members = nullptr;
	};
}