#include <stdafx.h>
#include <engine/video/ShaderCompilationData.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/ShaderCompileOptions.h>

namespace engine
{
	struct ShaderCompilationDataPrivate
	{
		ShaderCompilationDataPrivate(const ShaderCompileOptions& options)
			: options(options)
			, ok(false)
			, errorStr("")
		{ }

		ShaderCompileOptions options;

		bool ok = false;
		std::string errorStr;
	};

	ShaderCompilationData::ShaderCompilationData(const ShaderCompileOptions& options)
		: _members(new ShaderCompilationDataPrivate(options))
	{

	}

	ShaderCompilationData::~ShaderCompilationData()
	{
		delete _members;
		_members = nullptr;
	}

	const ShaderCompileOptions& ShaderCompilationData::getOptions() const
	{
		return _members->options;
	}

	void ShaderCompilationData::setOk()
	{
		_members->ok = true;
		_members->errorStr = "";
	}

	void ShaderCompilationData::setError(const std::string& error)
	{
		_members->ok = false;
		_members->errorStr = error;
	}

	bool ShaderCompilationData::compilationWasSuccessfull() const
	{
		return _members->ok;
	}

	const std::string& ShaderCompilationData::getError() const
	{
		return _members->errorStr;
	}

	void ShaderCompilationData::release()
	{
		releaseImpl();
	}
}