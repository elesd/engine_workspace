#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

#include <engine/video/Driver.h>

namespace engine
{
	class Driver;
	class EffectCompiler;
	class IndexBuffer;
	class Material;
	class MaterialDescription;
	class PipelineRendererBase;
	class Render;
	class RenderTarget;
	class ShaderCompiler;
	class Texture;
	class VertexBuffer;
	class Window;

	struct DriverInitParameters;

	enum class ShaderVersion;

	struct RenderContextParameters
	{
		DriverInitParameters driverParameters;
	};

	class RenderContext final
		: private NonCopyable
		, private NonMoveable
	{
	public:
		RenderContext(std::unique_ptr<Driver>&& driver);
		~RenderContext();

		void init(const RenderContextParameters& params, Window *window);

		Render* createRender(const std::string& id, std::unique_ptr<PipelineRendererBase>&& pipelineRenderer);
		bool removeRender(const std::string& id);
		Render* findRender(const std::string& id) const;
		bool hasRender(const std::string& id) const;
		
		// TODO
		// SetViewPort
		void setRenderTarget(RenderTarget* renderTarget);
		void setMaterial(Material* material);
		std::unique_ptr<RenderTarget> createRenderTarget(Texture* texture) const;
		std::unique_ptr<EffectCompiler> createEffectCompiler(const MaterialDescription&);
	private:
		std::unique_ptr<ShaderCompiler> createShaderCompiler(ShaderVersion) const;
		struct RenderContextPrivate* _members = nullptr;
	};
}