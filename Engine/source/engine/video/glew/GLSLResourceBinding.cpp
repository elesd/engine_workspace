#include <stdafx.h>
#include <engine/video/glew/GLSLResourceBinding.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	namespace glew
	{
		struct GLSLResourceBindingPrivate
		{
			GLint location;
			explicit GLSLResourceBindingPrivate(GLint location)
				: location(location)
			{	}
		};

		GLSLResourceBinding::GLSLResourceBinding(GLint location)
			: _members(new GLSLResourceBindingPrivate(location))
		{

		}

		GLSLResourceBinding::~GLSLResourceBinding()
		{
			delete _members;
			_members = nullptr;
		}

		GLint GLSLResourceBinding::getLocation() const
		{
			return _members->location;
		}
	}
}