#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	
	class MaterialDescription;
	class ShaderCompiler;
	class Effect;
	class Driver;

	class EffectCompiler
		: private NonCopyable
		, private NonMoveable
	{
		friend class RenderContext;
	private:
		EffectCompiler(Driver* driver, std::unique_ptr<ShaderCompiler>&& compiler, const MaterialDescription& descriptor);
	public:
		~EffectCompiler();

		std::unique_ptr<Effect> compileEffect(const std::string& techniqueName);

	private:
		struct EffectCompilerPrivate* _members = nullptr;
	};
}