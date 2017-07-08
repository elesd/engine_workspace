#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{

	class EffectCompilationData;
	class Material;
	class Shader;
	class ShaderCompilationData;


	class Effect
		: private NonCopyable
		, private NonMoveable
	{
	public:
		Effect(const Material *material, const std::string& techniqueName, Shader* vertexShader, Shader* fragmentShader);
		~Effect();

		void setCompiled(std::unique_ptr<EffectCompilationData>&& compilationData);
		bool isCompiled() const;

		const Shader* getVertexShader() const;
		const Shader* getFragmentShader() const;

		Shader* getVertexShader();
		Shader* getFragmentShader();

		const std::string& getName() const;
		const ShaderCompilationData* getVertexShaderData() const;
		const ShaderCompilationData* getFragmentShaderData() const;

		const EffectCompilationData* getCompilationData() const;
		const Material* getMaterial() const;
	private:
		void checkShaders() const;
		const ShaderCompilationData* getCorrespondingData(Shader* shader) const;

	private:
		struct EffectPrivate* _members = nullptr;
	};
}