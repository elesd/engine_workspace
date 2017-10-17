#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

#include <engine/utils/GuardedObject.h>

namespace engine
{
	class Effect;
	class EffectCompilationData;
	class MaterialInstance;
	class ShaderResourceStorageProxy;
	class ShaderInstance;

	class EffectInstance final
		: private NonCopyable
		, private NonMoveable
	{
		friend class Driver;
	public:
		EffectInstance(std::shared_ptr<Effect> source);
		~EffectInstance();

		bool isCompiled() const;
		const ShaderInstance* getVertexShader() const;
		const ShaderInstance* getFragmentShader() const;

		ShaderInstance* getVertexShader();
		ShaderInstance* getFragmentShader();

		const std::string& getName() const;
		const EffectCompilationData* getCompilationData() const;

		/* It is a bit complicated 
		   Effect has a source material and the effect instance needs a source material instance. 
		   It is not a good idea to make a function like this - Spagetti ongoing.
		   */
		//const MaterialInstance* getMaterial() const;

		const ShaderResourceStorageProxy* getResources() const;
		ShaderResourceStorageProxy* getResources();
	private:
		GuardedObject<Effect*> lockEffect();
		GuardedObject<const Effect*> lockEffect() const;
	private:
		struct EffectInstancePrivate* _members = nullptr;
	};
}