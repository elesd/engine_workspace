#include <stdafx.h>
#include <fileSystem/SimpleFileTestSuit.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/fileSystem/FilePath.h>
#include <engine/fileSystem/SimpleFile.h>
#include <engine/exceptions/RuntimeErrors.h>
namespace
{
	const std::string &emptyFilePath = "../../data/emptyFile.txt";
	const std::string &longFilePath = "../../data/longFile.txt";
	const std::string &testFilePath = "../../data/testFile.txt";
	const std::string &invalidPath = "../../data/monkey.txt";
}

namespace tests
{
	void SimpleFileTestSuit::openFileTest01()
	{
		engine::SimpleFile file(engine::FilePath(testFilePath), engine::FileMode::Read, engine::FileOpenMode::Text, false);
		assertTrue(ASSERTION_PARAMETER(file.isOk()));
	}

	void SimpleFileTestSuit::openFileTest02()
	{
		engine::SimpleFile file(engine::FilePath(invalidPath), engine::FileMode::Read, engine::FileOpenMode::Text, false);
		assertTrue(ASSERTION_PARAMETER(file.isOk() == false));
	}

	void SimpleFileTestSuit::readLineTest01()
	{
		engine::SimpleFile file(engine::FilePath(testFilePath), engine::FileMode::Read, engine::FileOpenMode::Text, false);
		std::string line = file.readLine();
		assertTrue(ASSERTION_PARAMETER(line == "this is a test line"));
		assertTrue(ASSERTION_PARAMETER(file));
	}

	void SimpleFileTestSuit::readLineTest02()
	{
		engine::SimpleFile file(engine::FilePath(longFilePath), engine::FileMode::Read, engine::FileOpenMode::Text, false);
		std::string line = file.readLine();
		assertTrue(ASSERTION_PARAMETER(line == "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"));
		assertTrue(ASSERTION_PARAMETER(file));
	}

	void SimpleFileTestSuit::readLineTest03()
	{
		engine::SimpleFile file(engine::FilePath(invalidPath), engine::FileMode::Read, engine::FileOpenMode::Text, false);
		bool exceptionCatched = false;
		try
		{
			std::string line = file.readLine();
		}
		catch(engine::IOError &)
		{
			exceptionCatched = true;
		}
		assertTrue(ASSERTION_PARAMETER(exceptionCatched));
		assertTrue(ASSERTION_PARAMETER(file.isOk() == false));
	}

	void SimpleFileTestSuit::readLineTest04()
	{
		engine::SimpleFile file(engine::FilePath(emptyFilePath), engine::FileMode::Read, engine::FileOpenMode::Text, false);
		std::string line = file.readLine();
		assertTrue(ASSERTION_PARAMETER(line == ""));
		assertTrue(ASSERTION_PARAMETER(file.atEof()));
		assertTrue(ASSERTION_PARAMETER(file));
	}

	void SimpleFileTestSuit::readLinesTest01()
	{
		engine::SimpleFile file(engine::FilePath(testFilePath), engine::FileMode::Read, engine::FileOpenMode::Text, false);
		std::vector<std::string> lines = file.readLines();
		assertTrue(ASSERTION_PARAMETER(lines.size() == 6));
		assertTrue(ASSERTION_PARAMETER(file));
	}

	void SimpleFileTestSuit::readLinesTest02()
	{
		engine::SimpleFile file(engine::FilePath(invalidPath), engine::FileMode::Read, engine::FileOpenMode::Text, false);
		bool exceptionCatched = false;
		try
		{
			std::vector<std::string> lines = file.readLines();
		} 
		catch(engine::IOError &)
		{
			exceptionCatched = true;
		}
		assertTrue(ASSERTION_PARAMETER(exceptionCatched));
		assertTrue(ASSERTION_PARAMETER(file.isOk() == false));
	}

	void SimpleFileTestSuit::readLinesTest03()
	{
		engine::SimpleFile file(engine::FilePath(emptyFilePath), engine::FileMode::Read, engine::FileOpenMode::Text, false);
		std::vector<std::string> lines = file.readLines();
		assertTrue(ASSERTION_PARAMETER(lines.size() == 1));
		assertTrue(ASSERTION_PARAMETER(lines[0] == ""));
		assertTrue(ASSERTION_PARAMETER(file));
		assertTrue(ASSERTION_PARAMETER(file.atEof()));
	}

	void SimpleFileTestSuit::readAllTest01()
	{
		engine::SimpleFile file(engine::FilePath(testFilePath), engine::FileMode::Read, engine::FileOpenMode::Text, false);
		std::vector<char> buff = file.readAll();
		assertTrue(ASSERTION_PARAMETER(file));
		assertTrue(ASSERTION_PARAMETER(buff.size() == 64));
	}

	void SimpleFileTestSuit::readAllTest02()
	{
		engine::SimpleFile file(engine::FilePath(invalidPath), engine::FileMode::Read, engine::FileOpenMode::Text, false);
		bool exceptionCatched = false;
		try
		{
			std::vector<char> buff = file.readAll();
		} 
		catch(engine::IOError &)
		{
			exceptionCatched = true;
		}
		assertTrue(ASSERTION_PARAMETER(exceptionCatched));
		assertTrue(ASSERTION_PARAMETER(file.isOk() == false));
	}

	void SimpleFileTestSuit::readAllTest03()
	{
		engine::SimpleFile file(engine::FilePath(emptyFilePath), engine::FileMode::Read, engine::FileOpenMode::Text, false);
		std::vector<char> buff = file.readAll();
		assertTrue(ASSERTION_PARAMETER(buff.size() == 0));
		assertTrue(ASSERTION_PARAMETER(file));
		assertTrue(ASSERTION_PARAMETER(file.atEof()));
	}

	void SimpleFileTestSuit::getSizeTest01()
	{
		engine::SimpleFile file(engine::FilePath(testFilePath), engine::FileMode::Read, engine::FileOpenMode::Text, false);
		size_t size = file.getSize();
		assertTrue(ASSERTION_PARAMETER(file));
		assertTrue(ASSERTION_PARAMETER(size == 64));
	}

	void SimpleFileTestSuit::getSizeTest02()
	{
		engine::SimpleFile file(engine::FilePath(invalidPath), engine::FileMode::Read, engine::FileOpenMode::Text, false);
		bool exceptionCatched = false;
		try
		{
			size_t size = file.getSize();
		} 
		catch(engine::IOError &)
		{
			exceptionCatched = true;
		}
		assertTrue(ASSERTION_PARAMETER(exceptionCatched));
		assertTrue(ASSERTION_PARAMETER(file.isOk() == false));
	}

	void SimpleFileTestSuit::getSizeTest03()
	{
		engine::SimpleFile file(engine::FilePath(emptyFilePath), engine::FileMode::Read, engine::FileOpenMode::Text, false);
		size_t size = file.getSize();
		assertTrue(ASSERTION_PARAMETER(size == 0));
		assertTrue(ASSERTION_PARAMETER(file));
	}
}