#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	class Driver;
	class ShaderResourceDescription;
	class ShaderResourceBinding;

	class ShaderResourceHandler
		: private NonCopyable
		, private NonMoveable
	{
	public:
		explicit ShaderResourceHandler(Driver* driver);
		virtual ~ShaderResourceHandler();

		void commitValue(const ShaderResourceDescription&, const ShaderResourceBinding* binding, float);
		void commitValue(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::vec2&);
		void commitValue(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::vec3&);
		void commitValue(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::vec4&);
		void commitValue(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::mat3&);
		void commitValue(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::mat4&);
		std::unique_ptr<ShaderResourceHandler> clone() const;
	protected:
		Driver* getDriver() const;

	private:
		virtual void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, float) = 0;
		virtual void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::vec2&) = 0;
		virtual void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::vec3&) = 0;
		virtual void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::vec4&) = 0;
		virtual void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::mat3&) = 0;
		virtual void commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::mat4&) = 0;
		virtual std::unique_ptr<ShaderResourceHandler> cloneImpl() const = 0;
	private:
		struct ShaderResourceHandlerPrivate* _members = nullptr;
	};
}