#include <stdafx.h>
#include <engine/render/RenderPass.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/entityFramework/Component.h>

#include <engine/render/RenderContext.h>


namespace engine
{
	struct RenderPassPrivate
	{
		RenderContext* renderContext = nullptr;

		Color4 clearColor;

		std::vector<Component*> visibleComponents;
		std::string name;

		RenderPassPrivate(const std::string& name, RenderContext* renderContext)
			: name(name), renderContext(renderContext)
		{
		}
	};

	RenderPass::RenderPass(const std::string& name, RenderContext* renderContext)
		: _members(new RenderPassPrivate(name, renderContext))
	{

	}

	RenderPass::RenderPass(RenderPass&& o)
		: _members(o._members)
	{
		o._members = nullptr;
	}

	RenderPass& RenderPass::operator=(RenderPass&& o)
	{
		delete _members;
		_members = o._members;
		o._members = nullptr;
		return *this;
	}

	RenderPass::~RenderPass()
	{
		delete _members;
		_members = nullptr;
	}

	void RenderPass::render()
	{
		// TODO 
		// setClearColor(_members->clearColor) 
		// ...
		for(Component* component: _members->visibleComponents)
		{
			component->onRender(_members->renderContext);
		}
	}

	const std::vector<Component*>& RenderPass::getComponents() const
	{
		return _members->visibleComponents;
	}
	
	void RenderPass::registerComponent(Component* o)
	{
		_members->visibleComponents.push_back(o);
	}

	void RenderPass::unregisterComponent(const Component* component)
	{
		auto it = std::remove(_members->visibleComponents.begin(), _members->visibleComponents.end(), component);
		_members->visibleComponents.erase(it, _members->visibleComponents.end());
	}

	void RenderPass::setClearColor(Color4 color)
	{
		_members->clearColor = color;
	}

	const Color4& RenderPass::getClearColor() const
	{
		static Color4 result;
		return result; 
	}
}
