#include <stdafx.h>
#include <engine/render/RenderContext.h>
///////////////////////////////////////////////////////////////////////////////

#include <engine/exceptions/LogicalErrors.h>

#include <engine/libraries/MaterialInstance.h>

#include <engine/render/Render.h>

#include <engine/video/Effect.h>
#include <engine/video/EffectComperator.h>
#include <engine/video/MaterialDescription.h>
#include <engine/video/EffectCompiler.h>

#include <engine/video/BufferObject.h>
#include <engine/video/BufferObjectFactory.h>
#include <engine/video/Driver.h>
#include <engine/video/Effect.h>
#include <engine/video/GlobalShaderResourceStorage.h>
#include <engine/video/Material.h>
#include <engine/video/RenderTarget.h>
#include <engine/video/ShaderCompiler.h>
#include <engine/video/ShaderResourceHandler.h>
#include <engine/video/ShaderResourceStorage.h>
#include <engine/video/ShaderResourceDescription.h>
#include <engine/video/Shader.h>

#include <engine/video/Geometry.h>
#include <engine/video/IndexBufferBase.h>
#include <engine/video/VertexBuffer.h>



namespace engine
{
	const DriverInitParameters& RenderContextParameters::getDriverParameters() const
	{
		return _driverParameters;
	}
	const GlobalResourceMapping& RenderContextParameters::getResourceMapping() const
	{
		return _resourceMapping;
	}

	//////////////////////////////////////////////////////////////////////////////

	struct RenderContextPrivate
	{
		std::map<std::string, std::unique_ptr<Render>> renders;
		const RenderTarget* currentRenderTarget = nullptr;
		EffectInstance* currentEffect = nullptr;
		EffectComperator effectComperator;
		std::unique_ptr<Driver> driver;
		std::unique_ptr<BufferObjectFactory> bufferObjectFactory;
		std::unique_ptr<GlobalShaderResourceStorage> globalResources;
		GlobalResourceMapping resourceMapping;

		RenderContextPrivate(std::unique_ptr<Driver>&& driver, std::unique_ptr<BufferObjectFactory>&& bufferObjectFactory)
			: driver(std::move(driver))
			, bufferObjectFactory(std::move(bufferObjectFactory))
		{
		}
	};

	RenderContext::RenderContext(std::unique_ptr<Driver>&& driver, std::unique_ptr<BufferObjectFactory>&& bufferObjectFactory)
		: _members(new RenderContextPrivate(std::move(driver), std::move(bufferObjectFactory)))
	{
		_members->bufferObjectFactory->setup(this);
	}

	RenderContext::~RenderContext()
	{
		delete _members;
		_members = nullptr;
	}

	void RenderContext::checkSetup()
	{
		if(_members->driver->checkDeviceSetup() == false)
		{
			throw InitializationError("Driver setup failed!");
		}
	}

	void RenderContext::setWindow(Window *window)
	{
		_members->driver->setWindow(window);
	}

	void RenderContext::init(const RenderContextParameters& params)
	{
		_members->driver->init(params.getDriverParameters());
		_members->globalResources = std::make_unique<GlobalShaderResourceStorage>();
		_members->resourceMapping = params.getResourceMapping();
		_members->globalResources->initGlobalResources(_members->resourceMapping);
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

	std::unique_ptr<Geometry> RenderContext::createGeometry() const
	{
		return _members->bufferObjectFactory->createGeometry();
	}

	std::unique_ptr<BufferObject> RenderContext::createVertexBufferObject(size_t size) const
	{
		return _members->bufferObjectFactory->createVertexBufferObject(size);
	}

	std::unique_ptr<BufferObject> RenderContext::createIndexBufferObject(size_t size) const
	{
		return _members->bufferObjectFactory->createIndexBufferObject(size);
	}

	void RenderContext::draw(GeometryInstance *bufferContext) const
	{
		_members->driver->draw(bufferContext);
	}

	void RenderContext::swapBuffer()
	{
		_members->driver->swapBuffer();
	}

	bool RenderContext::removeRender(const std::string& id)
	{
		size_t deletedItems = _members->renders.erase(id);
		return deletedItems > 0;
	}

	std::unique_ptr<RenderTarget> RenderContext::createRenderTarget(std::unique_ptr<Texture>&& texture) const
	{
		std::unique_ptr<RenderTarget> result = _members->driver->createRenderTarget(std::move(texture));
		return result;
	}

	std::unique_ptr<EffectCompiler> RenderContext::createEffectCompiler(Material* material)
	{
		std::unique_ptr<ShaderCompiler> shaderCompiler = createShaderCompiler(material->getDescription().getShaderVersion(), material->getDescription().getAttributeFormat());
		std::unique_ptr<EffectCompiler> effectCompiler(new EffectCompiler(material, _members->driver.get(), std::move(shaderCompiler)));
		return effectCompiler;
	}

	std::unique_ptr<ShaderCompiler> RenderContext::createShaderCompiler(ShaderVersion version, const AttributeFormat& attributeFormat) const
	{
		return std::unique_ptr<ShaderCompiler>(new ShaderCompiler(_members->driver.get(), version, attributeFormat));
	}

	void RenderContext::setRenderTarget(RenderTarget* renderTarget)
	{
		if(_members->currentRenderTarget != renderTarget)
		{
			_members->currentRenderTarget = renderTarget;
			_members->driver->setRenderTarget(renderTarget);
		}
	}

	void RenderContext::bindGeometryBuffers(GeometryInstance* geometry)
	{
		_members->driver->bindGeometryBuffers(geometry);
	}

	void RenderContext::setMaterial(MaterialInstance* material)
	{
		EffectInstance* currentEffect = material->getCurrentEffect();
		_members->effectComperator.compare(_members->currentEffect, currentEffect);
		_members->driver->setEffect(currentEffect, _members->effectComperator);

		if(_members->effectComperator.hasAnyChange())
		{
			_members->currentEffect = currentEffect;
		}
	}

	GlobalShaderResourceStorage* RenderContext::getGlobalResources()
	{
		return _members->globalResources.get();
	}

	const GlobalShaderResourceStorage* RenderContext::getGlobalResources() const
	{
		return _members->globalResources.get();
	}

	const GlobalResourceMapping& RenderContext::getResourceMapping() const
	{
		return _members->resourceMapping;
	}

}