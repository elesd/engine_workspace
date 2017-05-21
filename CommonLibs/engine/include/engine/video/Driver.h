#pragma once

#include <engine/video/BufferDesc.h>

namespace engine
{

	class Window;
	class WindowManager;
	class VertexBuffer;
	class IndexBuffer;
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
	{
		friend class WindowManager;
		friend struct WindowManagerPrivate;

	protected:
		/**Simple constructor*/
		Driver() = default;
	public:
		/**Virtual destructor*/
		virtual ~Driver() {}
		/**Init function*/
		void init(const DriverInitParameters& params, Window *window);

		void draw(const VertexBuffer* verticies, const IndexBuffer* indicies);
	private:
		/**Platform specific init implementation*/
		virtual void initImpl(const DriverInitParameters& params, Window *window) = 0;
		/// TODO
		virtual void drawImpl(const VertexBuffer* verticies, const IndexBuffer* indicies) {};
	};
}