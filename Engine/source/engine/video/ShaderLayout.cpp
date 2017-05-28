#include <stdafx.h>
#include <engine/video/ShaderLayout.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	struct ShaderLayoutPrivate
	{
		std::map<uint32_t, ShaderMemberType> layouts;
	};

	ShaderLayout::ShaderLayout()
		: _members(new ShaderLayoutPrivate())
	{

	}

	ShaderLayout::ShaderLayout(const ShaderLayout& o)
		: _members(o._members ? new ShaderLayoutPrivate(*o._members) : nullptr)
	{

	}

	ShaderLayout::ShaderLayout(ShaderLayout&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	ShaderLayout::~ShaderLayout()
	{
		delete _members;
		_members = nullptr;
	}

	ShaderLayout& ShaderLayout::operator=(const ShaderLayout& o)
	{
		delete _members;
		_members = new ShaderLayoutPrivate(*o._members);
		return *this;
	}

	ShaderLayout& ShaderLayout::operator=(ShaderLayout&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	bool ShaderLayout::operator==(const ShaderLayout& o) const
	{
		return _members == nullptr || o._members == nullptr || _members == o._members || _members->layouts == o._members->layouts;
	}

	void ShaderLayout::insertAttribute(ShaderMemberType type, uint32_t layout)
	{
		_members->layouts[layout] = type;
	}

	void ShaderLayout::removeAttirbute(uint32_t layout)
	{
		_members->layouts.erase(layout);
	}

	ShaderMemberType ShaderLayout::getAttribute(uint32_t layout) const
	{
		auto it = _members->layouts.find(layout);
		return it == _members->layouts.end() ? ShaderMemberType::Undef : it->second;
	}
}