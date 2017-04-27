#pragma once
template <class T>
class Vector
{
public:
	typedef T* iterator;
	typedef unsigned int size_type;

	Vector();
	Vector(size_type capacity);
	Vector(size_type size, const T & initial);
	Vector( Vector<T>& const v);
	virtual ~Vector();
	size_type capacity() const;
	size_type size() const;
	bool empty() const;

	iterator begin();
	iterator end();
	
	//TODO add const iterators


	T& front();
	T& back();
	void push_back(const T& value);
	void pop_back();

	void reserve(size_type capacity);
	void resize(size_type size);

	T & operator[](size_type index);
	Vector<T> & operator = (const Vector<T> &);
	void clear();
private:
	size_type size_;
	size_type capacity_;
	char *buffer_;
};

