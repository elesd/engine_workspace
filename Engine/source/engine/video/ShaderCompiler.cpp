#include <stdafx.h>
#include <engine/video/ShaderCompiler.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/Driver.h>
#include <engine/video/Shader.h>
#include <engine/video/ShaderCompilationData.h>
#include <engine/video/ShaderCompileOptions.h>

namespace engine
{
	struct ShaderCompilerPrivate
	{
		Driver* driver = nullptr;
		ShaderCompileOptions options;

		ShaderCompilerPrivate(Driver* driver, ShaderVersion version)
			: driver(driver)
			, options(version)
		{
		}

		ShaderCompilerPrivate(ShaderCompilerPrivate& o)
			: driver(o.driver)
			, options(o.options)
		{

		}

		ShaderCompilerPrivate& operator=(ShaderCompilerPrivate& o)
		{
			driver = o.driver;
			options = o.options;
		}
	};

	//////////////////////////////////////////////////////////////////////////////

	ShaderCompiler::ShaderCompiler(Driver* driver, ShaderVersion version)
		: _members(new ShaderCompilerPrivate(driver, version))
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
		(*_members) = *o._members;
		return *this;
	}

	ShaderCompiler& ShaderCompiler::operator=(ShaderCompiler&& o)
	{
		delete _members;
		_members = o._members;
		return *this;
	}

	bool ShaderCompiler::compileShader(Shader* shader, const std::string& techniqueName)
	{

		_members->driver->compileShader(shader, techniqueName, _members->options);

		return shader->getCompilationData(techniqueName)->compilationWasSuccessfull();
	}


	const ShaderCompileOptions& ShaderCompiler::getOptions() const
	{
		return _members->options;
	}

	ShaderCompileOptions& ShaderCompiler::getOptions()
	{
		return _members->options;
	}
}