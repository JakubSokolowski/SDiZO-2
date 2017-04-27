#include "stdafx.h"
#include "Vector.h"

//base constructor
template<class T>
Vector<T>::Vector()
	: capacity_(10)
	, size_(0)
	, buffer_(new char[sizeof(T) * 10])
{}

template<class T>
Vector<T>::Vector(size_type capacity)
	: size_(0)
	, capacity_(capacity)
	, buffer_(new char[sizeof(T) * capacity])
{}

//Creates vector and fills with given object
template<class T>
Vector<T>::Vector(size_type size, const T & initial)
{
	size_ = size;
	capacity_ = 10;
	buffer_ = new T[capacity_];
	for (unsigned int i = 0; i < size; i++)
		buffer_[i] = initial;
}

//Copy constructor [REVISED]
template<class T>
Vector<T>::Vector(Vector<T> & const obj)
	: size_(obj.size_)
	, capacity_(obj.capacity_)
	, buffer(nw char[sizeof(T)* capacity_])
{
	for (size_type i = 0; i < size_; i++)
		new (buffer_ + sizeof(T)*i) T(obj[i]);
}



template<class T>
Vector<T>::~Vector()
{
	delete[] buffer_;
}

template<class T>
uint Vector<T>::capacity() const
{
	return capacity_;
}

template<class T>
uint Vector<T>::size() const
{
	return size_;
}

template<class T>
bool Vector<T>::empty() const
{
	return size_ == 0;
}

template<class T>
Iterator Vector<T>::begin()
{
	return buffer_;
}

template<class T>
Iterator Vector<T>::end()
{
	return buffer+size*sizeof(T);
}

template<class T>
T & Vector<T>::front()
{
	return buffer[0];
}

template<class T>
T & Vector<T>::back()
{
	return buffer_[size_ - 1];
}

template<class T>
void Vector<T>::push_back(const T & value)
{
	if (size_ >= capacity_)
	{
		reserve(capacity_*2)
	}
	size_++;
	buffer[size_] = value;
}

template<class T>
void Vector<T>::pop_back()
{
	(reinterpret_cast<T*>(buffer_)[size_ - 1]).~T();
	--size_;
}

template<class T>
void Vector<T>::reserve(size_type capacity)
{
	T * newBuffer = new T[capacity];

	for (size_type i = 0; i < size_; i++)
		newBuffer[i] = buffer_[i];
	capacity_ = capacity;
	delete[] buffer_;
	buffer_ = newBuffer;
}

template<class T>
void Vector<T>::resize(size_type capacity)
{
	capacity_ = capacity;
	reserve(capacity_);
}

template<class T>
T & Vector<T>::operator[](size_type index)
{
	return buffer_[index];
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>&)
{
	delete[] buffer;
	_size = v._size;
	Log = v.Log;
	_capacity = v._capacity;
	buffer = new T[_capacity];
	for (unsigned int i = 0; i < _size; i++)
		buffer[i] = v.buffer[i];
	return *this;	
}

template<class T>
void Vector<T>::clear()
{
	capacity_ = 0;
	size_ = 0;
	buffer_ = 0;
}
