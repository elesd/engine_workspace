#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{

	class Shader;
	class ShaderCompilationData;
	class Effect
		: private NonCopyable
		, private NonMoveable
	{
	public:
		Effect(const std::string& techniqueName, Shader* vertexShader, Shader* fragmentShader);
		~Effect();

		const Shader* getVertexShader() const;
		const Shader* getFragmentShader() const;

		Shader* getVertexShader();
		Shader* getFragmentShader();

		const std::string& getName() const;
		const ShaderCompilationData* getVertexShaderData() const;
		const ShaderCompilationData* getFragmentShaderData() const;
	private:
		void checkShaders() const;
		const ShaderCompilationData* getCorrespondingData(Shader* shader) const;

	private:
		struct EffectPrivate* _members = nullptr;
	};
}