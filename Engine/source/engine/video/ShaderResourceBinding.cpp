#include <stdafx.h>
#include <engine/video/ShaderResourceBinding.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{

	std::unique_ptr<ShaderResourceBinding> ShaderResourceBinding::clone() const
	{
		return cloneImpl();
	}

}