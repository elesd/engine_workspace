#pragma once


namespace engine
{
	class RenderContext;

	class IRenderable
	{
	protected:
		IRenderable() = default;
		virtual ~IRenderable() {}
	public:

		virtual void preRender(RenderContext*) {};
		virtual void render(RenderContext*) = 0;
		virtual void postRender(RenderContext*) {};
	};
}