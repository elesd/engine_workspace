#pragma once

#include <engine/video/ShaderResourceBinding.h>

namespace engine
{
	namespace glew
	{
		class GLSLResourceBinding
			: public ShaderResourceBinding
		{
		public:
			explicit GLSLResourceBinding(GLint location);
			~GLSLResourceBinding() override;

			GLint getLocation() const;
			bool isBound() const override;

		private:
			struct GLSLResourceBindingPrivate* _members = nullptr;
		};
	}
}