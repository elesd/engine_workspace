#include <stdafx.h>
#include <engine/video/glew/GLSLVSCompilationData.h>
///////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_GLEW

namespace engine
{
	namespace glew
	{

		GLSLVSCompilationData::GLSLVSCompilationData(const ShaderCompileOptions& options)
			: ShaderCompilationData(options)
		{
			INACTIVE_MODULE_ERROR();
		}

		GLSLVSCompilationData::~GLSLVSCompilationData()
		{
			INACTIVE_MODULE_ERROR();
		}

		void GLSLVSCompilationData::releaseImpl()
		{
			INACTIVE_MODULE_ERROR();
		}

		GLuint GLSLVSCompilationData::getShaderId() const
		{
			INACTIVE_MODULE_ERROR();
			return 0;
		}

		void GLSLVSCompilationData::setOk(GLuint shaderId)
		{
			INACTIVE_MODULE_ERROR();
		}
	}
}
#endif