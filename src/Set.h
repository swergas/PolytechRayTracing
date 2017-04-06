#ifndef SET_H_
#define SET_H_

template<class T>
class Set {
protected:
	int _sz;
	T* _data; // shared_ptr<T> data;
	int _used;

public:
	Set(int _size = 4);
	virtual ~Set();

	bool add(T item); // always added to the end
	bool truncate(); // make size = _used
	void clear();
	int length();
	int size();
	bool empty();

	T operator[](int i) const;
	T get(int i) const;
	T& operator[](const int &i);

};
#include "Set.hpp"

#endif /* SET_H_ */
