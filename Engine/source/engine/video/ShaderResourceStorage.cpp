#include <stdafx.h>
#include <engine/video/ShaderResourceStorage.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/ShaderResource.h>
#include <engine/video/ShaderResourceHandler.h>
#include <engine/video/ShaderResourceDescription.h>

namespace engine
{
	struct ShaderResourceStoragePrivate
	{
		std::unordered_map<std::string, ShaderResource<GPUMemberType::Float>> floatResources;
		std::unordered_map<std::string, ShaderResource<GPUMemberType::Vec2>> vec2Resources;
		std::unordered_map<std::string, ShaderResource<GPUMemberType::Vec3>> vec3Resources;
		std::unordered_map<std::string, ShaderResource<GPUMemberType::Vec4>> vec4Resources;
		std::unordered_map<std::string, ShaderResource<GPUMemberType::Mat3>> mat3Resources;
		std::unordered_map<std::string, ShaderResource<GPUMemberType::Mat4>> mat4Resources;
		std::unique_ptr<ShaderResourceHandler> resourceHandler;
		ShaderResourceStorage* parentStorage = nullptr;

		explicit ShaderResourceStoragePrivate(std::unique_ptr<ShaderResourceHandler>&& resourceHandler)
			: resourceHandler(std::move(resourceHandler))
		{
		}
		ShaderResourceStoragePrivate(std::unique_ptr<ShaderResourceHandler>&& resourceHandler, ShaderResourceStorage* parentStorage)
			: resourceHandler(std::move(resourceHandler))
			, parentStorage(parentStorage)
		{
		}

	};

	ShaderResourceStorage::ShaderResourceStorage(std::unique_ptr<ShaderResourceHandler>&& resourceHandler, ShaderResourceStorage* parentStorage)
		: _members(new ShaderResourceStoragePrivate(std::move(resourceHandler), parentStorage))
	{

	}


	ShaderResourceStorage::ShaderResourceStorage(ShaderResourceStorage&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	ShaderResourceStorage::~ShaderResourceStorage()
	{
		delete _members;
		_members = nullptr;
	}

	ShaderResourceStorage& ShaderResourceStorage::operator=(ShaderResourceStorage&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	void ShaderResourceStorage::addResource(const ShaderResourceDescription& description)
	{
		const std::string& resourceName = description.getName();
		GPUMemberType type = description.getType();
		ASSERT(hasResource(resourceName, type) == false);
		switch(type)
		{
			case engine::GPUMemberType::Float: 
			_members->floatResources.insert(std::make_pair(resourceName, ShaderResource<GPUMemberType::Float>(_members->resourceHandler.get(), std::move(description))));
			break;
			case engine::GPUMemberType::Vec2:
			_members->vec2Resources.insert(std::make_pair(resourceName, ShaderResource<GPUMemberType::Vec2>(_members->resourceHandler.get(), std::move(description))));
			break;
			case engine::GPUMemberType::Vec3:
			_members->vec3Resources.insert(std::make_pair(resourceName, ShaderResource<GPUMemberType::Vec3>(_members->resourceHandler.get(), std::move(description))));
			break;
			case engine::GPUMemberType::Vec4:
			_members->vec4Resources.insert(std::make_pair(resourceName, ShaderResource<GPUMemberType::Vec4>(_members->resourceHandler.get(), std::move(description))));
			break;
			case engine::GPUMemberType::Mat3:
			_members->mat3Resources.insert(std::make_pair(resourceName, ShaderResource<GPUMemberType::Mat3>(_members->resourceHandler.get(), std::move(description))));
			break;
			case engine::GPUMemberType::Mat4:
			_members->mat4Resources.insert(std::make_pair(resourceName, ShaderResource<GPUMemberType::Mat4>(_members->resourceHandler.get(), std::move(description))));
			break;
			default:
			FAIL("Unknown resource type");
			break;
		}
	}

	bool ShaderResourceStorage::hasResource(const std::string& resourceName, GPUMemberType type) const
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

	void ShaderResourceStorage::setFloat(const std::string resourceName, float value)
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

	float ShaderResourceStorage::getFloat(const std::string resourceName) const
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

	void ShaderResourceStorage::setVec2(const std::string resourceName, const glm::vec2& value)
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

	const glm::vec2& ShaderResourceStorage::getVec2(const std::string resourceName) const
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

	void ShaderResourceStorage::setVec3(const std::string resourceName, const glm::vec3& value)
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

	const glm::vec3& ShaderResourceStorage::getVec3(const std::string resourceName) const
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

	void ShaderResourceStorage::setVec4(const std::string resourceName, const glm::vec4& value)
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

	const glm::vec4& ShaderResourceStorage::getVec4(const std::string resourceName) const
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

	void ShaderResourceStorage::setMat3(const std::string resourceName, const glm::mat3& value)
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

	const glm::mat3& ShaderResourceStorage::getMat3(const std::string resourceName) const
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

	void ShaderResourceStorage::setMat4(const std::string resourceName, const glm::mat4& value)
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

	const glm::mat4& ShaderResourceStorage::getMat4(const std::string resourceName) const
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

	void ShaderResourceStorage::commitResources()
	{
		if(_members->parentStorage)
		{
			_members->parentStorage->commitResources();
		}
		for(auto &pair : _members->floatResources)
		{
			pair.second.commitChanges();
		}
		for(auto &pair : _members->vec2Resources)
		{
			pair.second.commitChanges();
		}
		for(auto &pair : _members->vec3Resources)
		{
			pair.second.commitChanges();
		}
		for(auto &pair : _members->vec4Resources)
		{
			pair.second.commitChanges();
		}
		for(auto &pair : _members->mat3Resources)
		{
			pair.second.commitChanges();
		}
		for(auto &pair : _members->mat4Resources)
		{
			pair.second.commitChanges();
		}
	}

}