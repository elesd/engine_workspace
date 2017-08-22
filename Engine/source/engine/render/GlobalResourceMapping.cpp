#include <stdafx.h>
#include <engine/render/GlobalResourceMapping.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	struct GlobalResourceMappingPrivate
	{
		std::map<GlobalResource, std::string> mapping;
		explicit GlobalResourceMappingPrivate(const std::map<GlobalResource, std::string>& mapping)
			: mapping(mapping)
		{}
	};
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
}