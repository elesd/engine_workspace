#include <stdafx.h>
#include <engine/libraries/ShaderResourceStorageProxy.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/GPUTypes.h>
#include <engine/utils/Math.h>

namespace engine
{
	
	struct ShaderResourceStorageProxyPrivate
	{
		std::unordered_map<std::string, GPUMemberTypeTraits<GPUMemberType::Float>::ValueType> floatResources;
		std::unordered_map<std::string, GPUMemberTypeTraits<GPUMemberType::Vec2>::ValueType> vec2Resources;
		std::unordered_map<std::string, GPUMemberTypeTraits<GPUMemberType::Vec3>::ValueType> vec3Resources;
		std::unordered_map<std::string, GPUMemberTypeTraits<GPUMemberType::Vec4>::ValueType> vec4Resources;
		std::unordered_map<std::string, GPUMemberTypeTraits<GPUMemberType::Mat3>::ValueType> mat3Resources;
		std::unordered_map<std::string, GPUMemberTypeTraits<GPUMemberType::Mat4>::ValueType> mat4Resources;
		std::unordered_map<std::string, bool> floatChanges;
		std::unordered_map<std::string, bool> vec2Changes;
		std::unordered_map<std::string, bool> vec3Changes;
		std::unordered_map<std::string, bool> vec4Changes;
		std::unordered_map<std::string, bool> mat3Changes;
		std::unordered_map<std::string, bool> mat4Changes;
	};

	ShaderResourceStorageProxy::ShaderResourceStorageProxy()
		: _members(new ShaderResourceStorageProxyPrivate())
	{

	}

	ShaderResourceStorageProxy::~ShaderResourceStorageProxy()
	{
		delete _members;
		_members = nullptr;
	}

	ShaderResourceStorageProxy::ShaderResourceStorageProxy(const ShaderResourceStorageProxy& o)
		: _members(o._members == nullptr ? nullptr : new ShaderResourceStorageProxyPrivate(*o._members))
	{
	}

	ShaderResourceStorageProxy::ShaderResourceStorageProxy(ShaderResourceStorageProxy&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	ShaderResourceStorageProxy ShaderResourceStorageProxy::operator=(const ShaderResourceStorageProxy& o)
	{
		delete _members;
		_members = o._members == nullptr ? nullptr : new ShaderResourceStorageProxyPrivate(*o._members);
		return *this;
	}

	ShaderResourceStorageProxy ShaderResourceStorageProxy::operator=(ShaderResourceStorageProxy&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	void ShaderResourceStorageProxy::setFloat(const std::string& resourceName, float v)
	{
		auto it = _members->floatResources.find(resourceName);
		if(math::notEquals(v, it->second, glm::epsilon<float>()))
		{
			if(it != _members->floatResources.end())
			{
				it->second = v;
			}
			else
			{
				_members->floatResources.insert(std::make_pair(resourceName, v));
			}
			_members->floatChanges[resourceName] = true;
		}
	}

	float ShaderResourceStorageProxy::getFloat(const std::string& resourceName) const
	{
		auto it = _members->floatResources.find(resourceName);
		return it != _members->floatResources.end() ? it->second : 0.0f;
	}

	std::vector<std::pair<std::string, float>> ShaderResourceStorageProxy::clearChangesInFloats()
	{
		std::vector<std::pair<std::string, float>> result;
		for(const auto &pair : _members->floatChanges)
		{
			if(pair.second)
			{
				result.push_back(std::make_pair(pair.first, _members->floatResources[pair.first]));
			}
		}
		_members->floatChanges.clear();
		return result;
	}

	void ShaderResourceStorageProxy::setVec2(const std::string& resourceName, const vec2& v)
	{
		auto it = _members->vec2Resources.find(resourceName);
		if(math::notEquals(v, it->second, glm::epsilon<float>()))
		{
			if(it != _members->vec2Resources.end())
			{
				it->second = v;
			}
			else
			{
				_members->vec2Resources.insert(std::make_pair(resourceName, v));
			}
			_members->vec2Changes[resourceName] = true;
		}
	}

	const vec2& ShaderResourceStorageProxy::getVec2(const std::string& resourceName) const
	{
		auto it = _members->vec2Resources.find(resourceName);
		return it != _members->vec2Resources.end() ? it->second : vec2(0.0f);
	}

	std::vector<std::pair<std::string, vec2>> ShaderResourceStorageProxy::clearChangesInVec2()
	{
		std::vector<std::pair<std::string, vec2>> result;
		for(const auto &pair : _members->vec2Changes)
		{
			if(pair.second)
			{
				result.push_back(std::make_pair(pair.first, _members->vec2Resources[pair.first]));
			}
		}
		_members->vec2Changes.clear();
		return result;
	}

	void ShaderResourceStorageProxy::setVec3(const std::string& resourceName, const vec3& v)
	{
		auto it = _members->vec3Resources.find(resourceName);
		if(math::notEquals(v, it->second, glm::epsilon<float>()))
		{
			if(it != _members->vec3Resources.end())
			{
				it->second = v;
			}
			else
			{
				_members->vec3Resources.insert(std::make_pair(resourceName, v));
			}
			_members->vec3Changes[resourceName] = true;
		}
	}

	const vec3& ShaderResourceStorageProxy::getVec3(const std::string& resourceName) const
	{
		auto it = _members->vec3Resources.find(resourceName);
		return it != _members->vec3Resources.end() ? it->second : vec3(0.0f);
	}

	std::vector<std::pair<std::string, vec3>> ShaderResourceStorageProxy::clearChangesInVec3()
	{
		std::vector<std::pair<std::string, vec3>> result;
		for(const auto &pair : _members->vec3Changes)
		{
			if(pair.second)
			{
				result.push_back(std::make_pair(pair.first, _members->vec3Resources[pair.first]));
			}
		}
		_members->vec3Changes.clear();
		return result;
	}

	void ShaderResourceStorageProxy::setVec4(const std::string& resourceName, const vec4& v)
	{
		auto it = _members->vec4Resources.find(resourceName);
		if(math::notEquals(v, it->second, glm::epsilon<float>()))
		{
			if(it != _members->vec4Resources.end())
			{
				it->second = v;
			}
			else
			{
				_members->vec4Resources.insert(std::make_pair(resourceName, v));
			}
			_members->vec4Changes[resourceName] = true;
		}
	}

	const vec4& ShaderResourceStorageProxy::getVec4(const std::string& resourceName) const
	{
		auto it = _members->vec4Resources.find(resourceName);
		return it != _members->vec4Resources.end() ? it->second : vec4(0.0f);
	}

	std::vector<std::pair<std::string, vec4>> ShaderResourceStorageProxy::clearChangesInVec4()
	{
		std::vector<std::pair<std::string, vec4>> result;
		for(const auto &pair : _members->vec4Changes)
		{
			if(pair.second)
			{
				result.push_back(std::make_pair(pair.first, _members->vec4Resources[pair.first]));
			}
		}
		_members->vec4Changes.clear();
		return result;
	}

	void ShaderResourceStorageProxy::setMat3(const std::string& resourceName, const mat3& v)
	{
		auto it = _members->mat3Resources.find(resourceName);
		if(math::notEquals(v, it->second, glm::epsilon<float>()))
		{
			if(it != _members->mat3Resources.end())
			{
				it->second = v;
			}
			else
			{
				_members->mat3Resources.insert(std::make_pair(resourceName, v));
			}
			_members->mat3Changes[resourceName] = true;
		}
	}

	const mat3& ShaderResourceStorageProxy::getMat3(const std::string& resourceName) const
	{
		auto it = _members->mat3Resources.find(resourceName);
		return it != _members->mat3Resources.end() ? it->second : mat3(0.0f);
	}

	std::vector<std::pair<std::string, mat3>> ShaderResourceStorageProxy::clearChangesInMat3()
	{
		std::vector<std::pair<std::string, mat3>> result;
		for(const auto &pair : _members->mat3Changes)
		{
			if(pair.second)
			{
				result.push_back(std::make_pair(pair.first, _members->mat3Resources[pair.first]));
			}
		}
		_members->mat3Changes.clear();
		return result;
	}

	void ShaderResourceStorageProxy::setMat4(const std::string& resourceName, const mat4& v)
	{
		auto it = _members->mat4Resources.find(resourceName);
		if(math::notEquals(v, it->second, glm::epsilon<float>()))
		{
			if(it != _members->mat4Resources.end())
			{
				it->second = v;
			}
			else
			{
				_members->mat4Resources.insert(std::make_pair(resourceName, v));
			}
			_members->mat4Changes[resourceName] = true;
		}
	}

	const mat4& ShaderResourceStorageProxy::getMat4(const std::string& resourceName) const
	{
		auto it = _members->mat4Resources.find(resourceName);
		return it != _members->mat4Resources.end() ? it->second : mat4(0.0f);
	}

	std::vector<std::pair<std::string, mat4>> ShaderResourceStorageProxy::clearChangesInMat4()
	{
		std::vector<std::pair<std::string, mat4>> result;
		for(const auto &pair : _members->mat4Changes)
		{
			if(pair.second)
			{
				result.push_back(std::make_pair(pair.first, _members->mat4Resources[pair.first]));
			}
		}
		_members->mat4Changes.clear();
		return result;
	}
}
