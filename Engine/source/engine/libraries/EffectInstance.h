#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class Effect;
	class EffectCompilationData;
	class Material;
	class ShaderResourceStorageProxy;
	class ShaderInstance;

	class EffectInstance final
		: private NonCopyable
		, private NonMoveable
	{
	public:
		EffectInstance(Effect* source);
		~EffectInstance();

		bool isCompiled() const;
		const ShaderInstance* getVertexShader() const;
		const ShaderInstance* getFragmentShader() const;

		ShaderInstance* getVertexShader();
		ShaderInstance* getFragmentShader();

		const std::string& getName() const;
		const EffectCompilationData* getCompilationData() const;
		const Material* getMaterial() const;

		const ShaderResourceStorageProxy* getResources() const;
		ShaderResourceStorageProxy* getResources();
	private:
		struct EffectInstancePrivate* _members = nullptr;
	};
}