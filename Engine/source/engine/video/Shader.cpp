#include <stdafx.h>
#include <engine/video/Shader.h>

#include <engine/Context.h>
#include <engine/app/Application.h>

#include <engine/fileSystem/FileSystem.h>
#include <engine/fileSystem/SimpleFile.h>

#include <engine/video/ShaderCompilationData.h>
#include <engine/video/ShaderCompileOptions.h>

namespace
{
	std::vector<engine::ShaderType> allShader = {engine::ShaderType::FragmentShader, engine::ShaderType::FragmentShader};
}

namespace engine
{
	const std::vector<ShaderType>& ShaderTypeHelper::getAll()
	{
		return allShader;
	}

	struct ShaderPrivate
	{
		std::string code;
		std::string mainFunctionName;
		bool initialized = false;
		ShaderType shaderType;
		std::map<std::string, std::unique_ptr<ShaderCompilationData>> techniquesCompilationData;
		ShaderPrivate(ShaderType type) : shaderType(type) {}
	};

	Shader::Shader(ShaderType type)
		: _members(new ShaderPrivate(type))
	{
	}

	Shader::~Shader()
	{
		delete _members;
		_members = nullptr;
	}

	bool Shader::init(const FilePath& filePath, const std::string& mainFunctionName)
	{
		SimpleFile source = Context::fileSystem()->OpenFileSimple(filePath, FileMode::Read, FileOpenMode::Text, false);
		if (source.isOk() == false)
		{
			return false;
		}

		_members->code = source.readAll().data();
		_members->initialized = true;
		_members->mainFunctionName = mainFunctionName;
		return true;
	}

	void Shader::init(const std::string& shaderCode, const std::string& mainFunctionName)
	{
		_members->code = shaderCode;
		_members->initialized = true;
		_members->mainFunctionName = mainFunctionName;
	}

	bool Shader::isInitialized() const
	{
		return _members->initialized;
	}

	bool Shader::isCompiled(const std::string& techniqueName) const
	{
		return _members->techniquesCompilationData.find(techniqueName) != _members->techniquesCompilationData.end();
	}
	
	const std::string& Shader::getCode() const
	{
		ASSERT(isInitialized());
		return _members->code;
	}

	ShaderType Shader::getShaderType() const
	{
		return _members->shaderType;
	}

	const std::string& Shader::getMainFunctionName()
	{
		ASSERT(isInitialized());
		return _members->mainFunctionName;
	}

	void Shader::setCompiled(const std::string& techniqueName, std::unique_ptr<ShaderCompilationData>&& compilationData)
	{
		ASSERT(isInitialized());
		_members->techniquesCompilationData.insert(std::make_pair(techniqueName, std::move(compilationData)));
	}

	const ShaderCompilationData* Shader::getCompilationData(const std::string& techniqueName) const
	{
		ASSERT(isInitialized());
		ASSERT(isCompiled(techniqueName));
		auto it = _members->techniquesCompilationData.find(techniqueName);
		return it != _members->techniquesCompilationData.end() ? it->second.get() : nullptr;
	}

	bool Shader::isSame(const std::string& technique, const Shader& o) const
	{
		bool result = getCode() == o.getCode();
		result = result && getCompilationData(technique)->getOptions() == o.getCompilationData(technique)->getOptions();
		return result;
	}

	void Shader::releaseCompilationData(const std::string& technique)
	{
		ASSERT(isCompiled(technique));
		_members->techniquesCompilationData[technique]->release();
	}
}