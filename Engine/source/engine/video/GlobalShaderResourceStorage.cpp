#include <stdafx.h>
#include <engine/video/GlobalShaderResourceStorage.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/GlobalShaderResource.h>
#include <engine/video/ShaderResourceHandler.h>
#include <engine/video/ShaderResourceDescription.h>
#include <engine/video/GPUTypes.h>

namespace engine
{
	struct GlobalShaderResourceStoragePrivate
	{
		std::unordered_map<std::string, GlobalShaderResource<GPUMemberType::Float>> floatResources;
		std::unordered_map<std::string, GlobalShaderResource<GPUMemberType::Vec2>> vec2Resources;
		std::unordered_map<std::string, GlobalShaderResource<GPUMemberType::Vec3>> vec3Resources;
		std::unordered_map<std::string, GlobalShaderResource<GPUMemberType::Vec4>> vec4Resources;
		std::unordered_map<std::string, GlobalShaderResource<GPUMemberType::Mat3>> mat3Resources;
		std::unordered_map<std::string, GlobalShaderResource<GPUMemberType::Mat4>> mat4Resources;
		GlobalShaderResourceStorage* parentStorage = nullptr;

		GlobalShaderResourceStoragePrivate()
		{
		}
		GlobalShaderResourceStoragePrivate(GlobalShaderResourceStorage* parentStorage)
			: parentStorage(parentStorage)
		{
		}

	};

	GlobalShaderResourceStorage::GlobalShaderResourceStorage(GlobalShaderResourceStorage* parentStorage)
		: _members(new GlobalShaderResourceStoragePrivate(parentStorage))
	{

	}


	GlobalShaderResourceStorage::GlobalShaderResourceStorage(GlobalShaderResourceStorage&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	GlobalShaderResourceStorage::~GlobalShaderResourceStorage()
	{
		delete _members;
		_members = nullptr;
	}

	GlobalShaderResourceStorage& GlobalShaderResourceStorage::operator=(GlobalShaderResourceStorage&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	void GlobalShaderResourceStorage::addResource(const ShaderResourceDescription& desc)
	{
		const std::string& resourceName = desc.getName();
		GPUMemberType type = desc.getType();
		ASSERT(hasResource(resourceName, type) == false);
		switch(type)
		{
			case engine::GPUMemberType::Float:
				_members->floatResources.insert(std::make_pair(resourceName, GlobalShaderResource<GPUMemberType::Float>(desc)));
				break;
			case engine::GPUMemberType::Vec2:
				_members->vec2Resources.insert(std::make_pair(resourceName, GlobalShaderResource<GPUMemberType::Vec2>(desc)));
				break;
			case engine::GPUMemberType::Vec3:
				_members->vec3Resources.insert(std::make_pair(resourceName, GlobalShaderResource<GPUMemberType::Vec3>(desc)));
				break;
			case engine::GPUMemberType::Vec4:
				_members->vec4Resources.insert(std::make_pair(resourceName, GlobalShaderResource<GPUMemberType::Vec4>(desc)));
				break;
			case engine::GPUMemberType::Mat3:
				_members->mat3Resources.insert(std::make_pair(resourceName, GlobalShaderResource<GPUMemberType::Mat3>(desc)));
				break;
			case engine::GPUMemberType::Mat4:
				_members->mat4Resources.insert(std::make_pair(resourceName, GlobalShaderResource<GPUMemberType::Mat4>(desc)));
				break;
			default:
				FAIL("Unknown resource type");
				break;
		}
	}

	bool GlobalShaderResourceStorage::hasResource(const std::string& resourceName, GPUMemberType type) const
	{
		if(_members->parentStorage && _members->parentStorage->hasResource(resourceName, type))
		{
			return true;
		}

		bool result = false;
		switch(type)
		{
			case engine::GPUMemberType::Float:
				result = _members->floatResources.find(resourceName) != _members->floatResources.end();
				break;
			case engine::GPUMemberType::Vec2:
				result = _members->vec2Resources.find(resourceName) != _members->vec2Resources.end();
				break;
			case engine::GPUMemberType::Vec3:
				result = _members->vec3Resources.find(resourceName) != _members->vec3Resources.end();
				break;
			case engine::GPUMemberType::Vec4:
				result = _members->vec4Resources.find(resourceName) != _members->vec4Resources.end();
				break;
			case engine::GPUMemberType::Mat3:
				result = _members->mat3Resources.find(resourceName) != _members->mat3Resources.end();
				break;
			case engine::GPUMemberType::Mat4:
				result = _members->mat4Resources.find(resourceName) != _members->mat4Resources.end();
				break;
			default:
				FAIL("Unknown resource type");
				break;
		}
		return result;
	}

	std::vector<ShaderResourceDescription> GlobalShaderResourceStorage::collectResources() const
	{
		std::vector<ShaderResourceDescription> result;
		for(const auto& res : _members->floatResources)
		{
			result.push_back(res.second.getDescription());
		}
		for(const auto& res : _members->vec2Resources)
		{
			result.push_back(res.second.getDescription());
		}
		for(const auto& res : _members->vec3Resources)
		{
			result.push_back(res.second.getDescription());
		}
		for(const auto& res : _members->vec4Resources)
		{
			result.push_back(res.second.getDescription());
		}
		for(const auto& res : _members->mat3Resources)
		{
			result.push_back(res.second.getDescription());
		}
		for(const auto& res : _members->mat4Resources)
		{
			result.push_back(res.second.getDescription());
		}
		return result;
	}

	void GlobalShaderResourceStorage::setFloat(const std::string& resourceName, float value)
	{
		auto it = _members->floatResources.find(resourceName);
		if(_members->parentStorage && _members->parentStorage->hasResource(resourceName, GPUMemberType::Float))
		{
			ASSERT(it == _members->floatResources.end());
			_members->parentStorage->setFloat(resourceName, value);
		}
		else
		{
			ASSERT(it != _members->floatResources.end());
			it->second.setValue(value);
		}
	}

	float GlobalShaderResourceStorage::getFloat(const std::string& resourceName) const
	{
		auto it = _members->floatResources.find(resourceName);
		if(_members->parentStorage && _members->parentStorage->hasResource(resourceName, GPUMemberType::Float))
		{
			ASSERT(it == _members->floatResources.end());
			return _members->parentStorage->getFloat(resourceName);
		}
		else
		{
			ASSERT(it != _members->floatResources.end());
			return it->second.getValue();
		}
	}

	void GlobalShaderResourceStorage::setVec2(const std::string& resourceName, const glm::vec2& value)
	{
		auto it = _members->vec2Resources.find(resourceName);
		if(_members->parentStorage && _members->parentStorage->hasResource(resourceName, GPUMemberType::Vec2))
		{
			ASSERT(it == _members->vec2Resources.end());
			_members->parentStorage->setVec2(resourceName, value);
		}
		else
		{
			ASSERT(it != _members->vec2Resources.end());
			it->second.setValue(value);
		}
	}

	const glm::vec2& GlobalShaderResourceStorage::getVec2(const std::string& resourceName) const
	{
		auto it = _members->vec2Resources.find(resourceName);
		if(_members->parentStorage && _members->parentStorage->hasResource(resourceName, GPUMemberType::Vec2))
		{
			ASSERT(it == _members->vec2Resources.end());
			return _members->parentStorage->getVec2(resourceName);
		}
		else
		{
			ASSERT(it != _members->vec2Resources.end());
			return it->second.getValue();
		}
	}

	void GlobalShaderResourceStorage::setVec3(const std::string& resourceName, const glm::vec3& value)
	{
		auto it = _members->vec3Resources.find(resourceName);
		if(_members->parentStorage && _members->parentStorage->hasResource(resourceName, GPUMemberType::Vec3))
		{
			ASSERT(it == _members->vec3Resources.end());
			_members->parentStorage->setVec3(resourceName, value);
		}
		else
		{
			ASSERT(it != _members->vec3Resources.end());
			it->second.setValue(value);
		}
	}

	const glm::vec3& GlobalShaderResourceStorage::getVec3(const std::string& resourceName) const
	{
		auto it = _members->vec3Resources.find(resourceName);
		if(_members->parentStorage && _members->parentStorage->hasResource(resourceName, GPUMemberType::Vec3))
		{
			ASSERT(it == _members->vec3Resources.end());
			return _members->parentStorage->getVec3(resourceName);
		}
		else
		{
			ASSERT(it != _members->vec3Resources.end());
			return it->second.getValue();
		}
	}

	void GlobalShaderResourceStorage::setVec4(const std::string& resourceName, const glm::vec4& value)
	{
		auto it = _members->vec4Resources.find(resourceName);
		if(_members->parentStorage && _members->parentStorage->hasResource(resourceName, GPUMemberType::Vec4))
		{
			ASSERT(it == _members->vec4Resources.end());
			_members->parentStorage->setVec4(resourceName, value);
		}
		else
		{
			ASSERT(it != _members->vec4Resources.end());
			it->second.setValue(value);
		}
	}

	const glm::vec4& GlobalShaderResourceStorage::getVec4(const std::string& resourceName) const
	{
		auto it = _members->vec4Resources.find(resourceName);
		if(_members->parentStorage && _members->parentStorage->hasResource(resourceName, GPUMemberType::Vec4))
		{
			ASSERT(it == _members->vec4Resources.end());
			return _members->parentStorage->getVec4(resourceName);
		}
		else
		{
			ASSERT(it != _members->vec4Resources.end());
			return it->second.getValue();
		}
	}

	void GlobalShaderResourceStorage::setMat3(const std::string& resourceName, const glm::mat3& value)
	{
		auto it = _members->mat3Resources.find(resourceName);
		if(_members->parentStorage && _members->parentStorage->hasResource(resourceName, GPUMemberType::Mat3))
		{
			ASSERT(it == _members->mat3Resources.end());
			_members->parentStorage->setMat3(resourceName, value);
		}
		else
		{
			ASSERT(it != _members->mat3Resources.end());
			it->second.setValue(value);
		}
	}

	const glm::mat3& GlobalShaderResourceStorage::getMat3(const std::string& resourceName) const
	{
		auto it = _members->mat3Resources.find(resourceName);
		if(_members->parentStorage && _members->parentStorage->hasResource(resourceName, GPUMemberType::Mat3))
		{
			ASSERT(it == _members->mat3Resources.end());
			return _members->parentStorage->getMat3(resourceName);
		}
		else
		{
			ASSERT(it != _members->mat3Resources.end());
			return it->second.getValue();
		}
	}

	void GlobalShaderResourceStorage::setMat4(const std::string& resourceName, const glm::mat4& value)
	{
		auto it = _members->mat4Resources.find(resourceName);
		if(_members->parentStorage && _members->parentStorage->hasResource(resourceName, GPUMemberType::Mat4))
		{
			ASSERT(it == _members->mat4Resources.end());
			_members->parentStorage->setMat4(resourceName, value);
		}
		else
		{
			ASSERT(it != _members->mat4Resources.end());
			it->second.setValue(value);
		}
	}

	const glm::mat4& GlobalShaderResourceStorage::getMat4(const std::string& resourceName) const
	{
		auto it = _members->mat4Resources.find(resourceName);
		if(_members->parentStorage && _members->parentStorage->hasResource(resourceName, GPUMemberType::Mat4))
		{
			ASSERT(it == _members->mat4Resources.end());
			return _members->parentStorage->getMat4(resourceName);
		}
		else
		{
			ASSERT(it != _members->mat4Resources.end());
			return it->second.getValue();
		}
	}

	GlobalShaderResource<GPUMemberType::Float>* GlobalShaderResourceStorage::findFloatResource(const std::string& name) const
	{
		if(_members->parentStorage)
		{
			GlobalShaderResource<GPUMemberType::Float>* result = _members->parentStorage->findFloatResource(name);
			if(result)
				return result;
		}
		auto it = _members->floatResources.find(name);
		return it != _members->floatResources.end() ? &it->second : nullptr;
	}

	GlobalShaderResource<GPUMemberType::Vec2>* GlobalShaderResourceStorage::findVec2Resource(const std::string& name) const
	{
		if(_members->parentStorage)
		{
			GlobalShaderResource<GPUMemberType::Vec2>* result = _members->parentStorage->findVec2Resource(name);
			if(result)
				return result;
		}
		auto it = _members->vec2Resources.find(name);
		return it != _members->vec2Resources.end() ? &it->second : nullptr;
	}

	GlobalShaderResource<GPUMemberType::Vec3>* GlobalShaderResourceStorage::findVec3Resource(const std::string& name) const
	{
		if(_members->parentStorage)
		{
			GlobalShaderResource<GPUMemberType::Vec3>* result = _members->parentStorage->findVec3Resource(name);
			if(result)
				return result;
		}
		auto it = _members->vec3Resources.find(name);
		return it != _members->vec3Resources.end() ? &it->second : nullptr;
	}

	GlobalShaderResource<GPUMemberType::Vec4>* GlobalShaderResourceStorage::findVec4Resource(const std::string& name) const
	{
		if(_members->parentStorage)
		{
			GlobalShaderResource<GPUMemberType::Vec4>* result = _members->parentStorage->findVec4Resource(name);
			if(result)
				return result;
		}
		auto it = _members->vec4Resources.find(name);
		return it != _members->vec4Resources.end() ? &it->second : nullptr;
	}

	GlobalShaderResource<GPUMemberType::Mat3>* GlobalShaderResourceStorage::findMat3Resource(const std::string& name) const
	{
		if(_members->parentStorage)
		{
			GlobalShaderResource<GPUMemberType::Mat3>* result = _members->parentStorage->findMat3Resource(name);
			if(result)
				return result;
		}
		auto it = _members->mat3Resources.find(name);
		return it != _members->mat3Resources.end() ? &it->second : nullptr;
	}

	GlobalShaderResource<GPUMemberType::Mat4>* GlobalShaderResourceStorage::findMat4Resource(const std::string& name) const
	{
		if(_members->parentStorage)
		{
			GlobalShaderResource<GPUMemberType::Mat4>* result = _members->parentStorage->findMat4Resource(name);
			if(result)
				return result;
		}
		auto it = _members->mat4Resources.find(name);
		return it != _members->mat4Resources.end() ? &it->second : nullptr;
	}
}