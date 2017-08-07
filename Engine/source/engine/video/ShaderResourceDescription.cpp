#include <stdafx.h>
#include <engine/video/ShaderResourceDescription.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/ShaderResourceBinding.h>
#include <engine/video/GPUTypes.h>

namespace engine
{
	struct ShaderResourceDescriptionPrivate
	{
		std::string name;
		GPUMemberType type;
		std::unique_ptr<ShaderResourceBinding> bindingData;
		ShaderResourceDescriptionPrivate(const std::string& name, GPUMemberType type, std::unique_ptr<ShaderResourceBinding>&& bindingData)
			: name(name)
			, type(type)
			, bindingData(std::move(bindingData))
		{		}

		ShaderResourceDescriptionPrivate(const ShaderResourceDescriptionPrivate& o)
			:name(o.name)
			, type(o.type)
			, bindingData(o.bindingData->clone())
		{		}

		ShaderResourceDescriptionPrivate& operator=(const ShaderResourceDescriptionPrivate& o)
		{
			name = o.name;
			type = o.type;
			bindingData = o.bindingData->clone();
			return *this;
		}
	};

	ShaderResourceDescription::ShaderResourceDescription(const std::string &name, GPUMemberType type, std::unique_ptr<ShaderResourceBinding>&& bindingData)
		: _members(new ShaderResourceDescriptionPrivate(name, type, std::move(bindingData)))
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

	const ShaderResourceBinding* ShaderResourceDescription::getResourceBinding() const
	{
		return _members->bindingData.get();
	}



}