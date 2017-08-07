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

	void ShaderResourceHandler::commitValue(const ShaderResourceDescription& description, float value)
	{
		commitValueImpl(description, value);
	}

	void ShaderResourceHandler::commitValue(const ShaderResourceDescription& description, const glm::vec2& value)
	{
		commitValueImpl(description, value);
	}

	void ShaderResourceHandler::commitValue(const ShaderResourceDescription& description, const glm::vec3& value)
	{
		commitValueImpl(description, value);
	}

	void ShaderResourceHandler::commitValue(const ShaderResourceDescription& description, const glm::vec4& value)
	{
		commitValueImpl(description, value);
	}

	void ShaderResourceHandler::commitValue(const ShaderResourceDescription& description, const glm::mat3& value)
	{
		commitValueImpl(description, value);
	}

	void ShaderResourceHandler::commitValue(const ShaderResourceDescription& description, const glm::mat4& value)
	{
		commitValueImpl(description, value);
	}

	std::unique_ptr<ShaderResourceHandler> ShaderResourceHandler::ShaderResourceHandler::clone() const
	{
		std::unique_ptr<ShaderResourceHandler> result = cloneImpl();
		result->_members->driver = _members->driver;
		return result;
	}

	Driver* ShaderResourceHandler::getDriver() const
	{
		return _members->driver;
	}
}