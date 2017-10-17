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
		Effect* sourceEffect;
		EffectInstancePrivate(Effect* effect)
			: sourceEffect(effect)
		{ }
	};

	EffectInstance::EffectInstance(Effect* source)
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
		return _members->sourceEffect->isCompiled();
	}

	const ShaderInstance* EffectInstance::getVertexShader() const
	{
		return _members->sourceEffect->getVertexShader();
	}

	const ShaderInstance* EffectInstance::getFragmentShader() const
	{
		return _members->sourceEffect->getFragmentShader();
	}

	ShaderInstance* EffectInstance::getVertexShader()
	{
		return _members->sourceEffect->getVertexShader();
	}

	ShaderInstance* EffectInstance::getFragmentShader()
	{
		return _members->sourceEffect->getFragmentShader();
	}

	const std::string& EffectInstance::getName() const
	{
		return _members->sourceEffect->getName();
	}

	const EffectCompilationData* EffectInstance::getCompilationData() const
	{
		return _members->sourceEffect->getCompilationData();
	}
	
	const Material* EffectInstance::getMaterial() const
	{
		_members->sourceEffect->getMaterial();
	}

	const ShaderResourceStorageProxy* EffectInstance::getResources() const
	{
		return &_members->shaderStorage;
	}

	ShaderResourceStorageProxy* EffectInstance::getResources()
	{
		return &_members->shaderStorage;
	}
}