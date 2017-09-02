#include <stdafx.h>
#include <engine/video/glew/GLSLEffectCompilationData.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_GLEW 

namespace engine
{
	namespace glew
	{

		struct GLSLEffectCompilationDataPrivate
		{
			GLuint programId;
		};

		GLSLEffectCompilationData::GLSLEffectCompilationData()
			: EffectCompilationData(false)
			, _members(new GLSLEffectCompilationDataPrivate())
		{

		}

		GLSLEffectCompilationData::~GLSLEffectCompilationData()
		{
			delete _members;
			_members = nullptr;
		}

		void GLSLEffectCompilationData::setOk(GLuint programID)
		{
			EffectCompilationData::setOk();
			_members->programId = programID;
		}

		GLuint GLSLEffectCompilationData::getProgramId() const
		{
			ASSERT(isOk());
			return _members->programId;
		}


		
	}
}


#endif