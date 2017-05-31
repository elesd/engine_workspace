#include <stdafx.h>
#include <engine/render/Effect.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/Shader.h>
#include <engine/video/ShaderCompilationData.h>

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
		ASSERT(_members->vertexShader->getCompilationData(getName())->compilationWasSuccessfull());
		ASSERT(_members->fragmentShader->getCompilationData(getName())->compilationWasSuccessfull());
	}
}