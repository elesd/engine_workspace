#pragma once

#include <engine/video/BufferDesc.h>
#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>


namespace engine
{

	class Window;
	class WindowManager;
	class VertexBuffer;
	class IndexBuffer;
	class RenderContext;
	class RenderTarget;
	class Material;
	struct WindowManagerPrivate;

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
		friend struct WindowManagerPrivate;

	protected:
		/**Simple constructor*/
		Driver();
	public:
		/**Virtual destructor*/
		virtual ~Driver();
		/**Init function*/
		void init(RenderContext *renderContext, const DriverInitParameters& params, Window *window);

		void draw(const VertexBuffer* verticies, const IndexBuffer* indicies);

		void setViewPort(int32_t topX, int32_t topY, int32_t width, int32_t height);
	protected:
		RenderContext* getRenderContext();
		void setRenderTarget(RenderTarget* renderTarget);
		void setMaterial(Material* material);
	private:
		/**Platform specific init implementation*/
		virtual void initImpl(const DriverInitParameters& params, Window *window) = 0;

		virtual void drawImpl(const VertexBuffer* verticies, const IndexBuffer* indicies) = 0;

		virtual void setViewPortImpl(int32_t topX, int32_t topY, int32_t width, int32_t height) = 0;
		virtual void setRenderTargetImpl(RenderTarget* renderTarget) = 0;
		virtual void setMaterialImpl(Material* material) = 0;

	private:
		struct DriverPrivate* _members = nullptr;
	};
}