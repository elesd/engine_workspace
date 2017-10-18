#include <stdafx.h>
#include <engine/video/Effect.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/libraries/EffectInstance.h>
#include <engine/libraries/ShaderResourceStorageProxy.h>
#include <engine/libraries/ShaderInstance.h>

#include <engine/video/EffectCompilationData.h>
#include <engine/video/Shader.h>
#include <engine/video/ShaderCompilationData.h>
#include <engine/video/ShaderCompileOptions.h>
#include <engine/video/ShaderResourceDescription.h>
#include <engine/video/ShaderResourceStorage.h>
#include <engine/video/GPUTypes.h>

namespace engine
{
	struct EffectPrivate
	{
		std::unique_ptr<ShaderInstance> vertexShader = nullptr;
		std::unique_ptr<ShaderInstance> fragmentShader = nullptr;
		const Material* material = nullptr;
		std::unique_ptr<EffectCompilationData> compilationData;
		std::unique_ptr<ShaderResourceStorage> resources;
		const std::string techniqueName;
		EffectPrivate(const Material* material, const std::string& techniqueName, std::unique_ptr<ShaderInstance>&& vertexShader, std::unique_ptr<ShaderInstance>&& fragmentShader, std::unique_ptr<ShaderResourceStorage>&& resources)
			: techniqueName(techniqueName)
			, vertexShader(std::move(vertexShader))
			, fragmentShader(std::move(fragmentShader))
			, material(material)
			, resources(std::move(resources))
		{
		}
	};


	Effect::Effect(const Material* material, const std::string& techniqueName, std::unique_ptr<ShaderInstance>&& vertexShader, std::unique_ptr<ShaderInstance>&& fragmentShader, std::unique_ptr<ShaderResourceStorage>&& resources)
		: _members(new EffectPrivate(material, techniqueName, std::move(vertexShader), std::move(fragmentShader), std::move(resources)))
	{
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

	const ShaderInstance* Effect::getVertexShader() const
	{
		return _members->vertexShader.get();
	}

	const ShaderInstance* Effect::getFragmentShader() const
	{
		return _members->fragmentShader.get();
	}

	ShaderInstance* Effect::getVertexShader()
	{
		return _members->vertexShader.get();
	}

	ShaderInstance* Effect::getFragmentShader()
	{
		return _members->fragmentShader.get();
	}

	const std::string& Effect::getName() const
	{
		return _members->techniqueName;
	}

	const EffectCompilationData* Effect::getCompilationData() const
	{
		return _members->compilationData.get();
	}

	const Material* Effect::getMaterial() const
	{
		return _members->material;
	}

	const ShaderResourceStorage* Effect::getResources() const
	{
		return _members->resources.get();
	}

	ShaderResourceStorage* Effect::getResources()
	{
		return _members->resources.get();
	}
	
	void Effect::sync(EffectInstance* instance)
	{
		syncResources(instance);
	}

	void Effect::syncResources(EffectInstance* instance)
	{
		{
			std::vector<std::pair<std::string, float>> changeMap = instance->getResources()->clearChangesInFloats();
			for(const std::pair<std::string, float>& pair : changeMap)
			{
				getResources()->setFloat(pair.first, pair.second);
			}
		}
		{
			std::vector<std::pair<std::string, vec2>> changeMap = instance->getResources()->clearChangesInVec2();
			for(const std::pair<std::string, vec2>& pair : changeMap)
			{
				getResources()->setVec2(pair.first, pair.second);
			}
		}
		{
			std::vector<std::pair<std::string, vec3>> changeMap = instance->getResources()->clearChangesInVec3();
			for(const std::pair<std::string, vec3>& pair : changeMap)
			{
				getResources()->setVec3(pair.first, pair.second);
			}
		}
		{
			std::vector<std::pair<std::string, vec4>> changeMap = instance->getResources()->clearChangesInVec4();
			for(const std::pair<std::string, vec4>& pair : changeMap)
			{
				getResources()->setVec4(pair.first, pair.second);
			}
		}
		{
			std::vector<std::pair<std::string, mat3>> changeMap = instance->getResources()->clearChangesInMat3();
			for(const std::pair<std::string, mat3>& pair : changeMap)
			{
				getResources()->setMat3(pair.first, pair.second);
			}
		}
		{
			std::vector<std::pair<std::string, mat4>> changeMap = instance->getResources()->clearChangesInMat4();
			for(const std::pair<std::string, mat4>& pair : changeMap)
			{
				getResources()->setMat4(pair.first, pair.second);
			}
		}
	}

}