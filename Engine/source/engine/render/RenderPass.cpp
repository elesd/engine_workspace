#include <stdafx.h>
#include <engine/render/RenderPass.h>

#include <engine/render/IRenderable.h>

#include <engine/video/Driver.h>

namespace engine
{
	struct RenderPassPrivate
	{
		Driver* driver = nullptr;

		Color4 clearColor;

		std::vector<IRenderable*> objects;
		std::string name;

		RenderPassPrivate(const std::string& name, Driver *driver)
			: name(name), driver(driver)
		{
		}
	};

	RenderPass::RenderPass(const std::string& name, Driver *driver)
		: _members(new RenderPassPrivate(name, driver))
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
		// _members->dirver->setClearColor(_members->clearColor) 
		// ...
		for(IRenderable* obj : _members->objects)
		{
			obj->preRender(_members->driver);
			obj->render(_members->driver);
			obj->postRender(_members->driver);
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
