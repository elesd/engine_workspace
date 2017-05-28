#include <stdafx.h>
#include <engine/render/RenderPass.h>

#include <engine/render/IRenderable.h>
#include <engine/render/RenderContext.h>


namespace engine
{
	struct RenderPassPrivate
	{
		RenderContext* renderContext = nullptr;

		Color4 clearColor;

		std::vector<IRenderable*> objects;
		std::string name;

		RenderPassPrivate(const std::string& name, RenderContext* driver)
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
		for(IRenderable* obj : _members->objects)
		{
			obj->preRender(_members->renderContext);
			obj->render(_members->renderContext);
			obj->postRender(_members->renderContext);
		}
	}

	const std::vector<IRenderable*>& RenderPass::getObjects() const
	{
		return _members->objects;
	}

	std::vector<IRenderable*>& RenderPass::getObjects()
	{
		return _members->objects;
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
