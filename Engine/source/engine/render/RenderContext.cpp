#include <stdafx.h>
#include <engine/render/RenderContext.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/render/Render.h>
#include <engine/render/Material.h>

#include <engine/video/Driver.h>
#include <engine/video/RenderTarget.h>
#include <engine/video/ShaderCompiler.h>
#include <engine/video/Shader.h>


namespace
{
	struct ShaderCache
	{
		const engine::Shader* shader = nullptr;
		std::string techniqueName = "";
	};
}

namespace engine
{
	struct RenderContextPrivate
	{
		std::map<std::string, std::unique_ptr<Render>> renders;
		ShaderCache fragmentShaderCache;
		ShaderCache vertexShaderCache;
		const RenderTarget* currentRenderTarget = nullptr;
		std::unique_ptr<Driver> driver;
		RenderContextPrivate(std::unique_ptr<Driver>&& driver)
			: driver(std::move(driver))
		{
		}
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
		_members->driver->init(params.driverParameters, window);
	}

	Render* RenderContext::createRender(const std::string& id, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer)
	{
		ASSERT(!hasRender(id));
		std::unique_ptr<Render> newRender = std::make_unique<Render>(this, std::move(pipelineRenderer));
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

	std::unique_ptr<RenderTarget> RenderContext::createRenderTarget(Texture* texture) const
	{
		std::unique_ptr<RenderTarget> result = _members->driver->createRenderTarget(texture);
		return result;
	}

	std::unique_ptr<ShaderCompiler> RenderContext::createShaderCompiler(ShaderVersion version) const
	{
		return std::unique_ptr<ShaderCompiler>(new ShaderCompiler(_members->driver.get(), version));
	}

	void RenderContext::setRenderTarget(RenderTarget* renderTarget)
	{
		if(_members->currentRenderTarget != renderTarget)
		{
			_members->driver->setRenderTarget(renderTarget);
		}
	}

	void RenderContext::setMaterial(Material* material)
	{
		if(_members->fragmentShaderCache.shader == nullptr
		   || _members->fragmentShaderCache.techniqueName != material->getFragmentShaderTechniqueName()
		   || !_members->fragmentShaderCache.shader->isSame(_members->fragmentShaderCache.techniqueName, *material->getFragmentShader()))
		{
			_members->driver->setShader(material->getFragmentShader(), material->getFragmentShaderTechniqueName());
			_members->fragmentShaderCache.shader = material->getFragmentShader();
			_members->fragmentShaderCache.techniqueName = material->getFragmentShaderTechniqueName();
		}
		else if(_members->vertexShaderCache.shader == nullptr
				|| _members->vertexShaderCache.techniqueName != material->getVertexShaderTechniqueName()
				|| !_members->vertexShaderCache.shader->isSame(_members->vertexShaderCache.techniqueName, *material->getVertexShader()))
		{
			_members->driver->setShader(material->getVertexShader(), material->getVertexShaderTechniqueName());
			_members->vertexShaderCache.shader = material->getVertexShader();
			_members->vertexShaderCache.techniqueName = material->getVertexShaderTechniqueName();
		}
	}


}