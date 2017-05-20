#pragma once


namespace engine
{
	class Driver;

	class IRenderable
	{
	protected:
		IRenderable() = default;
		virtual ~IRenderable() {}
	public:

		virtual void preRender(Driver*) {};
		virtual void render(Driver*) = 0;
		virtual void postRender(Driver*) {};
	};
}