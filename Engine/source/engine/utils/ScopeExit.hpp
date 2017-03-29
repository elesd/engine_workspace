#pragma once

namespace engine
{

	template<class T>
	void ScopeExit_DeleteContainer<T>::deleteContainer(T &container)
	{
		for(T::iterator it = container.begin(); it != container.end(); ++it)
		{
			delete *it;
		}
	}
}

