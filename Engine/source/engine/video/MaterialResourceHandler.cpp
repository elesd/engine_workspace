#include <stdafx.h>
#include <engine/video/MaterialResourceHandler.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/GPUTypes.h>
#include <engine/video/ShaderResourceStorage.h>
#include <engine/video/Material.h>
#include <engine/video/Effect.h>


namespace engine
{
	struct MaterialResourceHandlerPrivate
	{
		Material* material = nullptr;
		MaterialResourceHandlerPrivate(Material* material)
			: material(material)
		{ }
	};

	MaterialResourceHandler::MaterialResourceHandler(Material* material)
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
		for(const auto& pair : _members->material->getCompiledEffects())
		{
			ShaderResourceStorage *resources = pair.second->getResources();
			if(resources->hasResource(resourceName, GPUMemberType::Float))
			{
				pair.second->getResources()->setFloat(resourceName, value);
			}
		}
	}

	void MaterialResourceHandler::setVec2(const std::string& resourceName, const vec2& value)
	{
		for(const auto& pair : _members->material->getCompiledEffects())
		{
			ShaderResourceStorage *resources = pair.second->getResources();
			if(resources->hasResource(resourceName, GPUMemberType::Vec2))
			{
				pair.second->getResources()->setVec2(resourceName, value);
			}
		}
	}

	void MaterialResourceHandler::setVec3(const std::string& resourceName, const vec3& value)
	{
		for(const auto& pair : _members->material->getCompiledEffects())
		{
			ShaderResourceStorage *resources = pair.second->getResources();
			if(resources->hasResource(resourceName, GPUMemberType::Vec3))
			{
				pair.second->getResources()->setVec3(resourceName, value);
			}
		}
	}

	void MaterialResourceHandler::setVec4(const std::string& resourceName, const vec4& value)
	{
		for(const auto& pair : _members->material->getCompiledEffects())
		{
			ShaderResourceStorage *resources = pair.second->getResources();
			if(resources->hasResource(resourceName, GPUMemberType::Vec4))
			{
				pair.second->getResources()->setVec4(resourceName, value);
			}
		}
	}

	void MaterialResourceHandler::setMat3(const std::string& resourceName, const mat3& value)
	{
		for(const auto& pair : _members->material->getCompiledEffects())
		{
			ShaderResourceStorage *resources = pair.second->getResources();
			if(resources->hasResource(resourceName, GPUMemberType::Mat3))
			{
				pair.second->getResources()->setMat3(resourceName, value);
			}
		}
	}

	void MaterialResourceHandler::setMat4(const std::string& resourceName, const mat4& value)
	{
		for(const auto& pair : _members->material->getCompiledEffects())
		{
			ShaderResourceStorage *resources = pair.second->getResources();
			if(resources->hasResource(resourceName, GPUMemberType::Mat4))
			{
				pair.second->getResources()->setMat4(resourceName, value);
			}
		}
	}
}