#include <stdafx.h>
#include <engine/video/AttributeFormat.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/GPUTypes.h>

namespace engine
{
	bool ShaderLayout::operator==(const ShaderLayout& o) const
	{
		return type == o.type && name == o.name;
	}


	struct AttributeFormatPrivate
	{
		std::map<uint32_t, ShaderLayout> layouts;
	};

	AttributeFormat::AttributeFormat()
		: _members(new AttributeFormatPrivate())
	{

	}

	AttributeFormat::AttributeFormat(const AttributeFormat& o)
		: _members(o._members ? new AttributeFormatPrivate(*o._members) : nullptr)
	{

	}

	AttributeFormat::AttributeFormat(AttributeFormat&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	AttributeFormat::~AttributeFormat()
	{
		delete _members;
		_members = nullptr;
	}

	AttributeFormat& AttributeFormat::operator=(const AttributeFormat& o)
	{
		delete _members;
		_members = new AttributeFormatPrivate(*o._members);
		return *this;
	}

	AttributeFormat& AttributeFormat::operator=(AttributeFormat&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	bool AttributeFormat::operator==(const AttributeFormat& o) const
	{
		return _members == nullptr || o._members == nullptr || _members == o._members || _members->layouts == o._members->layouts;
	}

	void AttributeFormat::insertAttribute(GPUMemberType type, uint32_t layout, const std::string& name)
	{
		ASSERT(GPUMemberTypeTraits::isAttributeType(type));
		_members->layouts[layout] = ShaderLayout({type, name});
	}

	size_t AttributeFormat::getNumOfAttributes() const
	{
		return _members->layouts.size();
	}

	void AttributeFormat::removeAttirbute(uint32_t layout)
	{
		_members->layouts.erase(layout);
	}

	const ShaderLayout& AttributeFormat::getAttribute(uint32_t layout) const
	{
		static ShaderLayout errorValue({GPUMemberType::Undef, "Undef"});
		auto it = _members->layouts.find(layout);
		return it == _members->layouts.end() ? errorValue : it->second;
	}
}