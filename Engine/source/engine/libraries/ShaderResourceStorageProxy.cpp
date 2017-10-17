#include <stdafx.h>
#include <engine/libraries/ShaderResourceStorageProxy.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/GPUTypes.h>

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
		_members->floatResources[resourceName] = v;
	}

	float ShaderResourceStorageProxy::getFloat(const std::string& resourceName) const
	{
		auto it = _members->floatResources.find(resourceName);
		return it != _members->floatResources.end() ? it->second : 0.0f;
	}

	void ShaderResourceStorageProxy::setVec2(const std::string& resourceName, const vec2& v)
	{
		_members->vec2Resources[resourceName] = v;
	}

	const vec2& ShaderResourceStorageProxy::getVec2(const std::string& resourceName) const
	{
		auto it = _members->vec2Resources.find(resourceName);
		return it != _members->vec2Resources.end() ? it->second : vec2(0.0f);
	}

	void ShaderResourceStorageProxy::setVec3(const std::string& resourceName, const vec3& v)
	{
		_members->vec3Resources[resourceName] = v;
	}

	const vec3& ShaderResourceStorageProxy::getVec3(const std::string& resourceName) const
	{
		auto it = _members->vec3Resources.find(resourceName);
		return it != _members->vec3Resources.end() ? it->second : vec3(0.0f);
	}

	void ShaderResourceStorageProxy::setVec4(const std::string& resourceName, const vec4& v)
	{
		_members->vec4Resources[resourceName] = v;
	}

	const vec4& ShaderResourceStorageProxy::getVec4(const std::string& resourceName) const
	{
		auto it = _members->vec4Resources.find(resourceName);
		return it != _members->vec4Resources.end() ? it->second : vec4(0.0f);
	}

	void ShaderResourceStorageProxy::setMat3(const std::string& resourceName, const mat3& v)
	{
		_members->mat3Resources[resourceName] = v;
	}

	const mat3& ShaderResourceStorageProxy::getMat3(const std::string& resourceName) const
	{
		auto it = _members->mat3Resources.find(resourceName);
		return it != _members->mat3Resources.end() ? it->second : mat3(0.0f);
	}

	void ShaderResourceStorageProxy::setMat4(const std::string& resourceName, const mat4& v)
	{
		_members->mat4Resources[resourceName] = v;
	}

	const mat4& ShaderResourceStorageProxy::getMat4(const std::string& resourceName) const
	{
		auto it = _members->mat4Resources.find(resourceName);
		return it != _members->mat4Resources.end() ? it->second : mat4(0.0f);
	}
}
