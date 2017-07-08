#pragma once

#include <engine/video/BufferDesc.h>
#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>


namespace engine
{
	class Effect;
	class EffectComperator;
	class IndexBufferBase;
	class Material;
	class MaterialContext;
	class RenderContext;
	class RenderTarget;
	class Shader;
	class ShaderCompileOptions;
	class Texture;
	class VertexBuffer;
	class WindowManager;
	class Window;

	
	/**Initialization parameters for the driver*/
	struct DriverInitParameters
	{
		/**Buffer descripition of the main buffer*/
		BufferDesc description;
		/**Sample count of the driver*/
		int32_t sampleCount;
	};


	/**
	* Video driver interface implementation.
	* All the graphical instructions will be executed via this class implementation.
	*/
	class Driver
		: private NonCopyable
		, private NonMoveable
	{
		friend class WindowManager;

	protected:
		/**Simple constructor*/
		Driver();
	public:
		/**Virtual destructor*/
		virtual ~Driver();
		/**Init function*/
		void init(const DriverInitParameters& params, Window *window);

		void draw(const VertexBuffer* verticies, const IndexBufferBase* indicies);
		void setRenderTarget(RenderTarget* renderTarget);
		void resetRenderTarget();
		void setViewPort(int32_t x, int32_t y, int32_t width, int32_t height);
		std::unique_ptr<RenderTarget> createRenderTarget(std::unique_ptr<Texture>&& texture);
		void compileShader(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options);
		void compileEffect(Effect* effect);
		void setMaterialContext(const MaterialContext* material);
		void setEffect(Effect *effect, const EffectComperator& comperator);
		void setShader(Shader* shader, const std::string& techniqueName);
		std::unique_ptr<MaterialContext> createMaterialContext(const Material* material);
		void swapBuffer();

	protected:
		Window* getWindow() const;

	private:
		/**Platform specific init implementation*/
		virtual void initImpl(const DriverInitParameters& params, Window *window) = 0;
		virtual void compileShaderImpl(Shader *shader, const std::string& techniqueName, const ShaderCompileOptions& options) = 0;
		virtual void compileEffectImpl(Effect* effect) = 0;
		virtual void drawImpl(const VertexBuffer* verticies, const IndexBufferBase* indicies) = 0;
		virtual void setMaterialContextImpl(const MaterialContext* material) = 0;
		virtual void setEffectImpl(Effect* effect) = 0;
		virtual void setShaderImpl(Shader* shader, const std::string& techniqueName) = 0;
		virtual std::unique_ptr<RenderTarget> createRenderTargetImpl(std::unique_ptr<Texture>&& texture) = 0;

		virtual void setViewPortImpl(int32_t x, int32_t y, int32_t width, int32_t height) = 0;
		virtual void setRenderTargetImpl(RenderTarget* renderTarget) = 0;
		virtual void resetRenderTargetImpl() = 0;
		virtual std::unique_ptr<MaterialContext> createMaterialContextImpl(const Material* material) = 0;
		virtual void swapBufferImpl() = 0;

	private:
		struct DriverPrivate* _members = nullptr;
	};
}