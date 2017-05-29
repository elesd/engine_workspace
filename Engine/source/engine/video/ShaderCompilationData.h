#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class ShaderCompileOptions;

	class ShaderCompilationData
		: private NonCopyable
		, private NonMoveable
	{
	protected:
		ShaderCompilationData(const ShaderCompileOptions& options);
	public:
		virtual ~ShaderCompilationData();

		const ShaderCompileOptions& getOptions() const;

		void setError(const std::string& error);

		bool compilationWasSuccessfull() const;
		const std::string& getError() const;
		// TODO Add ShaderLayoutDescription
	protected:
		void setOk();
	private:

		struct ShaderCompilationDataPrivate* _members = nullptr;
	};
}