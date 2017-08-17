#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class Material;
	class MaterialDescription;
	class ShaderCompileOptions;
	class ShaderCompiler;
	class Effect;
	class Driver;

	class EffectCompiler
		: private NonCopyable
		, private NonMoveable
	{
		friend class RenderContext;
	private:
		EffectCompiler(Material* material, Driver* driver, std::unique_ptr<ShaderCompiler>&& compiler);
	public:
		~EffectCompiler();

		std::unique_ptr<Effect> compileEffect(const std::string& techniqueName);
	private:
		void bindResources(Effect* effect) const;
	private:
		struct EffectCompilerPrivate* _members = nullptr;
	};
}