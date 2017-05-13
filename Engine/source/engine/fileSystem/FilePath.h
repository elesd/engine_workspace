#pragma once

namespace engine
{
	class FilePath
	{
	public:
		explicit FilePath(const std::string &path);
		~FilePath();
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