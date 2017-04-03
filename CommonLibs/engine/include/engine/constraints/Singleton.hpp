namespace engine
{

	template<class T>
	std::unique_ptr<T> Singleton<T>::_instance(nullptr);

	template<class T>
	T *Singleton<T>::getInstance()
	{
		return _instance.get();
	}

	template<class T>
	template<typename... Args>
	void Singleton<T>::createInstance(Args ...args)
	{
		_instance.reset(new T(args...));
	}

	template<class T>
	void Singleton<T>::releaseInstance()
	{
		_instance.reset(nullptr);
	}
}