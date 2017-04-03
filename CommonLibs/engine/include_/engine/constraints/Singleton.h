#pragma once

#include <engine/constraints/NonCopyable.h>
#include <engine/constraints/NonMoveable.h>

namespace engine
{
	/**
	* Singleton implementation
	*/
	template<class T>
	class Singleton : NonCopyable,
		NonMoveable
	{
	public:
		virtual ~Singleton() {}
		/**
		* @return the instance object
		*/
		static T *getInstance();

		/**
		* Create an instance with the given arguments
		* @param creation arguments
		*/
		template<typename... Args>
		static void createInstance(Args ...args);
		/** Delete the instance */
		static void releaseInstance();
	private:
		/**PIMPL*/
		static std::unique_ptr<T> _instance;
	};
}

#include <engine/constraints/Singleton.hpp>
