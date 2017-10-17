#include <stdafx.h>
#include <engine/libraries/MaterialInstance.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/libraries/EffectInstance.h>
#include <engine/libraries/MaterialResourceHandler.h>

#include <engine/video/Effect.h>
#include <engine/video/Material.h>

namespace engine
{
	struct MaterialInstancePrivate
	{
		// TODO replace shared_ptr
		std::shared_ptr<Material> origin;
		EffectInstance* currentEffect = nullptr;
		std::unique_ptr<MaterialResourceHandler> resourceHandler;
		std::map<std::string, std::unique_ptr<EffectInstance>> effects;
		explicit MaterialInstancePrivate(std::shared_ptr<Material> material)
			: origin(material)
		{
			
		}
	};

	MaterialInstance::MaterialInstance(std::shared_ptr<Material> origin)
		: _members(new MaterialInstancePrivate(origin))
	{
		std::unique_ptr<EffectInstance> defaultEffect = origin->getEffect(Material::defaultEffectName);
		_members->currentEffect = defaultEffect.get();
		// TODO instantiate all the compiled effects!
		_members->effects[Material::defaultEffectName] = std::move(defaultEffect);
		_members->resourceHandler.reset(new MaterialResourceHandler(this));
	}

	MaterialInstance::~MaterialInstance()
	{
		delete _members;
		_members = nullptr;
	}

	const std::string& MaterialInstance::getMaterialName() const
	{
		return _members->origin->getMaterialName();
	}

	void MaterialInstance::setCurrentEffect(const std::string& name)
	{
		// TODO Handle effect not compiled yet.
		std::unique_ptr<EffectInstance> effect = _members->origin->getEffect(Material::defaultEffectName);
		_members->currentEffect = effect.get();
		_members->effects[name] = std::move(effect);
	}

	EffectInstance* MaterialInstance::getCurrentEffect() const
	{
		return _members->currentEffect;
	}

	const AttributeFormat& MaterialInstance::getAttributeFormat() const
	{
		return _members->origin->getAttributeFormat();
	}

	const MaterialDescription& MaterialInstance::getDescription() const
	{
		return _members->origin->getDescription();
	}

	MaterialResourceHandler* MaterialInstance::getResourceHandler()
	{
		return _members->resourceHandler.get();
	}

	std::map<std::string, EffectInstance*> MaterialInstance::collectAllEffects()
	{
		std::map<std::string, EffectInstance*> result;
		for(const auto& pair : _members->effects)
		{
			result[pair.first] = pair.second.get();
		}
		return result;
	}

	std::map<std::string, const EffectInstance*> MaterialInstance::collectAllEffects() const
	{
		std::map<std::string, const EffectInstance*> result;
		for(const auto& pair : _members->effects)
		{
			result[pair.first] = pair.second.get();
		}
		return result;
	}


}