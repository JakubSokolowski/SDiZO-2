#pragma once

#include <cstddef>
#include <cstring>
#include <utility>
#include <iterator>
#include <stdexcept>
#include <iostream>



#define SDIZO_VECTOR_MAX_SIZE 1000000000

namespace sdz {

template <typename T>
class Vector {
public:
		// types:
		typedef T                                     value_type;
		typedef T &                                   reference;
		typedef const T &                             const_reference;
		typedef T *                                   pointer;
		typedef const T *                             const_pointer;
		typedef T *                                   iterator;
		typedef const T *                             const_iterator;
		typedef std::reverse_iterator<iterator>       reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ptrdiff_t                             difference_type;
		typedef unsigned int                          size_type;

		// 23.3.11.2, construct/copy/destroy:
		Vector() noexcept;
		explicit Vector(size_type n);
		Vector(size_type n, const T &val);
		Vector(typename Vector<T>::iterator first, typename Vector<T>::iterator last);
		Vector(std::initializer_list<T>);
		Vector(const Vector<T> &);
		Vector(Vector<T> &&) noexcept;
		~Vector();
		Vector<T> & operator = (const Vector<T> &);
		Vector<T> & operator = (Vector<T> &&);
		Vector<T> & operator = (std::initializer_list<T>);
		void Assign(size_type, const T &value);
		void Assign(typename Vector<T>::iterator, typename Vector<T>::iterator);
		void Assign(std::initializer_list<T>);

		// iterators:
		iterator begin() noexcept;
		const_iterator cbegin() const noexcept;
		iterator end() noexcept;
		const_iterator cend() const noexcept;
		reverse_iterator rbegin() noexcept;
		const_reverse_iterator crbegin() const noexcept;
		reverse_iterator rend() noexcept;
		const_reverse_iterator crend() const noexcept;

		// 23.3.11.3, capacity:
		bool IsEmpty() const noexcept;
		size_type GetSize() const noexcept;
		size_type GetMaxSize() const noexcept;
		size_type GetCapacity() const noexcept;
		void Resize(size_type);
		void Resize(size_type, const T &);
		void Reserve(size_type);
		void ShrinkToFit();

		// element access
		reference operator [](size_type);
		const_reference operator [](size_type) const;
		reference Get(size_type);
		const_reference Get(size_type) const;
		reference GetFront();
		const_reference GetFront() const;
		reference GetBack();
		const_reference GetBack() const;

		// 23.3.11.4, data access:
		T * Data() noexcept;
		const T * Data() const noexcept;

		// 23.3.11.5, modifiers:
		template <class ... Args> void EmplaceBack(Args && ... args);
		void PushBack(const T &);
		void PushBack(T &&);
		void PopBack();

		template <class ... Args> iterator Emplace(const_iterator, Args && ...);
		iterator Insert(const_iterator, const T &);
		iterator Insert(const_iterator, T &&);
		iterator Insert(const_iterator, size_type, const T&);
		template <class InputIt> iterator Insert(const_iterator, InputIt, InputIt);
		iterator Insert(const_iterator, std::initializer_list<T>);
		iterator Erase(const_iterator);
		iterator Erase(const_iterator, const_iterator);
		void SwapVectors(Vector<T> &);
		void Clear() noexcept;

		bool operator == (const Vector<T> &) const;
		bool operator != (const Vector<T> &) const;
		bool operator < (const Vector<T> &) const;
		bool operator <= (const Vector<T> &) const;
		bool operator > (const Vector<T> &) const;
		bool operator >= (const Vector<T> &) const;

		//Utilty & Display
		void DisplayGraph() noexcept;

	private:
		size_type reserved_size_ = 4;
		size_type vector_size_ = 0;
		T *arr_;

		inline void reallocate();

	};


	//Creates new vector able to hold 4 elements of type T
	template <typename T>
	Vector<T>::Vector() noexcept {
		arr_ = new T[reserved_size_];
	}

	//Creates new vector able to hold n elements of type T.
	//Base constructor called for every created element
	template <typename T>
	Vector<T>::Vector(typename Vector<T>::size_type n) {
		size_type i;
		reserved_size_ = n << 2;
		arr_ = new T[reserved_size_];
		for (i = 0; i < n; ++i)
			arr_[i] = T();
		vector_size_ = n;
	}

	//Creates new vector able to hold n elements of type T.
	//Vector is filled with given value
	template <typename T>
	Vector<T>::Vector(typename Vector<T>::size_type n, const T &value) {
		size_type i;
		//Increases the capacity of vector 4 times
		reserved_size_ = n << 2;
		arr_ = new T[reserved_size_];
		for (i = 0; i < n; ++i)
			arr_[i] = value;
		vector_size_ = n;
	}

	//Creates new vector, fills it with elements 
	//between iterators
	template <typename T>
	Vector<T>::Vector(typename Vector<T>::iterator first, typename Vector<T>::iterator last) {
		size_type i, count = last - first;
		reserved_size_ = count << 2;
		arr_ = new T[reserved_size_];
		for (i = 0; i < count; ++i, ++first)
			arr_[i] = *first;
		vector_size_ = count;
	}

	//Creates new vector, fills it with elements from initializer_list
	template <typename T>
	Vector<T>::Vector(std::initializer_list<T> list) {
		reserved_size_ = list.size() << 2;
		arr_ = new T[reserved_size_];
		for (auto &item : list)
			arr_[vector_size_++] = item;
	}

	//Copy Constructor
	template <typename T>
	Vector<T>::Vector(const Vector<T> &other) {
		size_type i;
		reserved_size_ = other.reserved_size_;
		arr_ = new T[reserved_size_];
		for (i = 0; i < other.vector_size_; ++i)
			arr_[i] = other.arr_[i];
		vector_size_ = other.vector_size_;
	}

	//Move Constructor
	template <typename T>
	Vector<T>::Vector(Vector<T> &&other) noexcept {
		size_type i;
		reserved_size_ = other.reserved_size_;
		arr_ = new T[reserved_size_];
		for (i = 0; i < other.vector_size_; ++i)
			arr_[i] = std::move(other.arr_[i]);
		vector_size_ = other.vector_size_;
	}

	//Destructor
	template <typename T>
	Vector<T>::~Vector() {
		delete[] arr_;
	}

	//Copy assignment operator
	template <typename T>
	Vector<T> & Vector<T>::operator = (const Vector<T> &other) {
		size_type i;
		if (reserved_size_ < other.vector_size_) {
			reserved_size_ = other.vector_size_ << 2;
			reallocate();
		}
		for (i = 0; i < other.vector_size_; ++i)
			arr_[i] = other.arr_[i];
		vector_size_ = other.vector_size_;
	}

	//Move assignment operator
	template <typename T>
	Vector<T> & Vector<T>::operator = (Vector<T> &&other) {
		size_type i;
		if (reserved_size_ < other.vector_size_) {
			reserved_size_ = other.vector_size_ << 2;
			reallocate();
		}
		for (i = 0; i < other.vector_size_; ++i)
			arr_[i] = std::move(other.arr_[i]);
		vector_size_ = other.vector_size_;
		return (*this);
	}

	//Initializer list assignment operator
	template <typename T>
	Vector<T> & Vector<T>::operator = (std::initializer_list<T> list) {
		if (reserved_size_ < list.size()) {
			reserved_size_ = list.size() << 2;
			reallocate();
		}
		vector_size_ = 0;
		for (auto &item : list)
			arr_[vector_size_++] = item;
	}

	//Assigns new contents to the vector, replacing its current contents, and modifying 
	//its size accordingly
	//Count - number of new elements, &value - reference to new value
	template <typename T>
	void Vector<T>::Assign(typename Vector<T>::size_type count, const T &value) {
		size_type i;
		if (count > reserved_size_) {
			reserved_size_ = count << 2;
			reallocate();
		}
		for (i = 0; i < count; ++i)
			arr_[i] = value;
		vector_size_ = count;
	}

	//Assigns new contents to the vector, replacing its current contents, and modifying 
	//its size accordingly.
	//Elements to assign pointed by first and last iterators.
	template <typename T>
	void Vector<T>::Assign(typename Vector<T>::iterator first, typename Vector<T>::iterator last) {
		size_type i, count = last - first;
		if (count > reserved_size_) {
			reserved_size_ = count << 2;
			reallocate();
		}
		for (i = 0; i < count; ++i, ++first)
			arr_[i] = *first;
		vector_size_ = count;
	}

	//Assigns new contents to the vector, replacing its current contents, and modifying 
	//its size accordingly.
	//Elements to assign given by std::initializer_list
	template <typename T>
	void Vector<T>::Assign(std::initializer_list<T> list) {
		size_type i, count = list.size();
		if (count > reserved_size_) {
			reserved_size_ = count << 2;
			reallocate();
		}
		i = 0;
		for (auto &item : list)
			arr_[i++] = item;
	}

	//Returns an iterator pointing to the first element in the sequence
	template <typename T>
	typename Vector<T>::iterator Vector<T>::begin() noexcept {
		return arr_;
	}

	//Returns a const iterator pointing to the first element in the sequence
	//Values pointed by const iterator cannot be modified
	template <typename T>
	typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept {
		return arr_;
	}

	//Returns an iterator pointing to the las element in the sequence
	template <typename T>
	typename Vector<T>::iterator Vector<T>::end() noexcept {
		return arr_ + vector_size_;
	}

	//Returns a const iterator pointing to the last element in the sequence
	//Values pointed by const iterator cannot be modified
	template <typename T>
	typename Vector<T>::const_iterator Vector<T>::cend() const noexcept {
		return arr_ + vector_size_;
	}

	//Returns a reverse iterator poining to the first element in the sequence 
	//(last element of vector)
	template <typename T>
	typename Vector<T>::reverse_iterator Vector<T>::rbegin() noexcept {
		return reverse_iterator(arr_ + vector_size_);
	}

	//Returns a const reverse iterator poining to the first element in the sequence 
	//(last element of vector). Values pointed by const iterator cannot be modified
	template <typename T>
	typename Vector<T>::const_reverse_iterator Vector<T>::crbegin() const noexcept {
		return reverse_iterator(arr_ + vector_size_);
	}

	//Returns a reverse iterator poining to the last element in the sequence 
	//(first element of vector)
	template <typename T>
	typename Vector<T>::reverse_iterator Vector<T>::rend() noexcept {
		return reverse_iterator(arr_);
	}

	//Returns a const reverse iterator poining to the last element in the sequence 
	//(first element of vector). Values pointed by const iterator cannot be modified
	template <typename T>
	typename Vector<T>::const_reverse_iterator Vector<T>::crend() const noexcept {
		return reverse_iterator(arr_);
	}

	//Reallocates array using memcpy, deletes the old array
	template <typename T>
	inline void Vector<T>::reallocate() {
		T *tarr = new T[reserved_size_];
		memcpy(tarr, arr_, vector_size_ * sizeof(T));
		delete[] arr_;
		arr_ = tarr;
	}

	//Returns true if number of elements in vector is equal to 0
	template <typename T>
	bool Vector<T>::IsEmpty() const noexcept {
		return vector_size_ == 0;
	}

	//Returns the number of elements in vector
	template <typename T>
	typename Vector<T>::size_type Vector<T>::GetSize() const noexcept {
		return vector_size_;
	}

	//Returns predefined max number of elements that can be stored in a vector
	template <typename T>
	typename Vector<T>::size_type Vector<T>::GetMaxSize() const noexcept {
		return SDIZO_VECTOR_MAX_SIZE;
	}

	//Returns the capacity of a vector - number of elements vector can hold
	template <typename T>
	typename Vector<T>::size_type Vector<T>::GetCapacity() const noexcept {
		return reserved_size_;
	}

	//Resizes the vector, so that it contains n elements.
	//When shrinking, deletes all the elements above n
	template <typename T>
	void Vector<T>::Resize(typename Vector<T>::size_type n) {
		if (n > vector_size_) {
			if (n > reserved_size_) {
				reserved_size_ = n;
				reallocate();
			}
		}
		else {
			size_type i;
			for (i = vector_size_; i < n; ++i)
				arr_[i].~T();
		}
		vector_size_ = n;
	}

	//Resizes the vector, so that it contains n elements. Val is copied to the new elements
	//When shrinking, deletes all the elements above n
	template <typename T>
	void Vector<T>::Resize(typename Vector<T>::size_type sz, const T &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		else {
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i].~T();
		}
		vector_size_ = sz;
	}

	//Requests that the vector capacity be at least enough to contain n elements
	//If n is greater then current capacity, function calls reallocate
	template <typename T>
	void Vector<T>::Reserve(typename Vector<T>::size_type _sz) {
		if (_sz > reserved_size_) {
			reserved_size_ = _sz;
			reallocate();
		}
	}

	//Requests the container to reduce its capacity to fit its size
	template <typename T>
	void Vector<T>::ShrinkToFit() {
		reserved_size_ = vector_size_;
		reallocate();
	}

	//Returns reference to the object at index. Does not perform bound checks
	template <typename T>
	typename Vector<T>::reference Vector<T>::operator [](typename Vector<T>::size_type index) {
		return arr_[index];
	}

	//Returns const reference to the object at index. Does not perform bound checks
	template <typename T>
	typename Vector<T>::const_reference Vector<T>::operator [](typename Vector<T>::size_type index) const {
		return arr_[index];
	}

	//Returns reference to the object at index. Performs bound checks and throws std::out_of_range if out of bounds
	template <typename T>
	typename Vector<T>::reference Vector<T>::Get(size_type pos) {
		if (pos < vector_size_)
			return arr_[pos];
		else
			throw std::out_of_range("accessed position is out of range");
	}

	//Returns const reference to the object at index. Performs bound checks and throws std::out_of_range if out of bounds
	template <typename T>
	typename Vector<T>::const_reference Vector<T>::Get(size_type pos) const {
		if (pos < vector_size_)
			return arr_[pos];
		else
			throw std::out_of_range("accessed position is out of range");
	}

	//Returns a reference to the first element in vector
	template <typename T>
	typename Vector<T>::reference Vector<T>::GetFront() {
		return arr_[0];
	}

	//Returns a const reference to the first element in vector
	template <typename T>
	typename Vector<T>::const_reference Vector<T>::GetFront() const {
		return arr_[0];
	}

	//Returns a reference to the last element in vector
	template <typename T>
	typename Vector<T>::reference Vector<T>::GetBack() {
		return arr_[vector_size_ - 1];
	}

	//Returns a const reference to the last element in vector
	template <typename T>
	typename Vector<T>::const_reference Vector<T>::GetBack() const {
		return arr_[vector_size_ - 1];
	}

	//Returns a pointer to the array used internally by the vector to store its owned elements
	template <typename T>
	T * Vector<T>::Data() noexcept {
		return arr_;
	}

	//Returns a pointer to const value array 
	template <typename T>
	const T * Vector<T>::Data() const noexcept {
		return arr_;
	}

	//Adds a new element at the end of a vector, after its current last element
	//The new elemetn is constructed in-place using args. Calls reallocate if needed
	template <typename T>
	template <class ... Args>
	void Vector<T>::EmplaceBack(Args && ... args) {
		if (vector_size_ == reserved_size_) {
			reserved_size_ <<= 2;
			reallocate();
		}
		arr_[vector_size_] = std::move(T(std::forward<Args>(args) ...));
		++vector_size_;
	}

	//Adds a new element at the end of a vector, after its current last element
	//The content of val is copied to the new element. Calls reallocate if needed
	template <typename T>
	void Vector<T>::PushBack(const T &val) {
		if (vector_size_ == reserved_size_) {
			reserved_size_ <<= 2;
			reallocate();
		}
		arr_[vector_size_] = val;
		++vector_size_;
	}

	//Adds a new element at the end of a vector, after its current last eleet
	//The content of val is moved to the new element. Calls reallocate if needed
	template <typename T>
	void Vector<T>::PushBack(T &&val) {
		if (vector_size_ == reserved_size_) {
			reserved_size_ <<= 2;
			reallocate();
		}
		arr_[vector_size_] = std::move(val);
		++vector_size_;
	}

	//Removes the current last element of a vector. Does not Reallocate
	template <typename T>
	void Vector<T>::PopBack() {
		--vector_size_;
		arr_[vector_size_].~T();
	}

	//Inserts a new element at position, new element is constructed in place using args
	template <typename T>
	template <class ... Args>
	typename Vector<T>::iterator Vector<T>::Emplace(typename Vector<T>::const_iterator it, Args && ... args) {
		iterator iit = &arr_[it - arr_];
		if (vector_size_ == reserved_size_) {
			reserved_size_ <<= 2;
			reallocate();
		}
		memmove(iit + 1, iit, (vector_size_ - (it - arr_)) * sizeof(T));
		(*iit) = std::move(T(std::forward<Args>(args) ...));
		++vector_size_;
		return iit;
	}

	//The vector is extended by inserting new elements before the element at the specified position
	//The elements added are copied. Reallocates if needed
	//Returns an iterator that points to the first of newly inserted elements
	template <typename T>
	typename Vector<T>::iterator Vector<T>::Insert(typename Vector<T>::const_iterator it, const T &val) {
		iterator iit = &arr_[it - arr_];
		if (vector_size_ == reserved_size_) {
			reserved_size_ <<= 2;
			reallocate();
		}
		memmove(iit + 1, iit, (vector_size_ - (it - arr_)) * sizeof(T));
		(*iit) = val;
		++vector_size_;
		return iit;
	}

	//The vector is extended by inserting new element before the element at the specified by iterator
	//The element added is moved using std::move . Reallocates if needed
	//Returns an iterator that points to the first of newly inserted element
	template <typename T>
	typename Vector<T>::iterator Vector<T>::Insert(typename Vector<T>::const_iterator it, T &&val) {
		iterator iit = &arr_[it - arr_];
		if (vector_size_ == reserved_size_) {
			reserved_size_ <<= 2;
			reallocate();
		}
		memmove(iit + 1, iit, (vector_size_ - (it - arr_)) * sizeof(T));
		(*iit) = std::move(val);
		++vector_size_;
		return iit;
	}

	//The vector is extended by inserting new elements before the element at the specified by iterator
	//The number of elements added is specified by cnt. The elements are copied from val. Reallocates if needed
	//Returns an iterator that points to the first of newly inserted elements
	template <typename T>
	typename Vector<T>::iterator Vector<T>::Insert(typename Vector<T>::const_iterator it, typename Vector<T>::size_type cnt, const T &val) {
		iterator f = &arr_[it - arr_];
		if (!cnt) return f;
		if (vector_size_ + cnt > reserved_size_) {
			reserved_size_ = (vector_size_ + cnt) << 2;
			reallocate();
		}
		memmove(f + cnt, f, (vector_size_ - (it - arr_)) * sizeof(T));
		vector_size_ += cnt;
		for (iterator it = f; cnt--; ++it)
			(*it) = val;
		return f;
	}

	//The vector is extended by inserting new elements before the element at the specified by iterator it
	//The number of elements added is specified by subtraction of iterators. The values are pointed by iterators
	//Returns an iterator that points to the first of newly inserted elements
	template <typename T>
	template <class InputIt>
	typename Vector<T>::iterator Vector<T>::Insert(typename Vector<T>::const_iterator it, InputIt first, InputIt last) {
		iterator f = &arr_[it - arr_];
		size_type cnt = last - first;
		if (!cnt) return f;
		if (vector_size_ + cnt > reserved_size_) {
			reserved_size_ = (vector_size_ + cnt) << 2;
			reallocate();
		}
		memmove(f + cnt, f, (vector_size_ - (it - arr_)) * sizeof(T));
		for (iterator it = f; first != last; ++it, ++first)
			(*it) = *first;
		vector_size_ += cnt;
		return f;
	}

	//The vector is extended by inserting new elements before the element at the specified by iterator
	//The number and values of iterators are specified by initializer_list
	//Returns an iterator that points to the first of newly inserted elements
	template <typename T>
	typename Vector<T>::iterator Vector<T>::Insert(typename Vector<T>::const_iterator it, std::initializer_list<T> lst) {
		size_type cnt = lst.size();
		iterator f = &arr_[it - arr_];
		if (!cnt) return f;
		if (vector_size_ + cnt > reserved_size_) {
			reserved_size_ = (vector_size_ + cnt) << 2;
			reallocate();
		}
		memmove(f + cnt, f, (vector_size_ - (it - arr_)) * sizeof(T));
		iterator iit = f;
		for (auto &item : lst) {
			(*iit) = item;
			++iit;
		}
		vector_size_ += cnt;
		return f;
	}

	//Removes single element from vector
	//Returns an iterator pointing to the new location of the element that followed the last element erased by the function call.
	template <typename T>
	typename Vector<T>::iterator Vector<T>::Erase(typename Vector<T>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		(*iit).~T();
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(T));
		--vector_size_;
		return iit;
	}

	//Removes range of elements ([first,last])
	//Returns an iterator pointing to the new location of the element that followed the last element erased by the function call.
	template <typename T>
	typename Vector<T>::iterator Vector<T>::Erase(typename Vector<T>::const_iterator first, typename Vector<T>::const_iterator last) {
		iterator f = &arr_[first - arr_];
		if (first == last) return f;
		for (; first != last; ++first)
			(*first).~T();
		memmove(f, last, (vector_size_ - (last - arr_)) * sizeof(T));
		vector_size_ -= last - first;
		return f;
	}

	//Exchanges the contents of vectors
	template <typename T>
	void Vector<T>::SwapVectors(Vector<T> &rhs) {
		size_t tvec_sz = vector_size_,
			trsrv_sz = reserved_size_;
		T *tarr = arr_;

		vector_size_ = rhs.vector_size_;
		reserved_size_ = rhs.reserved_size_;
		arr_ = rhs.arr_;

		rhs.vector_size_ = tvec_sz;
		rhs.reserved_size_ = trsrv_sz;
		rhs.arr_ = tarr;
	}

	//Removes and destroys all elements from vector, leaving the container with size of 0
	template <typename T>
	void Vector<T>::Clear() noexcept {
		size_type i;
		for (i = 0; i < vector_size_; ++i)
			arr_[i].~T();
		vector_size_ = 0;
	}

	//Compares sizes and elements, returns true if they match
	template <typename T>
	bool Vector<T>::operator == (const Vector<T> &rhs) const {
		if (vector_size_ != rhs.vector_size_) return false;
		size_type i;
		for (i = 0; i < vector_size_; ++i)
			if (arr_[i] != rhs.arr_[i])
				return false;
		return true;
	}

	//Compares sizes and elements, returns true if they mismatch
	template <typename T>
	bool Vector<T>::operator != (const Vector<T> &rhs) const {
		if (vector_size_ != rhs.vector_size_) return true;
		size_type i;
		for (i = 0; i < vector_size_; ++i)
			if (arr_[i] != rhs.arr_[i])
				return true;
		return false;
	}

	template <typename T>
	bool Vector<T>::operator < (const Vector<T> &rhs) const {
		size_type i, j, ub = vector_size_ < rhs.vector_size_ ? vector_size_ : rhs.vector_size_;
		for (i = 0; i < ub; ++i)
			if (arr_[i] != rhs.arr_[i])
				return arr_[i] < rhs.arr_[i];
		return vector_size_ < rhs.vector_size_;
	}

	template <typename T>
	bool Vector<T>::operator <= (const Vector<T> &rhs) const {
		size_type i, j, ub = vector_size_ < rhs.vector_size_ ? vector_size_ : rhs.vector_size_;
		for (i = 0; i < ub; ++i)
			if (arr_[i] != rhs.arr_[i])
				return arr_[i] < rhs.arr_[i];
		return vector_size_ <= rhs.vector_size_;
	}

	template <typename T>
	bool Vector<T>::operator > (const Vector<T> &rhs) const {
		size_type i, j, ub = vector_size_ < rhs.vector_size_ ? vector_size_ : rhs.vector_size_;
		for (i = 0; i < ub; ++i)
			if (arr_[i] != rhs.arr_[i])
				return arr_[i] > rhs.arr_[i];
		return vector_size_ > rhs.vector_size_;
	}

	template <typename T>
	bool Vector<T>::operator >= (const Vector<T> &rhs) const {
		size_type i, j, ub = vector_size_ < rhs.vector_size_ ? vector_size_ : rhs.vector_size_;
		for (i = 0; i < ub; ++i)
			if (arr_[i] != rhs.arr_[i])
				return arr_[i] > rhs.arr_[i];
		return vector_size_ >= rhs.vector_size_;
	}
	
	//Displays size, capacity and all the elements separted by whitespace
	template<typename T>
	inline void Vector<T>::DisplayGraph() noexcept
	{
		std::cout << "Size: " << vector_size_ << " Capacity: " << GetCapacity();
		for (auto iter = cbegin(); iter != cend(); iter++)
			std::cout << *iter << " ";
	}



	template <>
	void Vector<bool>::Resize(typename Vector<bool>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<signed char>::Resize(typename Vector<signed char>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<unsigned char>::Resize(typename Vector<unsigned char>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<char>::Resize(typename Vector<char>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<short int>::Resize(typename Vector<short int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<unsigned short int>::Resize(typename Vector<unsigned short int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<int>::Resize(typename Vector<int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<unsigned int>::Resize(typename Vector<unsigned int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<long int>::Resize(typename Vector<long int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<unsigned long int>::Resize(typename Vector<unsigned long int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<long long int>::Resize(typename Vector<long long int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<unsigned long long int>::Resize(typename Vector<unsigned long long int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<float>::Resize(typename Vector<float>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<double>::Resize(typename Vector<double>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<long double>::Resize(typename Vector<long double>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}


	template <>
	void Vector<bool>::Resize(typename Vector<bool>::size_type sz, const bool &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<signed char>::Resize(typename Vector<signed char>::size_type sz, const signed char &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<unsigned char>::Resize(typename Vector<unsigned char>::size_type sz, const unsigned char &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<char>::Resize(typename Vector<char>::size_type sz, const char &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<short int>::Resize(typename Vector<short int>::size_type sz, const short int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<unsigned short int>::Resize(typename Vector<unsigned short int>::size_type sz, const unsigned short int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<int>::Resize(typename Vector<int>::size_type sz, const int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<unsigned int>::Resize(typename Vector<unsigned int>::size_type sz, const unsigned int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<long int>::Resize(typename Vector<long int>::size_type sz, const long int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<unsigned long int>::Resize(typename Vector<unsigned long int>::size_type sz, const unsigned long int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<long long int>::Resize(typename Vector<long long int>::size_type sz, const long long int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<unsigned long long int>::Resize(typename Vector<unsigned long long int>::size_type sz, const unsigned long long int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<float>::Resize(typename Vector<float>::size_type sz, const float &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<double>::Resize(typename Vector<double>::size_type sz, const double &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void Vector<long double>::Resize(typename Vector<long double>::size_type sz, const long double &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr_[i] = c;
		}
		vector_size_ = sz;
	}


	template <>
	void Vector<bool>::PopBack() {
		--vector_size_;
	}

	template <>
	void Vector<signed char>::PopBack() {
		--vector_size_;
	}

	template <>
	void Vector<unsigned char>::PopBack() {
		--vector_size_;
	}

	template <>
	void Vector<char>::PopBack() {
		--vector_size_;
	}

	template <>
	void Vector<short int>::PopBack() {
		--vector_size_;
	}

	template <>
	void Vector<unsigned short int>::PopBack() {
		--vector_size_;
	}

	template <>
	void Vector<int>::PopBack() {
		--vector_size_;
	}

	template <>
	void Vector<unsigned int>::PopBack() {
		--vector_size_;
	}

	template <>
	void Vector<long int>::PopBack() {
		--vector_size_;
	}

	template <>
	void Vector<unsigned long int>::PopBack() {
		--vector_size_;
	}

	template <>
	void Vector<long long int>::PopBack() {
		--vector_size_;
	}

	template <>
	void Vector<unsigned long long int>::PopBack() {
		--vector_size_;
	}

	template <>
	void Vector<float>::PopBack() {
		--vector_size_;
	}

	template <>
	void Vector<double>::PopBack() {
		--vector_size_;
	}

	template <>
	void Vector<long double>::PopBack() {
		--vector_size_;
	}


	template <>
	typename Vector<bool>::iterator Vector<bool>::Erase(typename Vector<bool>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(bool));
		--vector_size_;
		return iit;
	}

	template <>
	typename Vector<signed char>::iterator Vector<signed char>::Erase(typename Vector<signed char>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(signed char));
		--vector_size_;
		return iit;
	}

	template <>
	typename Vector<unsigned char>::iterator Vector<unsigned char>::Erase(typename Vector<unsigned char>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(unsigned char));
		--vector_size_;
		return iit;
	}

	template <>
	typename Vector<char>::iterator Vector<char>::Erase(typename Vector<char>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(char));
		--vector_size_;
		return iit;
	}

	template <>
	typename Vector<short int>::iterator Vector<short int>::Erase(typename Vector<short int>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(short int));
		--vector_size_;
		return iit;
	}

	template <>
	typename Vector<unsigned short int>::iterator Vector<unsigned short int>::Erase(typename Vector<unsigned short int>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(unsigned short int));
		--vector_size_;
		return iit;
	}

	template <>
	typename Vector<int>::iterator Vector<int>::Erase(typename Vector<int>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(int));
		--vector_size_;
		return iit;
	}

	template <>
	typename Vector<unsigned int>::iterator Vector<unsigned int>::Erase(typename Vector<unsigned int>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(unsigned int));
		--vector_size_;
		return iit;
	}

	template <>
	typename Vector<long int>::iterator Vector<long int>::Erase(typename Vector<long int>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(long int));
		--vector_size_;
		return iit;
	}

	template <>
	typename Vector<unsigned long int>::iterator Vector<unsigned long int>::Erase(typename Vector<unsigned long int>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(unsigned long int));
		--vector_size_;
		return iit;
	}

	template <>
	typename Vector<long long int>::iterator Vector<long long int>::Erase(typename Vector<long long int>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(long long int));
		--vector_size_;
		return iit;
	}

	template <>
	typename Vector<unsigned long long int>::iterator Vector<unsigned long long int>::Erase(typename Vector<unsigned long long int>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(unsigned long long int));
		--vector_size_;
		return iit;
	}

	template <>
	typename Vector<float>::iterator Vector<float>::Erase(typename Vector<float>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(float));
		--vector_size_;
		return iit;
	}

	template <>
	typename Vector<double>::iterator Vector<double>::Erase(typename Vector<double>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(double));
		--vector_size_;
		return iit;
	}

	template <>
	typename Vector<long double>::iterator Vector<long double>::Erase(typename Vector<long double>::const_iterator it) {
		iterator iit = &arr_[it - arr_];
		memmove(iit, iit + 1, (vector_size_ - (it - arr_) - 1) * sizeof(long double));
		--vector_size_;
		return iit;
	}


	template <>
	typename Vector<bool>::iterator Vector<bool>::Erase(typename Vector<bool>::const_iterator first, typename Vector<bool>::const_iterator last) {
		iterator f = &arr_[first - arr_];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr_)) * sizeof(bool));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename Vector<signed char>::iterator Vector<signed char>::Erase(typename Vector<signed char>::const_iterator first, typename Vector<signed char>::const_iterator last) {
		iterator f = &arr_[first - arr_];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr_)) * sizeof(signed char));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename Vector<unsigned char>::iterator Vector<unsigned char>::Erase(typename Vector<unsigned char>::const_iterator first, typename Vector<unsigned char>::const_iterator last) {
		iterator f = &arr_[first - arr_];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr_)) * sizeof(unsigned char));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename Vector<char>::iterator Vector<char>::Erase(typename Vector<char>::const_iterator first, typename Vector<char>::const_iterator last) {
		iterator f = &arr_[first - arr_];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr_)) * sizeof(char));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename Vector<short int>::iterator Vector<short int>::Erase(typename Vector<short int>::const_iterator first, typename Vector<short int>::const_iterator last) {
		iterator f = &arr_[first - arr_];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr_)) * sizeof(short int));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename Vector<unsigned short int>::iterator Vector<unsigned short int>::Erase(typename Vector<unsigned short int>::const_iterator first, typename Vector<unsigned short int>::const_iterator last) {
		iterator f = &arr_[first - arr_];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr_)) * sizeof(unsigned short int));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename Vector<int>::iterator Vector<int>::Erase(typename Vector<int>::const_iterator first, typename Vector<int>::const_iterator last) {
		iterator f = &arr_[first - arr_];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr_)) * sizeof(int));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename Vector<unsigned int>::iterator Vector<unsigned int>::Erase(typename Vector<unsigned int>::const_iterator first, typename Vector<unsigned int>::const_iterator last) {
		iterator f = &arr_[first - arr_];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr_)) * sizeof(unsigned int));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename Vector<long long int>::iterator Vector<long long int>::Erase(typename Vector<long long int>::const_iterator first, typename Vector<long long int>::const_iterator last) {
		iterator f = &arr_[first - arr_];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr_)) * sizeof(long long int));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename Vector<unsigned long long int>::iterator Vector<unsigned long long int>::Erase(typename Vector<unsigned long long int>::const_iterator first, typename Vector<unsigned long long int>::const_iterator last) {
		iterator f = &arr_[first - arr_];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr_)) * sizeof(unsigned long long int));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename Vector<float>::iterator Vector<float>::Erase(typename Vector<float>::const_iterator first, typename Vector<float>::const_iterator last) {
		iterator f = &arr_[first - arr_];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr_)) * sizeof(float));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename Vector<double>::iterator Vector<double>::Erase(typename Vector<double>::const_iterator first, typename Vector<double>::const_iterator last) {
		iterator f = &arr_[first - arr_];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr_)) * sizeof(double));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename Vector<long double>::iterator Vector<long double>::Erase(typename Vector<long double>::const_iterator first, typename Vector<long double>::const_iterator last) {
		iterator f = &arr_[first - arr_];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr_)) * sizeof(long double));
		vector_size_ -= last - first;
		return f;
	}


	template <>
	void Vector<bool>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void Vector<signed char>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void Vector<unsigned char>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void Vector<char>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void Vector<short int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void Vector<unsigned short int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void Vector<int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void Vector<unsigned int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void Vector<long int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void Vector<unsigned long int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void Vector<long long int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void Vector<unsigned long long int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void Vector<float>::Clear() noexcept {
		vector_size_ = 0;
	}
	//ipla
	template <>
	void Vector<double>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void Vector<long double>::Clear() noexcept {
		vector_size_ = 0;
	}


}


