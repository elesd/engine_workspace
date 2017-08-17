#include <stdafx.h>
#include <engine/video/ShaderResourceDescription.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/ShaderResourceBindingData.h>
#include <engine/video/GPUTypes.h>

namespace engine
{
	struct ShaderResourceDescriptionPrivate
	{
		std::string name;
		GPUMemberType type;
		ShaderResourceBindingData bindingData;
		ShaderResourceDescriptionPrivate(const std::string& name, GPUMemberType type, const ShaderResourceBindingData& bindingData)
			: name(name)
			, type(type)
			, bindingData(bindingData)
		{		}

		ShaderResourceDescriptionPrivate(const ShaderResourceDescriptionPrivate& o)
			:name(o.name)
			, type(o.type)
			, bindingData(o.bindingData)
		{		}

		ShaderResourceDescriptionPrivate& operator=(const ShaderResourceDescriptionPrivate& o)
		{
			name = o.name;
			type = o.type;
			bindingData = o.bindingData;
			return *this;
		}
	};

	ShaderResourceDescription::ShaderResourceDescription(const std::string &name, GPUMemberType type, const ShaderResourceBindingData& bindingData)
		: _members(new ShaderResourceDescriptionPrivate(name, type, bindingData))
	{

	}

	ShaderResourceDescription::~ShaderResourceDescription()
	{
		delete _members;
		_members = nullptr;
	}

	ShaderResourceDescription::ShaderResourceDescription(const ShaderResourceDescription& o)
		: _members(o._members ? new ShaderResourceDescriptionPrivate(*o._members) : nullptr)
	{

	}

	ShaderResourceDescription::ShaderResourceDescription(ShaderResourceDescription&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	ShaderResourceDescription& ShaderResourceDescription::operator=(const ShaderResourceDescription& o)
	{
		if(_members)
		{
			(*_members) = *o._members;
		}
		else
		{
			delete _members;
			_members = nullptr;
		}
		return *this;
	}

	ShaderResourceDescription& ShaderResourceDescription::operator=(ShaderResourceDescription&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	const std::string& ShaderResourceDescription::getName() const
	{
		return _members->name;
	}

	GPUMemberType ShaderResourceDescription::getType() const
	{
		return _members->type;
	}

	const ShaderResourceBindingData& ShaderResourceDescription::getResourceBindingData() const
	{
		return _members->bindingData;
	}



}