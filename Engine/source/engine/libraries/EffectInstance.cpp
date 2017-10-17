#include <stdafx.h>
#include <engine/libraries/EffectInstance.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/Effect.h>

#include <engine/libraries/ShaderResourceStorageProxy.h>

namespace engine
{
	struct EffectInstancePrivate
	{
		ShaderResourceStorageProxy shaderStorage;
		// TODO Replace shared_ptr
		std::shared_ptr<Effect> origin;
		EffectInstancePrivate(std::shared_ptr<Effect> effect)
			: origin(effect)
		{ }
	};

	EffectInstance::EffectInstance(std::shared_ptr<Effect> source)
		: _members(new EffectInstancePrivate(source))
	{

	}

	EffectInstance::~EffectInstance()
	{
		delete _members;
		_members = nullptr;
	}

	bool EffectInstance::isCompiled() const
	{
		return _members->origin->isCompiled();
	}

	const ShaderInstance* EffectInstance::getVertexShader() const
	{
		return _members->origin->getVertexShader();
	}

	const ShaderInstance* EffectInstance::getFragmentShader() const
	{
		return _members->origin->getFragmentShader();
	}

	ShaderInstance* EffectInstance::getVertexShader()
	{
		return _members->origin->getVertexShader();
	}

	ShaderInstance* EffectInstance::getFragmentShader()
	{
		return _members->origin->getFragmentShader();
	}

	const std::string& EffectInstance::getName() const
	{
		return _members->origin->getName();
	}

	const EffectCompilationData* EffectInstance::getCompilationData() const
	{
		return _members->origin->getCompilationData();
	}

	const ShaderResourceStorageProxy* EffectInstance::getResources() const
	{
		return &_members->shaderStorage;
	}

	ShaderResourceStorageProxy* EffectInstance::getResources()
	{
		return &_members->shaderStorage;
	}

	GuardedObject<Effect*> EffectInstance::lockEffect()
	{
		return _members->origin->lock();
	}

	GuardedObject<const Effect*> EffectInstance::lockEffect() const
	{
		return static_cast<const Effect*>(_members->origin.get())->lock();
	}

}