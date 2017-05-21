#pragma once

#include <engine/constraints/NonCopyable.h>

namespace engine
{
	/**
	* Simple implementation of scope exit.
	* When this object dies executes a function which was given during construction.
	*/
	class ScopeExit
		: private NonCopyable
	{
	public:
		/**
		* Create scope exit with a given function.
		* @param f: the function to exection during object destruction.
		*/
		ScopeExit(std::function<void()> &&f)
			:_f(std::move(f))
		{	}

		/**
		* Moveable.
		* @param o: other object.
		*/
		ScopeExit(ScopeExit &&o)
			:_f(std::move(o._f))
		{	}

		/**Executes the stored function*/
		~ScopeExit()
		{
			_f();
		}

		/**
		* Moveable.
		* @param o: other object.
		* @return Returns a reference to this.
		*/
		ScopeExit &operator=(ScopeExit &&o)
		{
			_f = std::move(o._f);
		}

	private:
		/**stored function.*/
		std::function<void()> _f;
	};

	/**
	* Scope exit for container destruction.
	* @tparam T: container type.
	*/
	template<class T>
	struct ScopeExit_DeleteContainer : ScopeExit
	{
		/**Deletes the container content.*/
		static void deleteContainer(T &container);
	public:
		/**
		* Construct a scope exit for container desrtuction
		* @param container: Container to delete at exit.
		*/
		ScopeExit_DeleteContainer(T &container)
			:ScopeExit(std::bind(&deleteContainer, container))
		{}
	};
}

#include <ScopeExit.hpp> 