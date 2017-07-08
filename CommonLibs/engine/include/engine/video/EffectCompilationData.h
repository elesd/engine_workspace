#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class EffectCompilationData 
		: private NonCopyable
		, private NonMoveable
	{
	public:
		EffectCompilationData(bool supportSeparateProgram);
		virtual ~EffectCompilationData();

		bool isSupportSeparatePrograms() const;

		const std::string& getErrorMsg() const;
		bool isOk() const;

		void setOk();
		void setError(const std::string& errorMsg);
		
	private:
		struct EffectCompilationDataPrivate* _members = nullptr;
	};
}