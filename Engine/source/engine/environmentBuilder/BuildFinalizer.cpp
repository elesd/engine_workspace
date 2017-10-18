#include <stdafx.h>
#include <engine/environmentBuilder/BuildFinalizer.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/app/Application.h>

namespace engine
{
	void BuildFinalizer::build()
	{
		setInitialized();
	}
}