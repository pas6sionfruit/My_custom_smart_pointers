#pragma once
#include <memory>
#include <vector>

template<class T, class TDeleter = std::default_delete<T>>
class SharedPtr {

	typedef SharedPtr<T, TDeleter> T_SharedPtr;

	T* _data = nullptr;
	int* _counter = nullptr;
	TDeleter _Tdeleter;

public:

	SharedPtr() = default;
	SharedPtr(T* rhv);
	SharedPtr(const T_SharedPtr& rhv);
	SharedPtr(T_SharedPtr&& rhv);
	~SharedPtr();
	SharedPtr& operator=(const T_SharedPtr& rhv);
	SharedPtr& operator=(T_SharedPtr&& rhv);
	T& operator*() const;
	T* operator->() const;
	[[nodiscard]] T* GetPtr() const;
	[[nodiscard]] TDeleter& GetDeleter() const;
	[[nodiscard]] int* GetCounter() const;
	operator bool() const;
	void release();
	void reset(T* rhv = nullptr);
	void swap(T_SharedPtr& rhv);
};


template<class T, class TDeleter>
inline SharedPtr<T, TDeleter>::SharedPtr(T* rhv) {

	_counter = new int(1);
	_data = rhv;
}

template<class T, class TDeleter>
inline SharedPtr<T, TDeleter>::SharedPtr(const T_SharedPtr& rhv) {

	_counter = rhv._counter;
	_data = rhv._data;
	++(*_counter);

}

template<class T, class TDeleter>
inline SharedPtr<T, TDeleter>::SharedPtr(T_SharedPtr&& rhv) {

	_counter = rhv._counter;
	rhv._counter = nullptr;
	_data = rhv._data;
	rhv._data = nullptr;

}

template<class T, class TDeleter>
inline SharedPtr<T, TDeleter>::~SharedPtr() {

	if (_counter && *_counter > 1) {

		(*_counter)--;
	} 
	else {

		delete _counter;
		_Tdeleter(_data);
	}
}

template<class T, class TDeleter>
inline SharedPtr <T, TDeleter>& SharedPtr<T, TDeleter>::operator=(const T_SharedPtr& rhv) {

	if (this != *rhv) {

		if (_counter && *_counter > 1) {

			(*_counter)--;
		}
		else {

			_Tdeleter(_data);
			delete _counter;
		}
		_counter = rhv._counter;
		_data = rhv._data;
		++(*_counter);
	}

	return *this;
}

template<class T, class TDeleter>
inline SharedPtr<T, TDeleter>& SharedPtr<T, TDeleter>::operator=(T_SharedPtr&& rhv) {

	if (this != *rhv) {

		if (_counter && *_counter > 1) {

			(*_counter)--;
		}
		else {

			_Tdeleter(_data);
			delete _counter;
		}
		_counter = rhv._counter;
		rhv._counter = nullptr;
		_data = rhv._data;
		rhv._data = nullptr;
	}

	return *this;	
}

template<class T, class TDeleter>
inline T& SharedPtr<T, TDeleter>::operator*() const {
	
	return  *_data;
}

template<class T, class TDeleter>
inline T* SharedPtr<T, TDeleter>::operator->() const {

	return _data;
}

template<class T, class TDeleter>
inline T* SharedPtr<T, TDeleter>::GetPtr() const {

	return _data;
}

template<class T, class TDeleter>
inline TDeleter& SharedPtr<T, TDeleter>::GetDeleter() const {

	 return _Tdeleter;
}

template<class T, class TDeleter>
inline int* SharedPtr<T, TDeleter>::GetCounter() const {

	return _counter;
}

template<class T, class TDeleter>
inline SharedPtr<T, TDeleter>::operator bool() const {

	return _data;
}

template<class T, class TDeleter>
inline void SharedPtr<T, TDeleter>::release() {

	(*_counter)--;
	_data = nullptr;
}

template<class T, class TDeleter>
inline void SharedPtr<T, TDeleter>::reset(T* rhv) {

	_counter = new int(1);
	_data = rhv;
}

template<class T, class TDeleter>
inline void SharedPtr<T, TDeleter>::swap(T_SharedPtr& rhv) {

	std::swap(*this, rhv);

}
