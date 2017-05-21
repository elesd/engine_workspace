#include <stdafx.h>
#include <engine/render/RenderContext.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/Render.h>

#include <engine/video/Driver.h>

namespace engine
{
	struct RenderContextPrivate
	{
		std::map<std::string, std::unique_ptr<Render>> renders;
		Material* currentMaterial = nullptr;
		RenderTarget* currentRenderTarget = nullptr;
		std::unique_ptr<Driver> driver;
		RenderContextPrivate(std::unique_ptr<Driver>&& driver)
			: driver(std::move(driver))
		{ }
	};

	RenderContext::RenderContext(std::unique_ptr<Driver>&& driver)
		: _members(new RenderContextPrivate(std::move(driver)))
	{
	}

	RenderContext::~RenderContext()
	{
		delete _members;
		_members = nullptr;
	}

	void RenderContext::init(const RenderContextParameters& params, Window *window)
	{
		_members->driver->init(this, params.driverParameters, window);
	}

	Render* RenderContext::createRender(const std::string& id, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer)
	{
		ASSERT(!hasRender(id));
		std::unique_ptr<Render> newRender = std::make_unique<Render>(_members->driver.get(), std::move(pipelineRenderer));
		Render* result = newRender.get();
		_members->renders.insert(std::make_pair(id, std::move(newRender)));
		return result;
	}

	Render* RenderContext::findRender(const std::string& id) const
	{
		auto it = _members->renders.find(id);
		return it == _members->renders.end() ? nullptr : it->second.get();
	}

	bool RenderContext::hasRender(const std::string& id) const
	{
		return findRender(id) != nullptr;
	}

	bool RenderContext::removeRender(const std::string& id)
	{
		size_t deletedItems = _members->renders.erase(id);
		return deletedItems > 0;
	}

	RenderTarget* RenderContext::getCurrentRenderTarget()
	{
		return _members->currentRenderTarget;
	}

	Material* RenderContext::getCurrentMaterial()
	{
		return _members->currentMaterial;
	}

	void RenderContext::setCurrentRenderTarget(RenderTarget* renderTarget)
	{
		_members->currentRenderTarget = renderTarget;
	}

	void RenderContext::setCurrentMaterial(Material* material)
	{
		_members->currentMaterial = material;
	}
}