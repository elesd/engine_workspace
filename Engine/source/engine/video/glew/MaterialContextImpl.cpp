#include <stdafx.h>
#include <engine/video/glew/MaterialContextImpl.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	namespace glew
	{
		struct MaterialContextImplPrivate
		{
			GLuint vao;

			explicit MaterialContextImplPrivate(GLuint vao)
				: vao(vao)
			{ }
		};

		MaterialContextImpl::MaterialContextImpl(const Material* material, GLuint vao)
			: MaterialContext(material)
			, _members(new MaterialContextImplPrivate(vao))
		{

		}

		MaterialContextImpl::~MaterialContextImpl()
		{
			delete _members;
			_members = nullptr;
		}

		GLuint MaterialContextImpl::getVAO() const
		{
			return _members->vao;
		}
	}
}