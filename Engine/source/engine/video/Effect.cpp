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
		const std::string techniqueName;
		std::unique_ptr<ShaderInstance> vertexShader = nullptr;
		std::unique_ptr<ShaderInstance> fragmentShader = nullptr;
		const Material* material = nullptr;
		std::unique_ptr<EffectCompilationData> compilationData;
		std::unique_ptr<ShaderResourceStorage> resources;

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
		// TODO figure out something better
		std::vector<ShaderResourceDescription> descriptions = _members->resources->collectDescriptions();
		for(const ShaderResourceDescription& desc : descriptions)
		{
			const std::string& resourceName = desc.getName();
			switch(desc.getType())
			{
				case GPUMemberType::Float: getResources()->setFloat(resourceName, instance->getResources()->getFloat(resourceName)); break;
				case GPUMemberType::Mat3: getResources()->setMat3(resourceName, instance->getResources()->getMat3(resourceName)); break;
				case GPUMemberType::Mat4: getResources()->setMat4(resourceName, instance->getResources()->getMat4(resourceName)); break;
				case GPUMemberType::Vec2: getResources()->setVec2(resourceName, instance->getResources()->getVec2(resourceName)); break;
				case GPUMemberType::Vec3: getResources()->setVec3(resourceName, instance->getResources()->getVec3(resourceName)); break;
				case GPUMemberType::Vec4: getResources()->setVec4(resourceName, instance->getResources()->getVec4(resourceName)); break;
				default: FAIL("Unknown shader resource");
					break;
			}
		}
	}

}
