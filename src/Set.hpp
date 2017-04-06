#include "Set.h"

template<class T>
Set<T>::Set(int _size/*= 4*/) {
	if (_size < 0)
		_size = 1;
	_sz = _size;
	_data = new T[_sz];
	_used = 0;
}

template<class T>
Set<T>::~Set() {
	delete[] _data;
}

template<class T>
bool Set<T>::add(T item) { // always added to the end
	if (_used >= _sz) {
		_sz *= 2;
		T* temp = _data;
		if (!(_data = new T[_sz]))
			return false;
		for (int i = 0; i < _used; ++i)
			_data[i] = temp[i];
		delete[] temp;
	}
	_data[_used++] = item;
	return true;
}

template<class T>
bool Set<T>::truncate() { // make _sz = _used
	if (_used != _sz) {
		T* temp = _data;
		_sz = _used;
		if (!(_data = new T[_sz]))
			return false;
		for (int i = 0; i < _used; ++i)
			_data[i] = temp[i];
		delete[] temp;
	}
	return true;
}

template<class T>
void Set<T>::clear() {
	_used = 0;
}

template<class T>
int Set<T>::length() {
	return _used;
}


template<class T>
int Set<T>::size() {
	return _used;
}

template<class T>
bool Set<T>::empty() {
	return _used == 0;
}

template<class T>
T Set<T>::operator[](int i) const {
	return _data[i];
}

template<class T>
T Set<T>::get(int i) const {
	return _data[i];
}

template<class T>
T& Set<T>::operator[](const int &i) {
	return _data[i];
}
