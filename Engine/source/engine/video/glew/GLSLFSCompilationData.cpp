#include <stdafx.h>
#include <engine/video/glew/GLSLFSCompilationData.h>
///////////////////////////////////////////////////////////////////////////////

#if ENGINE_USE_GLEW 

namespace engine
{
	namespace glew
	{
		struct GLSLFSCompilationDataPrivate
		{
			GLuint shaderId;
			bool released = false;
		};

		GLSLFSCompilationData::GLSLFSCompilationData(const ShaderCompileOptions& options)
			: ShaderCompilationData(options)
			, _members(new GLSLFSCompilationDataPrivate())
		{

		}

		GLSLFSCompilationData::~GLSLFSCompilationData()
		{
			if(compilationWasSuccessfull() && _members->released == false)
			{
				glDeleteShader(_members->shaderId);
			}
			delete _members;
			_members = nullptr;
		}

		void GLSLFSCompilationData::releaseImpl()
		{
			glDeleteShader(_members->shaderId);
			_members->released = true;
		}


		GLuint GLSLFSCompilationData::getShaderId() const
		{
			ASSERT(compilationWasSuccessfull());
			return _members->shaderId;
		}

		void GLSLFSCompilationData::setOk(GLuint shaderId)
		{
			ShaderCompilationData::setOk();
			_members->shaderId = shaderId;
		}

	}
}

#endif