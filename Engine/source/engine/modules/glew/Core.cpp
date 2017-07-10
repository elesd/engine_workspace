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
			GLenum err = glewInit();
			if(GLEW_OK != err)
			{
				std::cerr << "GLEW initialization error: " << glewGetErrorString(err) << std::endl;
			}
			return err == GLEW_OK;
		}

	}
}
#else 

#include <engine/modules/glew/empty/Core.cpp>

#endif
