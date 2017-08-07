#include <stdafx.h>
#include <engine/video/EffectDescription.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/ShaderResourceDescription.h>
#include <engine/video/ShaderCompileOptions.h>

namespace engine
{
	struct EffectDescriptionPrivate
	{
		std::string name;
		ShaderCompileOptions options;
		std::vector<ShaderResourceDescription> resourceDescriptions;
		EffectDescriptionPrivate(const std::string& name, const ShaderCompileOptions& options)
			: name(name)
			, options(options)
		{ }
	};

	EffectDescription::EffectDescription(const std::string& name, const ShaderCompileOptions& options)
		: _members(new EffectDescriptionPrivate(name, options))
	{

	}

	EffectDescription::~EffectDescription()
	{
		delete _members;
		_members = nullptr;
	}
	
	EffectDescription::EffectDescription(const EffectDescription& o)
		: _members(o._members ? new EffectDescriptionPrivate(*o._members) : nullptr)
	{

	}

	EffectDescription::EffectDescription(EffectDescription&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	EffectDescription& EffectDescription::operator=(const EffectDescription& o)
	{
		if(o._members)
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

	EffectDescription& EffectDescription::operator=(EffectDescription&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	void EffectDescription::addParameter(const ShaderResourceDescription &description)
	{
		_members->resourceDescriptions.push_back(description);
	}

	const std::vector<ShaderResourceDescription>& EffectDescription::getParameters() const
	{
		return _members->resourceDescriptions;
	}

	const std::string& EffectDescription::getName() const
	{
		return _members->name;
	}

	const ShaderCompileOptions& EffectDescription::getOptions() const
	{
		return _members->options;
	}

	ShaderCompileOptions& EffectDescription::getOptions() 
	{
		return _members->options;
	}
}