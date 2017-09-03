#pragma once

namespace engine
{
	template<class T>
	class GuardedObject
	{
	public:
		GuardedObject(std::unique_lock<std::mutex>&& lock, const T& object)
			: _lock(std::move(lock))
			, _object(object)
		{

		}
		GuardedObject(GuardedObject&& o)
			: _lock(std::move(o._lock))
			, _object(o._object)
		{ }

		GuardedObject operator=(GuardedObject&& o)
		{
			_lock = std::move(o._lock);
			_object = o._object;
			return *this;
		}

		bool operator==(const GuardedObject& o) const
		{
			return o._object == _object;
		}

		const T& operator->() const
		{
			return _object;
		}

		T& operator->() 
		{
			return _object;
		}

		const T& operator*() const
		{
			return _object;
		}

		T& operator*() 
		{
			return _object;
		}

	private:
		std::unique_lock<std::mutex> _lock;
		T _object;
	};
}