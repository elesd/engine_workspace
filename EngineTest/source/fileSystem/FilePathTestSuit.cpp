#include <stdafx.h>
#include <fileSystem/FilePathTestSuit.h>

#include <engine/fileSystem/FilePath.h>

namespace tests
{
	void FilePathTestSuit::normalizeTest01()
	{
		const std::string testPath = "\\test\\test2";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.str() == "/test/test2"));
	}

	void FilePathTestSuit::normalizeTest02()
	{
		const std::string testPath = "\\test/test2";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.str() == "/test/test2"));
	}

	void FilePathTestSuit::normalizeTest03()
	{
		const std::string testPath = "test\\test2\\";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.str() == "test/test2/"));
	}

	void FilePathTestSuit::normalizeTest04()
	{
		const std::string testPath = "C:\\test\\test2";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.str() == "C:/test/test2"));
	}
	void FilePathTestSuit::normalizeTest05()
	{
		const std::string testPath = "";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.str() == ""));
	}

	void FilePathTestSuit::normalizeTest06()
	{
		const std::string testPath = "\\test///test2//";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.str() == "/test/test2/"));
	}

	void FilePathTestSuit::fileNameTest01()
	{
		const std::string testPath = "test2.cpp";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getFileName() == "test2.cpp"));
	}

	void FilePathTestSuit::fileNameTest02()
	{
		const std::string testPath = "test/test2.cpp";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getFileName() == "test2.cpp"));
	}

	void FilePathTestSuit::fileNameTest03()
	{
		const std::string testPath = "test/test2";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getFileName() == "test2"));
	}

	void FilePathTestSuit::fileNameTest04()
	{
		const std::string testPath = "/test2";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getFileName() == "test2"));
	}

	void FilePathTestSuit::fileNameTest05()
	{
		const std::string testPath = "";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getFileName() == ""));
	}

	void FilePathTestSuit::fileNameTest06()
	{
		const std::string testPath = "test2/";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getFileName() == ""));
	}

	void FilePathTestSuit::fileNameTest07()
	{
		const std::string testPath = "/test2/";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getFileName() == ""));
	}

	void FilePathTestSuit::fileExtensionTest01()
	{
		const std::string testPath = "test2.cpp";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getFileExtension() == "cpp"));
	}

	void FilePathTestSuit::fileExtensionTest02()
	{
		const std::string testPath = "test2.cpp.h";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getFileExtension() == "h"));
	}

	void FilePathTestSuit::fileExtensionTest03()
	{
		const std::string testPath = "test2";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getFileExtension() == ""));
	}

	void FilePathTestSuit::fileExtensionTest04()
	{
		const std::string testPath = "";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getFileExtension() == ""));
	}

	void FilePathTestSuit::fileExtensionTest05()
	{
		const std::string testPath = "/test2";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getFileExtension() == ""));
	}

	void FilePathTestSuit::fileExtensionTest06()
	{
		const std::string testPath = "/test2.asd";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getFileExtension() == "asd"));
	}

	void FilePathTestSuit::dirNameTest01()
	{
		const std::string testPath = "/test2.asd";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getDirName() == "/"));
	}

	void FilePathTestSuit::dirNameTest02()
	{
		const std::string testPath = "test2.asd";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getDirName() == "."));
	}

	void FilePathTestSuit::dirNameTest03()
	{
		const std::string testPath = "test/test2/test2.asd";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getDirName() == "test/test2"));
	}

	void FilePathTestSuit::dirNameTest04()
	{
		const std::string testPath = "/test/test2/test2.asd";
		engine::FilePath path(testPath);
		assertTrue(ASSERTION_PARAMETER(path.getDirName() == "/test/test2"));
	}
}