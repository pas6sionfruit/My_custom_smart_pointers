#pragma once
#include <memory>

template<class T, class TDeleter = std::default_delete<T>>
class UniquePtr {

	typedef UniquePtr<T, TDeleter> T_UniquePtr;

	T* _data = nullptr;
	TDeleter _Tdeleter;
	UniquePtr(const T_UniquePtr& ) = delete;
	UniquePtr& operator=(const T_UniquePtr&) = delete;

public:

	UniquePtr();
	UniquePtr(T* rhv);
	UniquePtr(T_UniquePtr&& rhv);
	~UniquePtr();
	UniquePtr& operator=(T_UniquePtr&& rhv);
	T& operator*() const;
	T* operator->() const;
	[[nodiscard]] T* GetPtr() const;
	[[nodiscard]] TDeleter& GetDeleter() const;
	operator bool() const;
	T* release();
	void reset(T* rhv = nullptr);
	void swap(T_UniquePtr& rhv);

};


template<class T, class TDeleter>
inline UniquePtr<T, TDeleter>::UniquePtr() = default;

template<class T, class TDeleter>
inline UniquePtr<T, TDeleter>::UniquePtr(T* rhv) : _data(rhv) {} // constant fields can be initialized only that way.

template<class T, class TDeleter>
inline UniquePtr<T, TDeleter>::UniquePtr(T_UniquePtr&& rhv) {

	_Tdeleter(_data); 
	_data = rhv._data;
	rhv._data = nullptr;
}

template<class T, class TDeleter>
inline UniquePtr<T, TDeleter>::~UniquePtr() {

	_Tdeleter(_data);
}

template<class T, class TDeleter>
inline UniquePtr<T, TDeleter>& UniquePtr<T, TDeleter>::operator=(T_UniquePtr&& rhv) {

	if (this != *rhv) {

		_Tdeleter(_data);   
		this = rhv._data;
		rhv._data = nullptr;
	}

	return *this;
}

template<class T, class TDeleter>
inline T& UniquePtr<T, TDeleter>::operator*() const {

	return *_data;
}

template<class T, class TDeleter>
inline T* UniquePtr<T, TDeleter>::operator->() const {

	return _data;
}

template<class T, class TDeleter>
inline T* UniquePtr<T, TDeleter>::GetPtr() const {

	return _data;
}

template<class T, class TDeleter>
inline TDeleter& UniquePtr<T, TDeleter>::GetDeleter() const {
	
	return _Tdeleter;
}

template<class T, class TDeleter>
inline UniquePtr<T, TDeleter>::operator bool() const {

	return _data != nullptr;
}

template<class T, class TDeleter>
inline T* UniquePtr<T, TDeleter>::release() {

	T* tmp = _data;
	_data = nullptr;
	return tmp;

}

template<class T, class TDeleter>
inline void UniquePtr<T, TDeleter>::reset(T* rhv) {

	_Tdeleter(_data);  
	_data = rhv;
}

template<class T, class TDeleter>
inline void UniquePtr<T, TDeleter>::swap(T_UniquePtr& rhv) {

	std::swap(_data, rhv._data);
}




