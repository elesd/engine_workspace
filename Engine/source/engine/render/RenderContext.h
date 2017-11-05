#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

#include <engine/video/Driver.h>
#include <engine/render/GlobalResourceMapping.h>

namespace engine
{
	class Geometry;
	class BufferObject;
	class BufferObjectFactory;
	class Driver;
	class EffectCompiler;
	class IndexBufferBase;
	class MaterialInstance;
	class MaterialDescription;
	class PipelineRendererBase;
	class Renderer;
	class RenderTarget;
	class ShaderCompiler;
	class ShaderResourceStorage;
	class ShaderResourceDescription;
	class Texture;
	class Window;

	struct DriverInitParameters;

	enum class ShaderVersion;

	struct RenderContextParameters
	{
		RenderContextParameters() = default;
		RenderContextParameters(DriverInitParameters driverParams, const GlobalResourceMapping& mapping)
			: _driverParameters(driverParams)
			, _resourceMapping(mapping)
		{ }
		const DriverInitParameters& getDriverParameters() const;
		const GlobalResourceMapping& getResourceMapping() const;
	private:
		DriverInitParameters _driverParameters;
		GlobalResourceMapping _resourceMapping;
	};

	class RenderContext final
		: private NonCopyable
		, private NonMoveable
	{
	public:
		RenderContext(std::unique_ptr<Driver>&& driver, std::unique_ptr<BufferObjectFactory>&& bufferObjectFactory);
		~RenderContext();

		void checkSetup();
		void setWindow(Window *window);
		void init(const RenderContextParameters& params);

		Renderer* createRender(const std::string& id, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer);
		bool removeRender(const std::string& id);
		Renderer* findRender(const std::string& id) const;
		bool hasRender(const std::string& id) const;
		
		std::unique_ptr<Geometry> createGeometry() const;
		std::unique_ptr<BufferObject> createVertexBufferObject(size_t size) const;
		std::unique_ptr<BufferObject> createIndexBufferObject(size_t size) const;

		void draw(GeometryInstance *bufferContext) const;

		void swapBuffer();
		// TODO
		// SetViewPort
		void setRenderTarget(RenderTarget* renderTarget);
		void bindGeometryBuffers(GeometryInstance* geometry);
		void setMaterial(MaterialInstance* material);
		std::unique_ptr<RenderTarget> createRenderTarget(std::unique_ptr<Texture>&& texture) const;
		std::unique_ptr<EffectCompiler> createEffectCompiler(Material* material);
		GlobalShaderResourceStorage* getGlobalResources();
		const GlobalShaderResourceStorage* getGlobalResources() const;
		const GlobalResourceMapping& getResourceMapping() const;

	private:
		std::unique_ptr<ShaderCompiler> createShaderCompiler(ShaderVersion, const AttributeFormat& attributeFormat) const;
		struct RenderContextPrivate* _members = nullptr;
	};
}