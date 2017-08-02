#include <stdafx.h>
#include <engine/video/ShaderCompiler.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/AttributeFormat.h>
#include <engine/video/Driver.h>
#include <engine/video/Shader.h>
#include <engine/video/ShaderCompilationData.h>
#include <engine/video/ShaderCompileOptions.h>

namespace engine
{
	struct ShaderCompilerPrivate
	{
		Driver* driver = nullptr;
		ShaderVersion version;
		std::map<std::string, ShaderCompileOptions> techniqueMap;
		AttributeFormat attributeFormat;

		ShaderCompilerPrivate(Driver* driver, ShaderVersion version, const AttributeFormat& format)
			: driver(driver)
			, version(version)
			, attributeFormat(format)
		{
		}

		ShaderCompilerPrivate(ShaderCompilerPrivate& o)
			: driver(o.driver)
			, version(o.version)
			, techniqueMap(o.techniqueMap)
		{

		}

		ShaderCompilerPrivate& operator=(ShaderCompilerPrivate& o)
		{
			driver = o.driver;
			techniqueMap = o.techniqueMap;
			version = o.version;
			return *this;
		}
	};

	//////////////////////////////////////////////////////////////////////////////

	ShaderCompiler::ShaderCompiler(Driver* driver, ShaderVersion version, const AttributeFormat& format)
		: _members(new ShaderCompilerPrivate(driver, version, format))
	{

	}
	ShaderCompiler::ShaderCompiler(const ShaderCompiler& o)
		: _members(o._members ? new ShaderCompilerPrivate(*o._members) : nullptr)
	{

	}

	ShaderCompiler::ShaderCompiler(ShaderCompiler&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	ShaderCompiler::~ShaderCompiler()
	{
		delete _members;
		_members = nullptr;
	}

	ShaderCompiler& ShaderCompiler::operator=(const ShaderCompiler& o)
	{
		if(o._members)
		{
			(*_members) = *o._members;
		}
		else
		{
			delete _members;
			_members = nullptr;
		}
		return *this;
	}

	ShaderCompiler& ShaderCompiler::operator=(ShaderCompiler&& o)
	{
		delete _members;
		_members = o._members;
		return *this;
	}

	void ShaderCompiler::init(const std::map<std::string, ShaderCompileOptions>& techniqueMap)
	{
		_members->techniqueMap = techniqueMap;
	}

	bool ShaderCompiler::compileShader(Shader* shader, const std::string& techniqueName)
	{
		auto it = _members->techniqueMap.find(techniqueName);
		ASSERT(it != _members->techniqueMap.end());
		_members->driver->compileShader(shader, techniqueName, it->second, _members->attributeFormat);

		return shader->getCompilationData(techniqueName)->compilationWasSuccessfull();
	}


	const ShaderCompileOptions& ShaderCompiler::getOptions(const std::string& techniqueName) const
	{
		auto it = _members->techniqueMap.find(techniqueName);
		ASSERT(it != _members->techniqueMap.end());
		return it->second;
	}

	ShaderCompileOptions& ShaderCompiler::getOptions(const std::string& techniqueName)
	{
		return _members->techniqueMap[techniqueName];
	}
}