#include <stdafx.h>
#include <engine/video/Shader.h>

#include <engine/Context.h>
#include <engine/app/Application.h>

#include <engine/fileSystem/FileSystem.h>
#include <engine/fileSystem/SimpleFile.h>

namespace engine
{
	struct ShaderPrivate
	{
		std::string code;
		std::vector<std::string> defines;
		bool initialized = false;
	};

	Shader::Shader()
		: _members(new ShaderPrivate)
	{
	}

	bool Shader::init(const FilePath& filePath)
	{
		SimpleFile source = Context::getInstance()->getApplication()->getFileSystem()->OpenFileSimple(filePath, FileMode::Read, FileOpenMode::Text, false);
		if (source.isOk() == false)
		{
			return false;
		}

		_members->code = source.readAll().data();
		_members->initialized = true;
		return true;
	}

	void Shader::init(const std::string& shaderCode)
	{
		_members->code = shaderCode;
		_members->initialized = true;
	}

	bool Shader::isInitialized() const
	{
		return _members->initialized;
	}

	const std::string& Shader::getCode() const
	{
		return _members->code;
	}

	const std::vector<std::string>& Shader::getDefines() const
	{
		return _members->defines;
	}

	void Shader::addShaderDefine(const std::string& define)
	{
		if (!hasShaderDefine(define))
		{
			_members->defines.push_back(define);
		}
	}

	bool Shader::removeShaderDefine(const std::string& define)
	{
		return false;
	}

	bool Shader::hasShaderDefine(const std::string &define) const
	{
		auto it = std::find(_members->defines.begin(), _members->defines.end(), define);
		return it != _members->defines.end();
	}
}