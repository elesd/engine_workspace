#include <stdafx.h>
#include <engine/servicies/RenderService.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	struct RenderServicePrivate
	{
		RenderContext* renderContext = nullptr;
		explicit RenderServicePrivate(RenderContext *renderContext)
			: renderContext(renderContext)
		{		}
	};

	RenderService::RenderService(RenderContext* renderContext)
		: _members(new RenderServicePrivate(renderContext))
	{ }

	RenderService::~RenderService()
	{
		delete _members;
		_members = nullptr;
	}

	RenderContext* RenderService::getRenderContext() const
	{
		return _members->renderContext;
	}

}