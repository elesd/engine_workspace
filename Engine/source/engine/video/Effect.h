#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>
#include <engine/constraints/Lockable.h>

namespace engine
{

	class EffectCompilationData;
	class EffectInstance;
	class Material;
	class ShaderInstance;
	class ShaderCompilationData;
	class ShaderResourceStorage;


	class Effect
		: private NonCopyable
		, private NonMoveable
		, public Lockable<Effect>
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

		/*
		TODO: Make that only driver can commit resources and move ShaderResourceStorage to the EffectInstance.
		*/
		const ShaderResourceStorage* getResources() const;
		ShaderResourceStorage* getResources();

		void sync(EffectInstance* instance);

	private:
		void syncResources(EffectInstance* instance);
	private:
		struct EffectPrivate* _members = nullptr;
	};
}