#include <stdafx.h>
#include <engine/video/ShaderResourceStorage.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/constraints/NonCopyable.h>

#include <engine/video/GlobalShaderResourceStorage.h>
#include <engine/video/ShaderResource.h>
#include <engine/video/ShaderResourceHandler.h>
#include <engine/video/ShaderResourceDescription.h>
#include <engine/video/GPUTypes.h>

namespace engine
{
///////////////////////////////////////////////////////////////////////////////

	template<GPUMemberType Type>
	class ShaderResourceAttachement
		: private NonCopyable
	{
	public:
		ShaderResourceAttachement() = default;
		ShaderResourceAttachement(ShaderResource<Type>* local, GlobalShaderResource<Type>* global);

		ShaderResourceAttachement(ShaderResourceAttachement&& o);
		
		~ShaderResourceAttachement();

		ShaderResourceAttachement& operator=(ShaderResourceAttachement&& o);

	private:
		ShaderResource<Type>* _localResource = nullptr;
		GlobalShaderResource<Type>* _globalResource = nullptr;
	};

///////////////////////////////////////////////////////////////////////////////

	template<GPUMemberType Type>
	ShaderResourceAttachement<Type>::ShaderResourceAttachement(ShaderResource<Type>* local, GlobalShaderResource<Type>* global)
		: _localResource(local)
		, _globalResource(global)
	{
		_globalResource->attachResource(_localResource);
	}

	template<GPUMemberType Type>
	ShaderResourceAttachement<Type>::ShaderResourceAttachement(ShaderResourceAttachement&& o)
		: _localResource(o._localResource)
		, _globalResource(o._globalResource)
	{
		o._localResource = nullptr;
		o._globalResource = nullptr;
	}
	
	template<GPUMemberType Type>
	ShaderResourceAttachement<Type>::~ShaderResourceAttachement()
	{
		if(_globalResource)
		{
			_globalResource->detachResource(_localResource);
		}
	}
	
	template<GPUMemberType Type>
	ShaderResourceAttachement<Type>& ShaderResourceAttachement<Type>::operator=(ShaderResourceAttachement<Type>&& o)
	{
		_localResource = o._localResource;
		_globalResource = o._globalResource;
		o._localResource = nullptr;
		o._globalResource = nullptr;
	}

///////////////////////////////////////////////////////////////////////////////

	struct ShaderResourceStoragePrivate
	{
		std::unordered_map<std::string, ShaderResource<GPUMemberType::Float>> floatResources;
		std::unordered_map<std::string, ShaderResource<GPUMemberType::Vec2>> vec2Resources;
		std::unordered_map<std::string, ShaderResource<GPUMemberType::Vec3>> vec3Resources;
		std::unordered_map<std::string, ShaderResource<GPUMemberType::Vec4>> vec4Resources;
		std::unordered_map<std::string, ShaderResource<GPUMemberType::Mat3>> mat3Resources;
		std::unordered_map<std::string, ShaderResource<GPUMemberType::Mat4>> mat4Resources;
		
		std::vector<ShaderResourceAttachement<GPUMemberType::Float>> floatAttachements;
		std::vector<ShaderResourceAttachement<GPUMemberType::Vec2>> vec2Attachements;
		std::vector<ShaderResourceAttachement<GPUMemberType::Vec3>> vec3Attachements;
		std::vector<ShaderResourceAttachement<GPUMemberType::Vec4>> vec4Attachements;
		std::vector<ShaderResourceAttachement<GPUMemberType::Mat3>> mat3Attachements;
		std::vector<ShaderResourceAttachement<GPUMemberType::Mat4>> mat4Attachements;

		std::unique_ptr<ShaderResourceHandler> resourceHandler;
		GlobalShaderResourceStorage* parentStorage = nullptr;

		explicit ShaderResourceStoragePrivate(std::unique_ptr<ShaderResourceHandler>&& resourceHandler)
			: resourceHandler(std::move(resourceHandler))
		{
		}
		ShaderResourceStoragePrivate(std::unique_ptr<ShaderResourceHandler>&& resourceHandler, GlobalShaderResourceStorage* parentStorage)
			: resourceHandler(std::move(resourceHandler))
			, parentStorage(parentStorage)
		{
		}

	};

///////////////////////////////////////////////////////////////////////////////

	ShaderResourceStorage::ShaderResourceStorage(std::unique_ptr<ShaderResourceHandler>&& resourceHandler, GlobalShaderResourceStorage* parentStorage)
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
				if(_members->parentStorage)
				{
					GlobalShaderResource<GPUMemberType::Float> *globalResource = _members->parentStorage->findFloatResource(resourceName);
					if(globalResource)
					{
						_members->floatAttachements.push_back(ShaderResourceAttachement<GPUMemberType::Float>(&_members->floatResources.find(resourceName)->second, globalResource));
					}
				}
			break;
			case engine::GPUMemberType::Vec2:
				_members->vec2Resources.insert(std::make_pair(resourceName, ShaderResource<GPUMemberType::Vec2>(_members->resourceHandler.get(), std::move(description))));
				if(_members->parentStorage)
				{
					GlobalShaderResource<GPUMemberType::Vec2> *globalResource = _members->parentStorage->findVec2Resource(resourceName);
					if(globalResource)
					{
						_members->vec2Attachements.push_back(ShaderResourceAttachement<GPUMemberType::Vec2>(&_members->vec2Resources.find(resourceName)->second, globalResource));
					}
				}
				break;
			case engine::GPUMemberType::Vec3:
				_members->vec3Resources.insert(std::make_pair(resourceName, ShaderResource<GPUMemberType::Vec3>(_members->resourceHandler.get(), std::move(description))));
				if(_members->parentStorage)
				{
					GlobalShaderResource<GPUMemberType::Vec3> *globalResource = _members->parentStorage->findVec3Resource(resourceName);
					if(globalResource)
					{
						_members->vec3Attachements.push_back(ShaderResourceAttachement<GPUMemberType::Vec3>(&_members->vec3Resources.find(resourceName)->second, globalResource));
					}
				}
				break;
			case engine::GPUMemberType::Vec4:
				_members->vec4Resources.insert(std::make_pair(resourceName, ShaderResource<GPUMemberType::Vec4>(_members->resourceHandler.get(), std::move(description))));
				if(_members->parentStorage)
				{
					GlobalShaderResource<GPUMemberType::Vec4> *globalResource = _members->parentStorage->findVec4Resource(resourceName);
					if(globalResource)
					{
						_members->vec4Attachements.push_back(ShaderResourceAttachement<GPUMemberType::Vec4>(&_members->vec4Resources.find(resourceName)->second, globalResource));
					}
				}
				break;
			case engine::GPUMemberType::Mat3:
				_members->mat3Resources.insert(std::make_pair(resourceName, ShaderResource<GPUMemberType::Mat3>(_members->resourceHandler.get(), std::move(description))));
				if(_members->parentStorage)
				{
					GlobalShaderResource<GPUMemberType::Mat3> *globalResource = _members->parentStorage->findMat3Resource(resourceName);
					if(globalResource)
					{
						_members->mat3Attachements.push_back(ShaderResourceAttachement<GPUMemberType::Mat3>(&_members->mat3Resources.find(resourceName)->second, globalResource));
					}
				}
				break;
			case engine::GPUMemberType::Mat4:
				_members->mat4Resources.insert(std::make_pair(resourceName, ShaderResource<GPUMemberType::Mat4>(_members->resourceHandler.get(), std::move(description))));
				if(_members->parentStorage)
				{
					GlobalShaderResource<GPUMemberType::Mat4> *globalResource = _members->parentStorage->findMat4Resource(resourceName);
					if(globalResource)
					{
						_members->mat4Attachements.push_back(ShaderResourceAttachement<GPUMemberType::Mat4>(&_members->mat4Resources.find(resourceName)->second, globalResource));
					}
				}
				break;
			default:
				FAIL("Unknown resource type");
				break;
		}
	}

	bool ShaderResourceStorage::hasResource(const std::string& resourceName, GPUMemberType type) const
	{
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

	std::vector<ShaderResourceDescription> ShaderResourceStorage::collectDescriptions() const
	{
		std::vector<ShaderResourceDescription> descriptions;
		for(const auto& res : _members->floatResources)
		{
			descriptions.push_back(res.second.getDescription());
		}
		for(const auto& res : _members->vec2Resources)
		{
			descriptions.push_back(res.second.getDescription());
		}
		for(const auto& res : _members->vec3Resources)
		{
			descriptions.push_back(res.second.getDescription());
		}
		for(const auto& res : _members->vec4Resources)
		{
			descriptions.push_back(res.second.getDescription());
		}
		for(const auto& res : _members->mat3Resources)
		{
			descriptions.push_back(res.second.getDescription());
		}
		for(const auto& res : _members->mat4Resources)
		{
			descriptions.push_back(res.second.getDescription());
		}

		return descriptions;
	}

	void ShaderResourceStorage::setResourceBinding(std::vector<std::pair<ShaderResourceDescription, std::unique_ptr<ShaderResourceBinding>>>&& resourceBinding)
	{
		for(std::pair<ShaderResourceDescription, std::unique_ptr<ShaderResourceBinding>>& pair : resourceBinding)
		{
			GPUMemberType type = pair.first.getType();
			const std::string resourceName = pair.first.getName();
			switch(type)
			{
				case GPUMemberType::Float:
				{
					auto& resource = _members->floatResources.at(resourceName);
					resource.bind(std::move(pair.second));
				}
					break;
				case GPUMemberType::Vec2:
				{
					auto& resource = _members->vec2Resources.at(resourceName);
					resource.bind(std::move(pair.second));
				}
					break;
				case GPUMemberType::Vec3:
				{
					auto& resource = _members->vec3Resources.at(resourceName);
					resource.bind(std::move(pair.second));
				}
					break;
				case GPUMemberType::Vec4:
				{
					auto& resource = _members->vec4Resources.at(resourceName);
					resource.bind(std::move(pair.second));
				}
					break;
				case GPUMemberType::Mat3:
				{
					auto& resource = _members->mat3Resources.at(resourceName);
					resource.bind(std::move(pair.second));
				}
					break;
				case GPUMemberType::Mat4:
				{
					auto& resource = _members->mat4Resources.at(resourceName);
					resource.bind(std::move(pair.second));
				}
					break;
				case GPUMemberType::Undef:
				default:
					break;
			}
		}
		ASSERT(checkResourceBinding());
	}

	void ShaderResourceStorage::setFloat(const std::string& resourceName, float value)
	{
		auto it = _members->floatResources.find(resourceName);

		ASSERT(it != _members->floatResources.end());
		it->second.setValue(value);
	}

	float ShaderResourceStorage::getFloat(const std::string& resourceName) const
	{
		auto it = _members->floatResources.find(resourceName);
		ASSERT(it != _members->floatResources.end());
		return it->second.getValue();
	}

	void ShaderResourceStorage::setVec2(const std::string& resourceName, const glm::vec2& value)
	{
		auto it = _members->vec2Resources.find(resourceName);
		ASSERT(it != _members->vec2Resources.end());
		it->second.setValue(value);
	}

	const glm::vec2& ShaderResourceStorage::getVec2(const std::string& resourceName) const
	{
		auto it = _members->vec2Resources.find(resourceName);
		ASSERT(it != _members->vec2Resources.end());
		return it->second.getValue();
	}

	void ShaderResourceStorage::setVec3(const std::string& resourceName, const glm::vec3& value)
	{
		auto it = _members->vec3Resources.find(resourceName);
		ASSERT(it != _members->vec3Resources.end());
		it->second.setValue(value);
	}

	const glm::vec3& ShaderResourceStorage::getVec3(const std::string& resourceName) const
	{
		auto it = _members->vec3Resources.find(resourceName);
		ASSERT(it != _members->vec3Resources.end());
		return it->second.getValue();
	}

	void ShaderResourceStorage::setVec4(const std::string& resourceName, const glm::vec4& value)
	{
		auto it = _members->vec4Resources.find(resourceName);
		ASSERT(it != _members->vec4Resources.end());
		it->second.setValue(value);
	}

	const glm::vec4& ShaderResourceStorage::getVec4(const std::string& resourceName) const
	{
		auto it = _members->vec4Resources.find(resourceName);
		ASSERT(it != _members->vec4Resources.end());
		return it->second.getValue();
	}

	void ShaderResourceStorage::setMat3(const std::string& resourceName, const glm::mat3& value)
	{
		auto it = _members->mat3Resources.find(resourceName);
		ASSERT(it != _members->mat3Resources.end());
		it->second.setValue(value);
	}

	const glm::mat3& ShaderResourceStorage::getMat3(const std::string& resourceName) const
	{
		auto it = _members->mat3Resources.find(resourceName);
		ASSERT(it != _members->mat3Resources.end());
		return it->second.getValue();
	}

	void ShaderResourceStorage::setMat4(const std::string& resourceName, const glm::mat4& value)
	{
		auto it = _members->mat4Resources.find(resourceName);
		ASSERT(it != _members->mat4Resources.end());
		it->second.setValue(value);
	}

	const glm::mat4& ShaderResourceStorage::getMat4(const std::string& resourceName) const
	{
		auto it = _members->mat4Resources.find(resourceName);
		ASSERT(it != _members->mat4Resources.end());
		return it->second.getValue();
	}

	void ShaderResourceStorage::commitResources()
	{
		if(_members->parentStorage)
		{
			_members->parentStorage->calculateAggregatedResources();
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

	bool ShaderResourceStorage::checkResourceBinding() const
	{
		bool result = true;
		for(const auto& resourcePair : _members->floatResources)
		{
			result = result && resourcePair.second.isBound();
			ASSERT(result && "Not bounded resource!");
		}
		for(const auto& resourcePair : _members->vec2Resources)
		{
			result = result && resourcePair.second.isBound();
			ASSERT(result && "Not bounded resource!");
		}
		for(const auto& resourcePair : _members->vec3Resources)
		{
			result = result && resourcePair.second.isBound();
			ASSERT(result && "Not bounded resource!");
		}
		for(const auto& resourcePair : _members->vec4Resources)
		{
			result = result && resourcePair.second.isBound();
			ASSERT(result && "Not bounded resource!");
		}
		for(const auto& resourcePair : _members->mat3Resources)
		{
			result = result && resourcePair.second.isBound();
			ASSERT(result && "Not bounded resource!");
		}
		for(const auto& resourcePair : _members->mat4Resources)
		{
			result = result && resourcePair.second.isBound();
			ASSERT(result && "Not bounded resource!");
		}
		return result;
	}

}
