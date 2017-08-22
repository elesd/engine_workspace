#include <stdafx.h>
#include <engine/entityFramework/Component.h>
///////////////////////////////////////////////////////////////////////////////

namespace engine
{
	struct ComponentPrivate
	{
		uint32_t tag = 0;
	};

	Component::Component()
		: _members(new ComponentPrivate())
	{

	}

	Component::~Component()
	{
		delete _members;
		_members = nullptr;
	}

	uint32_t Component::getTag() const
	{
		return _members->tag;
	}

	void Component::onRender(RenderContext* renderContext)
	{
		onRenderComponent(renderContext);
	}

	void Component::onUpdate()
	{
		onUpdateComponent();
	}

	std::unique_ptr<Component> Component::clone() const
	{
		std::unique_ptr<Component> result = cloneComponent();
		result->setTag(getTag());
		return result;
	}

	void Component::setTag(uint32_t tag)
	{
		_members->tag = tag;
	}
}