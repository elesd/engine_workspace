#include <stdafx.h>
#include <engine/libraries/MaterialResourceHandler.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/libraries/MaterialInstance.h>
#include <engine/libraries/EffectInstance.h>
#include <engine/libraries/ShaderResourceStorageProxy.h>

#include <engine/video/GPUTypes.h>
#include <engine/video/ShaderResourceStorage.h>


namespace engine
{
	struct MaterialResourceHandlerPrivate
	{
		MaterialInstance* material = nullptr;
		MaterialResourceHandlerPrivate(MaterialInstance* material)
			: material(material)
		{ }
	};

	MaterialResourceHandler::MaterialResourceHandler(MaterialInstance* material)
		: _members(new MaterialResourceHandlerPrivate(material))
	{

	}

	MaterialResourceHandler::~MaterialResourceHandler()
	{
		delete _members;
		_members = nullptr;
	}

	void MaterialResourceHandler::setFloat(const std::string& resourceName, float value)
	{
		for(const auto& pair : _members->material->collectAllEffects())
		{
			ShaderResourceStorageProxy *resources = pair.second->getResources();
			resources->setFloat(resourceName, value);
		}
	}

	void MaterialResourceHandler::setVec2(const std::string& resourceName, const vec2& value)
	{
		for(const auto& pair : _members->material->collectAllEffects())
		{
			ShaderResourceStorageProxy *resources = pair.second->getResources();
			pair.second->getResources()->setVec2(resourceName, value);
		}
	}

	void MaterialResourceHandler::setVec3(const std::string& resourceName, const vec3& value)
	{
		for(const auto& pair : _members->material->collectAllEffects())
		{
			ShaderResourceStorageProxy *resources = pair.second->getResources();
			pair.second->getResources()->setVec3(resourceName, value);
		}
	}

	void MaterialResourceHandler::setVec4(const std::string& resourceName, const vec4& value)
	{
		for(const auto& pair : _members->material->collectAllEffects())
		{
			ShaderResourceStorageProxy *resources = pair.second->getResources();
			pair.second->getResources()->setVec4(resourceName, value);
		}
	}

	void MaterialResourceHandler::setMat3(const std::string& resourceName, const mat3& value)
	{
		for(const auto& pair : _members->material->collectAllEffects())
		{
			ShaderResourceStorageProxy *resources = pair.second->getResources();
			pair.second->getResources()->setMat3(resourceName, value);
		}
	}

	void MaterialResourceHandler::setMat4(const std::string& resourceName, const mat4& value)
	{
		for(const auto& pair : _members->material->collectAllEffects())
		{
			ShaderResourceStorageProxy *resources = pair.second->getResources();
			pair.second->getResources()->setMat4(resourceName, value);
		}
	}
}