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
		}
	}

	float ShaderResourceStorageProxy::getFloat(const std::string& resourceName) const
	{
		auto it = _members->floatResources.find(resourceName);
		return it != _members->floatResources.end() ? it->second : 0.0f;
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
		}
	}

	const vec2& ShaderResourceStorageProxy::getVec2(const std::string& resourceName) const
	{
		static vec2 defaultValue(0.0f);
		auto it = _members->vec2Resources.find(resourceName);
		return it != _members->vec2Resources.end() ? it->second : defaultValue;
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
		}
	}

	const vec3& ShaderResourceStorageProxy::getVec3(const std::string& resourceName) const
	{
		static vec3 defaultValue(0.0f);
		auto it = _members->vec3Resources.find(resourceName);
		return it != _members->vec3Resources.end() ? it->second : defaultValue;
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
		}
	}

	const vec4& ShaderResourceStorageProxy::getVec4(const std::string& resourceName) const
	{
		static vec4 defaultValue(0.0f);

		auto it = _members->vec4Resources.find(resourceName);
		return it != _members->vec4Resources.end() ? it->second : defaultValue;
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
		}
	}

	const mat3& ShaderResourceStorageProxy::getMat3(const std::string& resourceName) const
	{
		static mat3 defaultValue(0.0f);

		auto it = _members->mat3Resources.find(resourceName);
		return it != _members->mat3Resources.end() ? it->second : defaultValue;
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
		}
	}

	const mat4& ShaderResourceStorageProxy::getMat4(const std::string& resourceName) const
	{
		static mat4 defaultValue(0.0f);

		auto it = _members->mat4Resources.find(resourceName);
		return it != _members->mat4Resources.end() ? it->second : defaultValue;
	}
}
