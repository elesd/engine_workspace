#include <stdafx.h>
#include <engine/render/GlobalResourceMapping.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/GlobalShaderResourceStorage.h>

namespace
{
	const std::vector<engine::GlobalResource> floatResources = {};
	const std::vector<engine::GlobalResource> vec2Resources = {};
	const std::vector<engine::GlobalResource> vec3Resources = {
		engine::GlobalResource::CameraPosition
	};
	const std::vector<engine::GlobalResource> vec4Resources = {};
	const std::vector<engine::GlobalResource> mat2Resources = {};
	const std::vector<engine::GlobalResource> mat3Resources = {};
	const std::vector<engine::GlobalResource> mat4Resources = {
		engine::GlobalResource::WorldMatrix,
		engine::GlobalResource::InvProjectionMatrix,
		engine::GlobalResource::InvProjectionViewMatrix,
		engine::GlobalResource::InvProjectionViewWorldMatrix,
		engine::GlobalResource::InvViewMatrix,
		engine::GlobalResource::InvViewWorldMatrix,
		engine::GlobalResource::InvWorldMatrix,
		engine::GlobalResource::ProjectionMatrix,
		engine::GlobalResource::ProjectionViewMatrix,
		engine::GlobalResource::ProjectionViewWorldMatrix,
		engine::GlobalResource::ViewMatrix,
		engine::GlobalResource::ViewWorldMatrix
	};

}

namespace engine
{
	struct GlobalResourceMappingPrivate
	{
		std::map<GlobalResource, std::string> mapping;
		explicit GlobalResourceMappingPrivate(const std::map<GlobalResource, std::string>& mapping)
			: mapping(mapping)
		{}
	};

	const std::vector<GlobalResource>& GlobalResourceMapping::getFloatResources()
	{
		return floatResources;
	}

	const std::vector<GlobalResource>& GlobalResourceMapping::getVec2Resources()
	{
		return vec2Resources;
	}

	const std::vector<GlobalResource>& GlobalResourceMapping::getVec3Resources()
	{
		return vec3Resources;
	}

	const std::vector<GlobalResource>& GlobalResourceMapping::getVec4Resources()
	{
		return vec4Resources;
	}

	const std::vector<GlobalResource>& GlobalResourceMapping::getMat3Resources()
	{
		return mat3Resources;
	}

	const std::vector<GlobalResource>& GlobalResourceMapping::getMat4Resources()
	{
		return mat4Resources;
	}

	GlobalResourceMapping::GlobalResourceMapping(const std::map<GlobalResource, std::string>& mapping)
		: _members(new GlobalResourceMappingPrivate(mapping))
	{

	}

	GlobalResourceMapping::~GlobalResourceMapping()
	{
		delete _members;
		_members = nullptr;
	}

	GlobalResourceMapping::GlobalResourceMapping(const GlobalResourceMapping& o)
		: _members(o._members ? new GlobalResourceMappingPrivate(*o._members) : nullptr)
	{

	}

	GlobalResourceMapping::GlobalResourceMapping(GlobalResourceMapping&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	GlobalResourceMapping& GlobalResourceMapping::operator=(const GlobalResourceMapping& o)
	{
		delete _members;
		_members = o._members ? new GlobalResourceMappingPrivate(*o._members) : nullptr;
		return *this;
	}

	GlobalResourceMapping& GlobalResourceMapping::operator=(GlobalResourceMapping&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	const std::string& GlobalResourceMapping::operator[](GlobalResource resource) const
	{
		static const std::string defautlResult = "RESOURCE_NOT_FOUND";
		auto it = _members->mapping.find(resource);
		ASSERT(it != _members->mapping.end());
		return it != _members->mapping.end() ? it->second : defautlResult;
	}

	bool GlobalResourceMapping::hasResource(GlobalResource resource) const
	{
		if(_members == nullptr || _members->mapping.empty())
			return false;
		return _members->mapping.find(resource) != _members->mapping.end();
	}

	bool GlobalResourceMapping::isInitialized() const
	{
		return _members != nullptr;
	}

}