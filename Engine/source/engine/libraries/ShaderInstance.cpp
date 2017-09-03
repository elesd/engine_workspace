#include <stdafx.h>
#include <engine/libraries/ShaderInstance.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/Shader.h>

namespace engine
{
	struct ShaderInstancePrivate
	{
		std::shared_ptr<Shader> origin;
		ShaderInstancePrivate(const std::shared_ptr<Shader>& shaderOrigin)
			: origin(shaderOrigin)
		{ }
	};

	ShaderInstance::ShaderInstance(const std::shared_ptr<Shader>& shaderOrigin)
		: _members(new ShaderInstancePrivate(shaderOrigin))
	{

	}

	ShaderInstance::~ShaderInstance()
	{
		delete _members;
		_members = nullptr;
	}

	bool ShaderInstance::isInitialized() const
	{
		// no lock neccessary
		return _members->origin->isInitialized();
	}

	bool ShaderInstance::operator==(const ShaderInstance& o) const
	{
		return o._members->origin == _members->origin;
	}

	bool ShaderInstance::isCompiled(const std::string& technique)
	{
		return _members->origin->lock()->isCompiled(technique);
	}

	ShaderType ShaderInstance::getShaderType() const
	{
		// no lock neccessary
		return _members->origin->getShaderType();
	}

	const std::string& ShaderInstance::getMainFunctionName()
	{
		ASSERT(isInitialized());
		// The question has sense if it is initialized, but in this case there is no need extra lock
		return _members->origin->getMainFunctionName();
	}

	bool ShaderInstance::isSame(const std::string& technique, const ShaderInstance& o) const
	{
		if(_members->origin == o._members->origin)
			return true;

		GuardedObject<Shader*> guardedThis = _members->origin->lock();
		GuardedObject<const Shader*> guardedO = std::move(o.lockShader());
		return guardedThis->isSame(technique, **guardedO);
	}

	const std::string& ShaderInstance::getCode() const
	{
		ASSERT(isInitialized());
		return _members->origin->getCode();
	}

	GuardedObject<Shader*> ShaderInstance::lockShader()
	{
		return _members->origin->lock();
	}

	GuardedObject<const Shader*> ShaderInstance::lockShader() const
	{
		return static_cast<const Shader*>(_members->origin.get())->lock();
	}

}