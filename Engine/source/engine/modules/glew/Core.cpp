#include <stdafx.h>
#if ENGINE_USE_GLEW
#include <engine/modules/glew/Core.h>
/////////////////////////////////////////////////////

#include <GL/glew.h>

namespace engine
{
	namespace glew
	{
		bool Core::init()
		{
			return true;
		}

		bool Core::initOpenglContext()
		{
			glewExperimental = GL_TRUE;
			GLenum err = glewInit();
			if(GLEW_OK != err)
			{
				std::cerr << "GLEW initialization error: " << glewGetErrorString(err) << std::endl;
			}
			GLenum glErr = GL_NO_ERROR;
			while((glErr = glGetError()) != GL_NO_ERROR)
			{
				std::cerr << "Warning: glew init error with code: " << glErr << std::endl;
			}
			return err == GLEW_OK;
		}

	}
}

#endif
