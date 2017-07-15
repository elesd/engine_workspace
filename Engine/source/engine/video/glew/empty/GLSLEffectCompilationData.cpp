#include <stdafx.h>
#include <engine/video/glew/GLSLEffectCompilationData.h>
///////////////////////////////////////////////////////////////////////////////

#if !ENGINE_USE_GLEW

namespace engine
{
	namespace glew
	{


		GLSLEffectCompilationData::GLSLEffectCompilationData()
			: EffectCompilationData(false)
		{
			INACTIVE_MODULE_ERROR();
		}

		GLSLEffectCompilationData::~GLSLEffectCompilationData()
		{
			INACTIVE_MODULE_ERROR();
		}

		void GLSLEffectCompilationData::setOk(GLuint programID)
		{
			INACTIVE_MODULE_ERROR();
		}

		GLuint GLSLEffectCompilationData::getProgramId() const
		{
			INACTIVE_MODULE_ERROR();
			return 0;
		}


		
	}
}

#endif