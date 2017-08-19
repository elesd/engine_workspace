#include <stdafx.h>
#include <engine/video/glew/GLSLResourceHandler.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/video/glew/GLSLResourceBinding.h>

namespace engine
{
	namespace glew
	{
		GLSLResourceHandler::GLSLResourceHandler(Driver* driver) 
			: ShaderResourceHandler(driver)
		{

		}

		GLSLResourceHandler::~GLSLResourceHandler()
		{

		}

		void GLSLResourceHandler::commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, float value)
		{
			const GLSLResourceBinding* glslBinding = static_cast<const GLSLResourceBinding*>(binding);
			glUniform1f(glslBinding->getLocation(), value);
		}

		void GLSLResourceHandler::commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::vec2& value)
		{
			const GLSLResourceBinding* glslBinding = static_cast<const GLSLResourceBinding*>(binding);
			glUniform2fv(glslBinding->getLocation(), 1, &value[0]);
		}

		void GLSLResourceHandler::commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::vec3& value)
		{
			const GLSLResourceBinding* glslBinding = static_cast<const GLSLResourceBinding*>(binding);
			glUniform3fv(glslBinding->getLocation(), 1, &value[0]);
		}

		void GLSLResourceHandler::commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::vec4& value)
		{
			const GLSLResourceBinding* glslBinding = static_cast<const GLSLResourceBinding*>(binding);
			glUniform4fv(glslBinding->getLocation(), 1, &value[0]);
		}

		void GLSLResourceHandler::commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::mat3& value)
		{
			const GLSLResourceBinding* glslBinding = static_cast<const GLSLResourceBinding*>(binding);
			glUniformMatrix3fv(glslBinding->getLocation(), 1, false, &value[0][0]);
		}

		void GLSLResourceHandler::commitValueImpl(const ShaderResourceDescription&, const ShaderResourceBinding* binding, const glm::mat4& value)
		{
			const GLSLResourceBinding* glslBinding = static_cast<const GLSLResourceBinding*>(binding);
			glUniformMatrix4fv(glslBinding->getLocation(), 1, false, &value[0][0]);
		}
	}
}