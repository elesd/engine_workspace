#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

#include <engine/utils/GuardedObject.h>

namespace engine
{

	class EffectCompilationData;
	class Material;
	class ShaderInstance;
	class ShaderCompilationData;
	class ShaderResourceStorage;


	class Effect
		: private NonCopyable
		, private NonMoveable
	{
	public:
		Effect(const Material *material, const std::string& techniqueName, std::unique_ptr<ShaderInstance>&& vertexShader, std::unique_ptr<ShaderInstance>&& fragmentShader, std::unique_ptr<ShaderResourceStorage>&& resources);
		~Effect();

		void setCompiled(std::unique_ptr<EffectCompilationData>&& compilationData);
		bool isCompiled() const;

		const ShaderInstance* getVertexShader() const;
		const ShaderInstance* getFragmentShader() const;

		ShaderInstance* getVertexShader();
		ShaderInstance* getFragmentShader();

		const std::string& getName() const;

		const EffectCompilationData* getCompilationData() const;
		const Material* getMaterial() const;

		const ShaderResourceStorage* getResources() const;
		ShaderResourceStorage* getResources();
		GuardedObject<Effect*> lock();
		GuardedObject<const Effect*> lock() const;
	private:
		struct EffectPrivate* _members = nullptr;
	};
}