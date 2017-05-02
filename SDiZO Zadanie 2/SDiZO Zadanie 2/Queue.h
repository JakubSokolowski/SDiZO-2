#pragma once

#include <cstddef>
#include <cstring>
#include <utility>
#include <iterator>
#include <stdexcept>
#include <iostream>



#define SDIZO_VECTOR_MAX_SIZE 1000000000

namespace DTS {

	template <typename T>
	class Queue {
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
		Queue() noexcept;
		explicit Queue(size_type n);
		Queue(size_type n, const T &val);
		Queue(typename Queue<T>::iterator first, typename Queue<T>::iterator last);
		Queue(const Queue<T> &);
		Queue(Queue<T> &&) noexcept;
		~Queue();
		Queue<T> & operator = (const Queue<T> &);
		Queue<T> & operator = (Queue<T> &&);

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
		reference GetFront();
		const_reference GetFront() const;



		void PushBack(const T &);
		void PushBack(T &&);
		void PopBack();
		void PopFront();



	private:
		size_type reserved_size_ = 4;
		size_type queue_size_ = 0;
		T *arr_;

		inline void reallocate();

	};


	//Creates new vector able to hold 4 elements of type T
	template <typename T>
	Queue<T>::Queue() noexcept {
		arr_ = new T[reserved_size_];
	}

	//Creates new vector able to hold n elements of type T.
	//Base constructor called for every created element
	template <typename T>
	Queue<T>::Queue(typename Queue<T>::size_type n) {
		size_type i;
		reserved_size_ = n << 2;
		arr_ = new T[reserved_size_];
		for (i = 0; i < n; ++i)
			arr_[i] = T();
		queue_size_ = n;
	}

	//Creates new vector able to hold n elements of type T.
	//Vector is filled with given value
	template <typename T>
	Queue<T>::Queue(typename Queue<T>::size_type n, const T &value) {
		size_type i;
		//Increases the capacity of vector 4 times
		reserved_size_ = n << 2;
		arr_ = new T[reserved_size_];
		for (i = 0; i < n; ++i)
			arr_[i] = value;
		queue_size_ = n;
	}

	//Creates new vector, fills it with elements 
	//between iterators
	template <typename T>
	Queue<T>::Queue(typename Queue<T>::iterator first, typename Queue<T>::iterator last) {
		size_type i, count = last - first;
		reserved_size_ = count << 2;
		arr_ = new T[reserved_size_];
		for (i = 0; i < count; ++i, ++first)
			arr_[i] = *first;
		queue_size_ = count;
	}

	//Copy Constructor
	template <typename T>
	Queue<T>::Queue(const Queue<T> &other) {
		size_type i;
		reserved_size_ = other.reserved_size_;
		arr_ = new T[reserved_size_];
		for (i = 0; i < other.queue_size_; ++i)
			arr_[i] = other.arr_[i];
		queue_size_ = other.queue_size_;
	}

	//Move Constructor
	template <typename T>
	Queue<T>::Queue(Queue<T> &&other) noexcept {
		size_type i;
		reserved_size_ = other.reserved_size_;
		arr_ = new T[reserved_size_];
		for (i = 0; i < other.queue_size_; ++i)
			arr_[i] = std::move(other.arr_[i]);
		queue_size_ = other.queue_size_;
	}

	//Destructor
	template <typename T>
	Queue<T>::~Queue() {
		delete[] arr_;
	}

	//Copy assignment operator
	template <typename T>
	Queue<T> & Queue<T>::operator = (const Queue<T> &other) {
		size_type i;
		if (reserved_size_ < other.queue_size_) {
			reserved_size_ = other.queue_size_ << 2;
			reallocate();
		}
		for (i = 0; i < other.queue_size_; ++i)
			arr_[i] = other.arr_[i];
		queue_size_ = other.queue_size_;
	}

	//Move assignment operator
	template <typename T>
	Queue<T> & Queue<T>::operator = (Queue<T> &&other) {
		size_type i;
		if (reserved_size_ < other.queue_size_) {
			reserved_size_ = other.queue_size_ << 2;
			reallocate();
		}
		for (i = 0; i < other.queue_size_; ++i)
			arr_[i] = std::move(other.arr_[i]);
		queue_size_ = other.queue_size_;
	}


	//Returns an iterator pointing to the first element in the sequence
	template <typename T>
	typename Queue<T>::iterator Queue<T>::begin() noexcept {
		return arr_;
	}

	//Returns a const iterator pointing to the first element in the sequence
	//Values pointed by const iterator cannot be modified
	template <typename T>
	typename Queue<T>::const_iterator Queue<T>::cbegin() const noexcept {
		return arr_;
	}

	//Returns an iterator pointing to the las element in the sequence
	template <typename T>
	typename Queue<T>::iterator Queue<T>::end() noexcept {
		return arr_ + queue_size_;
	}

	//Returns a const iterator pointing to the last element in the sequence
	//Values pointed by const iterator cannot be modified
	template <typename T>
	typename Queue<T>::const_iterator Queue<T>::cend() const noexcept {
		return arr_ + queue_size_;
	}

	//Returns a reverse iterator poining to the first element in the sequence 
	//(last element of vector)
	template <typename T>
	typename Queue<T>::reverse_iterator Queue<T>::rbegin() noexcept {
		return reverse_iterator(arr_ + queue_size_);
	}

	//Returns a const reverse iterator poining to the first element in the sequence 
	//(last element of vector). Values pointed by const iterator cannot be modified
	template <typename T>
	typename Queue<T>::const_reverse_iterator Queue<T>::crbegin() const noexcept {
		return reverse_iterator(arr_ + queue_size_);
	}

	//Returns a reverse iterator poining to the last element in the sequence 
	//(first element of vector)
	template <typename T>
	typename Queue<T>::reverse_iterator Queue<T>::rend() noexcept {
		return reverse_iterator(arr_);
	}

	//Returns a const reverse iterator poining to the last element in the sequence 
	//(first element of vector). Values pointed by const iterator cannot be modified
	template <typename T>
	typename Queue<T>::const_reverse_iterator Queue<T>::crend() const noexcept {
		return reverse_iterator(arr_);
	}

	//Reallocates array using memcpy, deletes the old array
	template <typename T>
	inline void Queue<T>::reallocate() {
		T *tarr = new T[reserved_size_];
		memcpy(tarr, arr_, queue_size_ * sizeof(T));
		delete[] arr_;
		arr_ = tarr;
	}

	//Returns true if number of elements in vector is equal to 0
	template <typename T>
	bool Queue<T>::IsEmpty() const noexcept {
		return queue_size_ == 0;
	}

	//Returns the number of elements in vector
	template <typename T>
	typename Queue<T>::size_type Queue<T>::GetSize() const noexcept {
		return queue_size_;
	}

	//Returns predefined max number of elements that can be stored in a vector
	template <typename T>
	typename Queue<T>::size_type Queue<T>::GetMaxSize() const noexcept {
		return SDIZO_VECTOR_MAX_SIZE;
	}

	//Returns the capacity of a vector - number of elements vector can hold
	template <typename T>
	typename Queue<T>::size_type Queue<T>::GetCapacity() const noexcept {
		return reserved_size_;
	}

	//Resizes the vector, so that it contains n elements.
	//When shrinking, deletes all the elements above n
	template <typename T>
	void Queue<T>::Resize(typename Queue<T>::size_type n) {
		if (n > queue_size_) {
			if (n > reserved_size_) {
				reserved_size_ = n;
				reallocate();
			}
		}
		else {
			size_type i;
			for (i = queue_size_; i < n; ++i)
				arr_[i].~T();
		}
		queue_size_ = n;
	}

	//Resizes the vector, so that it contains n elements. Val is copied to the new elements
	//When shrinking, deletes all the elements above n
	template <typename T>
	void Queue<T>::Resize(typename Queue<T>::size_type sz, const T &c) {
		if (sz > queue_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = queue_size_; i < sz; ++i)
				arr_[i] = c;
		}
		else {
			size_type i;
			for (i = queue_size_; i < sz; ++i)
				arr_[i].~T();
		}
		queue_size_ = sz;
	}

	//Requests that the vector capacity be at least enough to contain n elements
	//If n is greater then current capacity, function calls reallocate
	template <typename T>
	void Queue<T>::Reserve(typename Queue<T>::size_type _sz) {
		if (_sz > reserved_size_) {
			reserved_size_ = _sz;
			reallocate();
		}
	}

	//Requests the container to reduce its capacity to fit its size
	template <typename T>
	void Queue<T>::ShrinkToFit() {
		reserved_size_ = queue_size_;
		reallocate();
	}

	
	//Returns a reference to the first element in vector
	template <typename T>
	typename Queue<T>::reference Queue<T>::GetFront() {
		return arr_[0];
	}

	//Returns a const reference to the first element in vector
	template <typename T>
	typename Queue<T>::const_reference Queue<T>::GetFront() const {
		return arr_[0];
	}


	//Adds a new element at the end of a vector, after its current last element
	//The content of val is copied to the new element. Calls reallocate if needed
	template <typename T>
	void Queue<T>::PushBack(const T &val) {
		if (queue_size_ == reserved_size_) {
			reserved_size_ <<= 2;
			reallocate();
		}
		arr_[queue_size_] = val;
		++queue_size_;
	}

	//Adds a new element at the end of a vector, after its current last eleet
	//The content of val is moved to the new element. Calls reallocate if needed
	template <typename T>
	void Queue<T>::PushBack(T &&val) {
		if (queue_size_ == reserved_size_) {
			reserved_size_ <<= 2;
			reallocate();
		}
		arr_[queue_size_] = std::move(val);
		++queue_size_;
	}

	//Removes the current last element of a vector. Does not Reallocate
	template <typename T>
	void Queue<T>::PopBack() {
		--queue_size_;
		arr_[queue_size_].~T();
	}

	template<typename T>
	inline void Queue<T>::PopFront()
	{
		auto it = begin();
		arr_[0].~T();
		memmove(it, it + 1, (queue_size_ - (it - arr_) * sizeof(T)));
		--queue_size_;
	}
}
