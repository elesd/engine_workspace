#include <stdafx.h>
#include <engine/render/Effect.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/Shader.h>
#include <engine/video/ShaderCompilationData.h>
#include <engine/video/ShaderCompileOptions.h>

namespace engine
{
	struct EffectPrivate
	{
		Shader* vertexShader = nullptr;
		Shader* fragmentShader = nullptr;
		const std::string techniqueName;
		EffectPrivate(const std::string& techniqueName, Shader* vertexShader, Shader* fragmentShader)
			: techniqueName(techniqueName)
			, vertexShader(vertexShader)
			, fragmentShader(fragmentShader)
		{ }
	};


	Effect::Effect(const std::string& techniqueName, Shader* vertexShader, Shader* fragmentShader)
		: _members(new EffectPrivate(techniqueName, vertexShader, fragmentShader))
	{
		checkShaders();
	}

	Effect::~Effect()
	{
		delete _members;
		_members = nullptr;
	}

	const Shader* Effect::getVertexShader() const
	{
		return _members->vertexShader;
	}
	
	const Shader* Effect::getFragmentShader() const
	{
		return _members->fragmentShader;
	}

	Shader* Effect::getVertexShader()
	{
		return _members->vertexShader;
	}

	Shader* Effect::getFragmentShader()
	{
		return _members->fragmentShader;
	}

	const std::string& Effect::getName() const
	{
		return _members->techniqueName;
	}

	void Effect::checkShaders() const
	{
		ASSERT(getVertexShaderData()->compilationWasSuccessfull());
		ASSERT(getFragmentShaderData()->compilationWasSuccessfull());
	}

	const ShaderCompilationData* Effect::getCorrespondingData(Shader* shader) const
	{
		return shader->getCompilationData(getName());
	}

	const ShaderCompilationData* Effect::getVertexShaderData() const
	{
		return getCorrespondingData(_members->vertexShader);
	}

	const ShaderCompilationData* Effect::getFragmentShaderData() const
	{
		return getCorrespondingData(_members->fragmentShader);
	}


}