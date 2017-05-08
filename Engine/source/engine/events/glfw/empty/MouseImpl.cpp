#include <stdafx.h>
#include <engine/events/glfw/MouseImpl.h>
///////////////////////////////////////////////////////////////////////////////
#if !ENGINE_USE_GLFW

namespace engine
{
	namespace glfw
	{
		void MouseImpl::handleMoveEvent(float , float )
		{
			HARD_FAIL("Inactive module");
		}

		void MouseImpl::handleClickEvent(int32_t , int32_t , int32_t )
		{
			HARD_FAIL("Inactive module");
		}

		void MouseImpl::handleScollEvent(float, float)
		{
			HARD_FAIL("Inactive module");
		}

		void MouseImpl::handlePressEvent(int32_t)
		{
			HARD_FAIL("Inactive module");
		}

		void MouseImpl::handleReleaseEvent(int32_t )
		{
			HARD_FAIL("Inactive module");
		}
	}
}

#endif
