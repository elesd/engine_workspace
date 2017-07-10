#include <stdafx.h>
#include <engine/video/Effect.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/EffectCompilationData.h>
#include <engine/video/Shader.h>
#include <engine/video/ShaderCompilationData.h>
#include <engine/video/ShaderCompileOptions.h>

namespace engine
{
	struct EffectPrivate
	{
		Shader* vertexShader = nullptr;
		Shader* fragmentShader = nullptr;
		const Material* material = nullptr;
		std::unique_ptr<EffectCompilationData> compilationData;
		const std::string techniqueName;
		EffectPrivate(const Material* material, const std::string& techniqueName, Shader* vertexShader, Shader* fragmentShader)
			: techniqueName(techniqueName)
			, vertexShader(vertexShader)
			, fragmentShader(fragmentShader)
		{ }
	};


	Effect::Effect(const Material* material, const std::string& techniqueName, Shader* vertexShader, Shader* fragmentShader)
		: _members(new EffectPrivate(material, techniqueName, vertexShader, fragmentShader))
	{
		checkShaders();
	}

	Effect::~Effect()
	{
		delete _members;
		_members = nullptr;
	}

	void Effect::setCompiled(std::unique_ptr<EffectCompilationData>&& compilationData)
	{
		ASSERT(isCompiled() == false);
		_members->compilationData = std::move(compilationData);
	}

	bool Effect::isCompiled() const
	{
		return _members->compilationData != nullptr;
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
		if(getVertexShaderData()->compilationWasSuccessfull() == false)
		{
			std::cerr << "Vertex shader error: " << getVertexShaderData()->getError() << std::endl;
			FAIL("Shader compilation error");
		}
		if(getFragmentShaderData()->compilationWasSuccessfull() == false)
		{
			std::cerr << "Vertex shader error: " << getFragmentShaderData()->getError() << std::endl;
			FAIL("Shader compilation error");
		}
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

	const EffectCompilationData* Effect::getCompilationData() const
	{
		return _members->compilationData.get();
	}

	const Material* Effect::getMaterial() const
	{
		return _members->material;
	}

}