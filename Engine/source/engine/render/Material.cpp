#include <stdafx.h>
#include <engine/render/Material.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/MaterialDescription.h>
#include <engine/render/EffectCompiler.h>
#include <engine/render/Effect.h>

#include <engine/video/Shader.h>
#include <engine/video/ShaderCompilationData.h>
#include <engine/video/ShaderCompileOptions.h>

namespace
{
	const std::string defaultEffectName = "Default";
}

namespace engine
{
	
	struct MaterialPrivate
	{
		std::unique_ptr<EffectCompiler> effectCompiler;
		std::map<std::string, std::unique_ptr<Effect>> effectCache;
		std::string name;
		std::string currentEffect;
		MaterialPrivate(const std::string& name, std::unique_ptr<EffectCompiler>&& effectCompiler)
			: name(name) 
			, effectCompiler(std::move(effectCompiler))
			, currentEffect(defaultEffectName)
		{}
	};

	Material::Material(const std::string& name, std::unique_ptr<EffectCompiler>&& effectCompiler)
		: _members(new MaterialPrivate(name, std::move(effectCompiler)))
	{
		setCurrentEffect(_members->currentEffect);
	}

	Material::Material(Material&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	Material& Material::operator=(Material&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	Material::~Material()
	{
		delete _members;
		_members = nullptr;
	}

	void Material::setCurrentEffect(const std::string& name)
	{
		_members->currentEffect = name;
		if(_members->effectCache.find(name) == _members->effectCache.end())
		{
			std::unique_ptr<Effect> effect = _members->effectCompiler->compileEffect(name);
			_members->effectCache.insert(std::make_pair(name, std::move(effect)));
		}
	}

	const std::string& Material::getCurrentEffectName() const
	{
		return _members->currentEffect;
	}

	Effect* Material::getEffect() const
	{
		auto it = _members->effectCache.find(_members->currentEffect);
		ASSERT(it != _members->effectCache.end());
		return it->second.get();
	}

	const std::string& Material::getMaterialName() const
	{
		return _members->name;
	}



	
}