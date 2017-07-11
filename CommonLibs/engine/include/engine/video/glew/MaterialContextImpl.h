#pragma once

#include <engine/video/MaterialContext.h>

namespace engine
{
	namespace glew
	{
		class MaterialContextImpl
			: public MaterialContext
		{
		public:
			MaterialContextImpl(const Material* material, Driver* driver, GLuint vao);
			~MaterialContextImpl() override;

			GLuint getVAO() const;
		private:
			struct MaterialContextImplPrivate* _members = nullptr;
		};
	}
}