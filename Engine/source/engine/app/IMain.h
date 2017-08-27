#pragma once

#include <engine/constraints/NonCopyable.h>


namespace engine
{
	/**
	* Base class for core logic of an application
	*/
	class IMain : NonCopyable
	{
	protected:
		/**Simple constructor only for child classes.*/
		IMain() = default;
	public:
		/**Simple destructor*/
		~IMain() {};
		/**Called once when the application is started*/
		virtual void load() = 0;
		/**Called once per each frame to update the main*/
		virtual void update() = 0;

	};
}
