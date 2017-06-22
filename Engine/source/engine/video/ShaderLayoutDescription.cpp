#include <stdafx.h>
#include <engine/video/ShaderLayoutDescription.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/GPUTypes.h>

namespace engine
{
	bool ShaderLayout::operator==(const ShaderLayout& o) const
	{
		return type == o.type && name == o.name;
	}


	struct ShaderLayoutDescriptionPrivate
	{
		std::map<uint32_t, ShaderLayout> layouts;
	};

	ShaderLayoutDescription::ShaderLayoutDescription()
		: _members(new ShaderLayoutDescriptionPrivate())
	{

	}

	ShaderLayoutDescription::ShaderLayoutDescription(const ShaderLayoutDescription& o)
		: _members(o._members ? new ShaderLayoutDescriptionPrivate(*o._members) : nullptr)
	{

	}

	ShaderLayoutDescription::ShaderLayoutDescription(ShaderLayoutDescription&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	ShaderLayoutDescription::~ShaderLayoutDescription()
	{
		delete _members;
		_members = nullptr;
	}

	ShaderLayoutDescription& ShaderLayoutDescription::operator=(const ShaderLayoutDescription& o)
	{
		delete _members;
		_members = new ShaderLayoutDescriptionPrivate(*o._members);
		return *this;
	}

	ShaderLayoutDescription& ShaderLayoutDescription::operator=(ShaderLayoutDescription&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	bool ShaderLayoutDescription::operator==(const ShaderLayoutDescription& o) const
	{
		return _members == nullptr || o._members == nullptr || _members == o._members || _members->layouts == o._members->layouts;
	}

	void ShaderLayoutDescription::insertAttribute(GPUMemberType type, uint32_t layout, const std::string& name)
	{
		ASSERT(GPUMemberTypeTraits::isAttributeType(type));
		_members->layouts[layout] = ShaderLayout({type, name});
	}

	size_t ShaderLayoutDescription::getNumOfAttributes() const
	{
		return _members->layouts.size();
	}

	void ShaderLayoutDescription::removeAttirbute(uint32_t layout)
	{
		_members->layouts.erase(layout);
	}

	const ShaderLayout& ShaderLayoutDescription::getAttribute(uint32_t layout) const
	{
		static ShaderLayout errorValue({GPUMemberType::Undef, "Undef"});
		auto it = _members->layouts.find(layout);
		return it == _members->layouts.end() ? errorValue : it->second;
	}
}