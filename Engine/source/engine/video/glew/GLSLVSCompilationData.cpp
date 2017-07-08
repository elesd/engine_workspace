#include <stdafx.h>
#include <engine/video/glew/GLSLVSCompilationData.h>
///////////////////////////////////////////////////////////////////////////////


namespace engine
{
	namespace glew
	{
		struct GLSLVSCompilationDataPrivate
		{
			GLuint shaderId;
			bool released = false;
		};

		GLSLVSCompilationData::GLSLVSCompilationData(const ShaderCompileOptions& options)
			: ShaderCompilationData(options)
			, _members(new GLSLVSCompilationDataPrivate())
		{

		}

		GLSLVSCompilationData::~GLSLVSCompilationData()
		{
			if(compilationWasSuccessfull() && _members->released == false)
			{
				glDeleteShader(_members->shaderId);
			}
			delete _members;
			_members = nullptr;
		}

		void GLSLVSCompilationData::releaseImpl()
		{
			glDeleteShader(_members->shaderId);
			_members->released = true;
		}

		GLuint GLSLVSCompilationData::getShaderId() const
		{
			ASSERT(compilationWasSuccessfull());
			return _members->shaderId;
		}

		void GLSLVSCompilationData::setOk(GLuint shaderId)
		{
			ShaderCompilationData::setOk();
			_members->shaderId = shaderId;
		}
	}
}