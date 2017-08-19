#include <stdafx.h>
#include <engine/video/ShaderResourceHandler.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	struct ShaderResourceHandlerPrivate
	{
		Driver* driver = nullptr;
		explicit ShaderResourceHandlerPrivate(Driver* driver)
			: driver(driver)
		{ }

	};
	ShaderResourceHandler::ShaderResourceHandler(Driver* driver)
		:_members(new ShaderResourceHandlerPrivate(driver))
	{

	}

	ShaderResourceHandler::~ShaderResourceHandler()
	{
		delete _members;
		_members = nullptr;
	}

	void ShaderResourceHandler::commitValue(const ShaderResourceDescription& description, const ShaderResourceBinding* binding, float value)
	{
		commitValueImpl(description, binding, value);
	}

	void ShaderResourceHandler::commitValue(const ShaderResourceDescription& description, const ShaderResourceBinding* binding, const glm::vec2& value)
	{
		commitValueImpl(description, binding, value);
	}

	void ShaderResourceHandler::commitValue(const ShaderResourceDescription& description, const ShaderResourceBinding* binding, const glm::vec3& value)
	{
		commitValueImpl(description, binding, value);
	}

	void ShaderResourceHandler::commitValue(const ShaderResourceDescription& description, const ShaderResourceBinding* binding, const glm::vec4& value)
	{
		commitValueImpl(description, binding, value);
	}

	void ShaderResourceHandler::commitValue(const ShaderResourceDescription& description, const ShaderResourceBinding* binding, const glm::mat3& value)
	{
		commitValueImpl(description, binding, value);
	}

	void ShaderResourceHandler::commitValue(const ShaderResourceDescription& description, const ShaderResourceBinding* binding, const glm::mat4& value)
	{
		commitValueImpl(description, binding, value);
	}

	Driver* ShaderResourceHandler::getDriver() const
	{
		return _members->driver;
	}
}