#include <stdafx.h>
#include <engine/video/EffectCompilationData.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	struct EffectCompilationDataPrivate
	{
		bool supportSeparateProgram = false;
		std::string errorMsg;
		bool ok = false;
		explicit EffectCompilationDataPrivate(bool supportSeparateProgram)
			: supportSeparateProgram(supportSeparateProgram)
		{ }
	};

	EffectCompilationData::EffectCompilationData(bool supportSeparateProgram)
		: _members(new EffectCompilationDataPrivate(supportSeparateProgram))
	{

	}

	EffectCompilationData::~EffectCompilationData()
	{
		delete _members;
		_members = nullptr;
	}

	bool EffectCompilationData::isSupportSeparatePrograms() const
	{
		return _members->supportSeparateProgram;
	}

	const std::string& EffectCompilationData::getErrorMsg() const
	{
		return _members->errorMsg;
	}

	bool EffectCompilationData::isOk() const
	{
		return _members->ok;
	}

	void EffectCompilationData::setOk()
	{
		_members->ok = true;
	}

	void EffectCompilationData::setError(const std::string& errorMsg)
	{
		_members->ok = false;
		_members->errorMsg = errorMsg;
	}
}