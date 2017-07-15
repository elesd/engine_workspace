#include <stdafx.h>
#include <engine/video/glew/GLSLFSCompilationData.h>
///////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_GLEW

namespace engine
{
	namespace glew
	{

		GLSLFSCompilationData::GLSLFSCompilationData(const ShaderCompileOptions& options)
			: ShaderCompilationData(options)
		{
			INACTIVE_MODULE_ERROR();
		}

		GLSLFSCompilationData::~GLSLFSCompilationData()
		{
			INACTIVE_MODULE_ERROR();
		}

		void GLSLFSCompilationData::releaseImpl()
		{
			INACTIVE_MODULE_ERROR();
		}


		GLuint GLSLFSCompilationData::getShaderId() const
		{
			INACTIVE_MODULE_ERROR();
			return 0;
		}

		void GLSLFSCompilationData::setOk(GLuint shaderId)
		{
			INACTIVE_MODULE_ERROR();
		}

	}
}

#endif