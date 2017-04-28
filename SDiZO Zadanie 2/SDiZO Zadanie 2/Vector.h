#pragma once

#include <cstddef>
#include <cstring>
#include <utility>
#include <iterator>
#include <stdexcept>
#include <iostream>



#define SDIZO_VECTOR_MAX_SIZE 1000000000

namespace sdizo {

	template <typename T>
class vector {
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
		vector() noexcept;
		explicit vector(size_type n);
		vector(size_type n, const T &val);
		vector(typename vector<T>::iterator first, typename vector<T>::iterator last);
		vector(std::initializer_list<T>);
		vector(const vector<T> &);
		vector(vector<T> &&) noexcept;
		~vector();
		vector<T> & operator = (const vector<T> &);
		vector<T> & operator = (vector<T> &&);
		vector<T> & operator = (std::initializer_list<T>);
		void Assign(size_type, const T &value);
		void Assign(typename vector<T>::iterator, typename vector<T>::iterator);
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
		T * data() noexcept;
		const T * data() const noexcept;

		// 23.3.11.5, modifiers:
		template <class ... Args> void emplace_back(Args && ... args);
		void PushBack(const T &);
		void PushBack(T &&);
		void PopBack();

		template <class ... Args> iterator emplace(const_iterator, Args && ...);
		iterator Insert(const_iterator, const T &);
		iterator Insert(const_iterator, T &&);
		iterator Insert(const_iterator, size_type, const T&);
		template <class InputIt> iterator Insert(const_iterator, InputIt, InputIt);
		iterator Insert(const_iterator, std::initializer_list<T>);
		iterator Erase(const_iterator);
		iterator Erase(const_iterator, const_iterator);
		void SwapVectors(vector<T> &);
		void Clear() noexcept;

		bool operator == (const vector<T> &) const;
		bool operator != (const vector<T> &) const;
		bool operator < (const vector<T> &) const;
		bool operator <= (const vector<T> &) const;
		bool operator > (const vector<T> &) const;
		bool operator >= (const vector<T> &) const;

		//Utilty & Display
		void Display() noexcept;

	private:
		size_type reserved_size_ = 4;
		size_type vector_size_ = 0;
		T *arr;

		inline void reallocate();

	};



	template <typename T>
	vector<T>::vector() noexcept {
		arr = new T[reserved_size_];
	}

	template <typename T>
	vector<T>::vector(typename vector<T>::size_type n) {
		size_type i;
		reserved_size_ = n << 2;
		arr = new T[reserved_size_];
		for (i = 0; i < n; ++i)
			arr[i] = T();
		vector_size_ = n;
	}

	template <typename T>
	vector<T>::vector(typename vector<T>::size_type n, const T &value) {
		size_type i;
		reserved_size_ = n << 2;
		arr = new T[reserved_size_];
		for (i = 0; i < n; ++i)
			arr[i] = value;
		vector_size_ = n;
	}

	template <typename T>
	vector<T>::vector(typename vector<T>::iterator first, typename vector<T>::iterator last) {
		size_type i, count = last - first;
		reserved_size_ = count << 2;
		arr = new T[reserved_size_];
		for (i = 0; i < count; ++i, ++first)
			arr[i] = *first;
		vector_size_ = count;
	}

	template <typename T>
	vector<T>::vector(std::initializer_list<T> lst) {
		reserved_size_ = lst.GetSize() << 2;
		arr = new T[reserved_size_];
		for (auto &item : lst)
			arr[vector_size_++] = item;
	}

	template <typename T>
	vector<T>::vector(const vector<T> &other) {
		size_type i;
		reserved_size_ = other.reserved_size_;
		arr = new T[reserved_size_];
		for (i = 0; i < other.vector_size_; ++i)
			arr[i] = other.arr[i];
		vector_size_ = other.vector_size_;
	}

	template <typename T>
	vector<T>::vector(vector<T> &&other) noexcept {
		size_type i;
		reserved_size_ = other.reserved_size_;
		arr = new T[reserved_size_];
		for (i = 0; i < other.vector_size_; ++i)
			arr[i] = std::move(other.arr[i]);
		vector_size_ = other.vector_size_;
	}

	template <typename T>
	vector<T>::~vector() {
		delete[] arr;
	}

	template <typename T>
	vector<T> & vector<T>::operator = (const vector<T> &other) {
		size_type i;
		if (reserved_size_ < other.vector_size_) {
			reserved_size_ = other.vector_size_ << 2;
			reallocate();
		}
		for (i = 0; i < other.vector_size_; ++i)
			arr[i] = other.arr[i];
		vector_size_ = other.vector_size_;
	}

	template <typename T>
	vector<T> & vector<T>::operator = (vector<T> &&other) {
		size_type i;
		if (reserved_size_ < other.vector_size_) {
			reserved_size_ = other.vector_size_ << 2;
			reallocate();
		}
		for (i = 0; i < other.vector_size_; ++i)
			arr[i] = std::move(other.arr[i]);
		vector_size_ = other.vector_size_;
	}

	template <typename T>
	vector<T> & vector<T>::operator = (std::initializer_list<T> lst) {
		if (reserved_size_ < lst.GetSize()) {
			reserved_size_ = lst.GetSize() << 2;
			reallocate();
		}
		vector_size_ = 0;
		for (auto &item : lst)
			arr[vector_size_++] = item;
	}

	template <typename T>
	void vector<T>::Assign(typename vector<T>::size_type count, const T &value) {
		size_type i;
		if (count > reserved_size_) {
			reserved_size_ = count << 2;
			reallocate();
		}
		for (i = 0; i < count; ++i)
			arr[i] = value;
		vector_size_ = count;
	}

	template <typename T>
	void vector<T>::Assign(typename vector<T>::iterator first, typename vector<T>::iterator last) {
		size_type i, count = last - first;
		if (count > reserved_size_) {
			reserved_size_ = count << 2;
			reallocate();
		}
		for (i = 0; i < count; ++i, ++first)
			arr[i] = *first;
		vector_size_ = count;
	}

	template <typename T>
	void vector<T>::Assign(std::initializer_list<T> lst) {
		size_type i, count = lst.GetSize();
		if (count > reserved_size_) {
			reserved_size_ = count << 2;
			reallocate();
		}
		i = 0;
		for (auto &item : lst)
			arr[i++] = item;
	}


	template <typename T>
	typename vector<T>::iterator vector<T>::begin() noexcept {
		return arr;
	}

	template <typename T>
	typename vector<T>::const_iterator vector<T>::cbegin() const noexcept {
		return arr;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::end() noexcept {
		return arr + vector_size_;
	}

	template <typename T>
	typename vector<T>::const_iterator vector<T>::cend() const noexcept {
		return arr + vector_size_;
	}

	template <typename T>
	typename vector<T>::reverse_iterator vector<T>::rbegin() noexcept {
		return reverse_iterator(arr + vector_size_);
	}

	template <typename T>
	typename vector<T>::const_reverse_iterator vector<T>::crbegin() const noexcept {
		return reverse_iterator(arr + vector_size_);
	}

	template <typename T>
	typename vector<T>::reverse_iterator vector<T>::rend() noexcept {
		return reverse_iterator(arr);
	}

	template <typename T>
	typename vector<T>::const_reverse_iterator vector<T>::crend() const noexcept {
		return reverse_iterator(arr);
	}


	template <typename T>
	inline void vector<T>::reallocate() {
		T *tarr = new T[reserved_size_];
		memcpy(tarr, arr, vector_size_ * sizeof(T));
		delete[] arr;
		arr = tarr;
	}


	template <typename T>
	bool vector<T>::IsEmpty() const noexcept {
		return vector_size_ == 0;
	}

	template <typename T>
	typename vector<T>::size_type vector<T>::GetSize() const noexcept {
		return vector_size_;
	}

	template <typename T>
	typename vector<T>::size_type vector<T>::GetMaxSize() const noexcept {
		return SDIZO_VECTOR_MAX_SIZE;
	}

	template <typename T>
	typename vector<T>::size_type vector<T>::GetCapacity() const noexcept {
		return reserved_size_;
	}

	template <typename T>
	void vector<T>::Resize(typename vector<T>::size_type sz) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
		}
		else {
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i].~T();
		}
		vector_size_ = sz;
	}

	template <typename T>
	void vector<T>::Resize(typename vector<T>::size_type sz, const T &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		else {
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i].~T();
		}
		vector_size_ = sz;
	}

	template <typename T>
	void vector<T>::Reserve(typename vector<T>::size_type _sz) {
		if (_sz > reserved_size_) {
			reserved_size_ = _sz;
			reallocate();
		}
	}

	template <typename T>
	void vector<T>::ShrinkToFit() {
		reserved_size_ = vector_size_;
		reallocate();
	}


	template <typename T>
	typename vector<T>::reference vector<T>::operator [](typename vector<T>::size_type idx) {
		return arr[idx];
	}

	template <typename T>
	typename vector<T>::const_reference vector<T>::operator [](typename vector<T>::size_type idx) const {
		return arr[idx];
	}

	template <typename T>
	typename vector<T>::reference vector<T>::Get(size_type pos) {
		if (pos < vector_size_)
			return arr[pos];
		else
			throw std::out_of_range("accessed position is out of range");
	}

	template <typename T>
	typename vector<T>::const_reference vector<T>::Get(size_type pos) const {
		if (pos < vector_size_)
			return arr[pos];
		else
			throw std::out_of_range("accessed position is out of range");
	}

	template <typename T>
	typename vector<T>::reference vector<T>::GetFront() {
		return arr[0];
	}

	template <typename T>
	typename vector<T>::const_reference vector<T>::GetFront() const {
		return arr[0];
	}

	template <typename T>
	typename vector<T>::reference vector<T>::GetBack() {
		return arr[vector_size_ - 1];
	}

	template <typename T>
	typename vector<T>::const_reference vector<T>::GetBack() const {
		return arr[vector_size_ - 1];
	}


	template <typename T>
	T * vector<T>::data() noexcept {
		return arr;
	}

	template <typename T>
	const T * vector<T>::data() const noexcept {
		return arr;
	}


	template <typename T>
	template <class ... Args>
	void vector<T>::emplace_back(Args && ... args) {
		if (vector_size_ == reserved_size_) {
			reserved_size_ <<= 2;
			reallocate();
		}
		arr[vector_size_] = std::move(T(std::forward<Args>(args) ...));
		++vector_size_;
	}

	template <typename T>
	void vector<T>::PushBack(const T &val) {
		if (vector_size_ == reserved_size_) {
			reserved_size_ <<= 2;
			reallocate();
		}
		arr[vector_size_] = val;
		++vector_size_;
	}

	template <typename T>
	void vector<T>::PushBack(T &&val) {
		if (vector_size_ == reserved_size_) {
			reserved_size_ <<= 2;
			reallocate();
		}
		arr[vector_size_] = std::move(val);
		++vector_size_;
	}

	template <typename T>
	void vector<T>::PopBack() {
		--vector_size_;
		arr[vector_size_].~T();
	}


	template <typename T>
	template <class ... Args>
	typename vector<T>::iterator vector<T>::emplace(typename vector<T>::const_iterator it, Args && ... args) {
		iterator iit = &arr[it - arr];
		if (vector_size_ == reserved_size_) {
			reserved_size_ <<= 2;
			reallocate();
		}
		memmove(iit + 1, iit, (vector_size_ - (it - arr)) * sizeof(T));
		(*iit) = std::move(T(std::forward<Args>(args) ...));
		++vector_size_;
		return iit;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::Insert(typename vector<T>::const_iterator it, const T &val) {
		iterator iit = &arr[it - arr];
		if (vector_size_ == reserved_size_) {
			reserved_size_ <<= 2;
			reallocate();
		}
		memmove(iit + 1, iit, (vector_size_ - (it - arr)) * sizeof(T));
		(*iit) = val;
		++vector_size_;
		return iit;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::Insert(typename vector<T>::const_iterator it, T &&val) {
		iterator iit = &arr[it - arr];
		if (vector_size_ == reserved_size_) {
			reserved_size_ <<= 2;
			reallocate();
		}
		memmove(iit + 1, iit, (vector_size_ - (it - arr)) * sizeof(T));
		(*iit) = std::move(val);
		++vector_size_;
		return iit;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::Insert(typename vector<T>::const_iterator it, typename vector<T>::size_type cnt, const T &val) {
		iterator f = &arr[it - arr];
		if (!cnt) return f;
		if (vector_size_ + cnt > reserved_size_) {
			reserved_size_ = (vector_size_ + cnt) << 2;
			reallocate();
		}
		memmove(f + cnt, f, (vector_size_ - (it - arr)) * sizeof(T));
		vector_size_ += cnt;
		for (iterator it = f; cnt--; ++it)
			(*it) = val;
		return f;
	}

	template <typename T>
	template <class InputIt>
	typename vector<T>::iterator vector<T>::Insert(typename vector<T>::const_iterator it, InputIt first, InputIt last) {
		iterator f = &arr[it - arr];
		size_type cnt = last - first;
		if (!cnt) return f;
		if (vector_size_ + cnt > reserved_size_) {
			reserved_size_ = (vector_size_ + cnt) << 2;
			reallocate();
		}
		memmove(f + cnt, f, (vector_size_ - (it - arr)) * sizeof(T));
		for (iterator it = f; first != last; ++it, ++first)
			(*it) = *first;
		vector_size_ += cnt;
		return f;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::Insert(typename vector<T>::const_iterator it, std::initializer_list<T> lst) {
		size_type cnt = lst.GetSize();
		iterator f = &arr[it - arr];
		if (!cnt) return f;
		if (vector_size_ + cnt > reserved_size_) {
			reserved_size_ = (vector_size_ + cnt) << 2;
			reallocate();
		}
		memmove(f + cnt, f, (vector_size_ - (it - arr)) * sizeof(T));
		iterator iit = f;
		for (auto &item : lst) {
			(*iit) = item;
			++iit;
		}
		vector_size_ += cnt;
		return f;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::Erase(typename vector<T>::const_iterator it) {
		iterator iit = &arr[it - arr];
		(*iit).~T();
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(T));
		--vector_size_;
		return iit;
	}

	template <typename T>
	typename vector<T>::iterator vector<T>::Erase(typename vector<T>::const_iterator first, typename vector<T>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		for (; first != last; ++first)
			(*first).~T();
		memmove(f, last, (vector_size_ - (last - arr)) * sizeof(T));
		vector_size_ -= last - first;
		return f;
	}

	template <typename T>
	void vector<T>::SwapVectors(vector<T> &rhs) {
		size_t tvec_sz = vector_size_,
			trsrv_sz = reserved_size_;
		T *tarr = arr;

		vector_size_ = rhs.vector_size_;
		reserved_size_ = rhs.reserved_size_;
		arr = rhs.arr;

		rhs.vector_size_ = tvec_sz;
		rhs.reserved_size_ = trsrv_sz;
		rhs.arr = tarr;
	}

	template <typename T>
	void vector<T>::Clear() noexcept {
		size_type i;
		for (i = 0; i < vector_size_; ++i)
			arr[i].~T();
		vector_size_ = 0;
	}


	template <typename T>
	bool vector<T>::operator == (const vector<T> &rhs) const {
		if (vector_size_ != rhs.vector_size_) return false;
		size_type i;
		for (i = 0; i < vector_size_; ++i)
			if (arr[i] != rhs.arr[i])
				return false;
		return true;
	}

	template <typename T>
	bool vector<T>::operator != (const vector<T> &rhs) const {
		if (vector_size_ != rhs.vector_size_) return true;
		size_type i;
		for (i = 0; i < vector_size_; ++i)
			if (arr[i] != rhs.arr[i])
				return true;
		return false;
	}

	template <typename T>
	bool vector<T>::operator < (const vector<T> &rhs) const {
		size_type i, j, ub = vector_size_ < rhs.vector_size_ ? vector_size_ : rhs.vector_size_;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] < rhs.arr[i];
		return vector_size_ < rhs.vector_size_;
	}

	template <typename T>
	bool vector<T>::operator <= (const vector<T> &rhs) const {
		size_type i, j, ub = vector_size_ < rhs.vector_size_ ? vector_size_ : rhs.vector_size_;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] < rhs.arr[i];
		return vector_size_ <= rhs.vector_size_;
	}

	template <typename T>
	bool vector<T>::operator > (const vector<T> &rhs) const {
		size_type i, j, ub = vector_size_ < rhs.vector_size_ ? vector_size_ : rhs.vector_size_;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] > rhs.arr[i];
		return vector_size_ > rhs.vector_size_;
	}

	template <typename T>
	bool vector<T>::operator >= (const vector<T> &rhs) const {
		size_type i, j, ub = vector_size_ < rhs.vector_size_ ? vector_size_ : rhs.vector_size_;
		for (i = 0; i < ub; ++i)
			if (arr[i] != rhs.arr[i])
				return arr[i] > rhs.arr[i];
		return vector_size_ >= rhs.vector_size_;
	}

	template<typename T>
	inline void vector<T>::Display() noexcept
	{
		std::cout << "Size: " << vector_size_ << " Capacity: " << GetCapacity();
		for (auto iter = begin(); iter != end(); iter++)
			std::cout << *iter << " ";
	}



	template <>
	void vector<bool>::Resize(typename vector<bool>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void vector<signed char>::Resize(typename vector<signed char>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void vector<unsigned char>::Resize(typename vector<unsigned char>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void vector<char>::Resize(typename vector<char>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void vector<short int>::Resize(typename vector<short int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void vector<unsigned short int>::Resize(typename vector<unsigned short int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void vector<int>::Resize(typename vector<int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void vector<unsigned int>::Resize(typename vector<unsigned int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void vector<long int>::Resize(typename vector<long int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void vector<unsigned long int>::Resize(typename vector<unsigned long int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void vector<long long int>::Resize(typename vector<long long int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void vector<unsigned long long int>::Resize(typename vector<unsigned long long int>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void vector<float>::Resize(typename vector<float>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void vector<double>::Resize(typename vector<double>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}

	template <>
	void vector<long double>::Resize(typename vector<long double>::size_type sz) {
		if (sz > reserved_size_) {
			reserved_size_ = sz;
			reallocate();
		}
		vector_size_ = sz;
	}


	template <>
	void vector<bool>::Resize(typename vector<bool>::size_type sz, const bool &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void vector<signed char>::Resize(typename vector<signed char>::size_type sz, const signed char &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void vector<unsigned char>::Resize(typename vector<unsigned char>::size_type sz, const unsigned char &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void vector<char>::Resize(typename vector<char>::size_type sz, const char &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void vector<short int>::Resize(typename vector<short int>::size_type sz, const short int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void vector<unsigned short int>::Resize(typename vector<unsigned short int>::size_type sz, const unsigned short int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void vector<int>::Resize(typename vector<int>::size_type sz, const int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void vector<unsigned int>::Resize(typename vector<unsigned int>::size_type sz, const unsigned int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void vector<long int>::Resize(typename vector<long int>::size_type sz, const long int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void vector<unsigned long int>::Resize(typename vector<unsigned long int>::size_type sz, const unsigned long int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void vector<long long int>::Resize(typename vector<long long int>::size_type sz, const long long int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void vector<unsigned long long int>::Resize(typename vector<unsigned long long int>::size_type sz, const unsigned long long int &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void vector<float>::Resize(typename vector<float>::size_type sz, const float &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void vector<double>::Resize(typename vector<double>::size_type sz, const double &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		vector_size_ = sz;
	}

	template <>
	void vector<long double>::Resize(typename vector<long double>::size_type sz, const long double &c) {
		if (sz > vector_size_) {
			if (sz > reserved_size_) {
				reserved_size_ = sz;
				reallocate();
			}
			size_type i;
			for (i = vector_size_; i < sz; ++i)
				arr[i] = c;
		}
		vector_size_ = sz;
	}


	template <>
	void vector<bool>::PopBack() {
		--vector_size_;
	}

	template <>
	void vector<signed char>::PopBack() {
		--vector_size_;
	}

	template <>
	void vector<unsigned char>::PopBack() {
		--vector_size_;
	}

	template <>
	void vector<char>::PopBack() {
		--vector_size_;
	}

	template <>
	void vector<short int>::PopBack() {
		--vector_size_;
	}

	template <>
	void vector<unsigned short int>::PopBack() {
		--vector_size_;
	}

	template <>
	void vector<int>::PopBack() {
		--vector_size_;
	}

	template <>
	void vector<unsigned int>::PopBack() {
		--vector_size_;
	}

	template <>
	void vector<long int>::PopBack() {
		--vector_size_;
	}

	template <>
	void vector<unsigned long int>::PopBack() {
		--vector_size_;
	}

	template <>
	void vector<long long int>::PopBack() {
		--vector_size_;
	}

	template <>
	void vector<unsigned long long int>::PopBack() {
		--vector_size_;
	}

	template <>
	void vector<float>::PopBack() {
		--vector_size_;
	}

	template <>
	void vector<double>::PopBack() {
		--vector_size_;
	}

	template <>
	void vector<long double>::PopBack() {
		--vector_size_;
	}


	template <>
	typename vector<bool>::iterator vector<bool>::Erase(typename vector<bool>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(bool));
		--vector_size_;
		return iit;
	}

	template <>
	typename vector<signed char>::iterator vector<signed char>::Erase(typename vector<signed char>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(signed char));
		--vector_size_;
		return iit;
	}

	template <>
	typename vector<unsigned char>::iterator vector<unsigned char>::Erase(typename vector<unsigned char>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(unsigned char));
		--vector_size_;
		return iit;
	}

	template <>
	typename vector<char>::iterator vector<char>::Erase(typename vector<char>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(char));
		--vector_size_;
		return iit;
	}

	template <>
	typename vector<short int>::iterator vector<short int>::Erase(typename vector<short int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(short int));
		--vector_size_;
		return iit;
	}

	template <>
	typename vector<unsigned short int>::iterator vector<unsigned short int>::Erase(typename vector<unsigned short int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(unsigned short int));
		--vector_size_;
		return iit;
	}

	template <>
	typename vector<int>::iterator vector<int>::Erase(typename vector<int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(int));
		--vector_size_;
		return iit;
	}

	template <>
	typename vector<unsigned int>::iterator vector<unsigned int>::Erase(typename vector<unsigned int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(unsigned int));
		--vector_size_;
		return iit;
	}

	template <>
	typename vector<long int>::iterator vector<long int>::Erase(typename vector<long int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(long int));
		--vector_size_;
		return iit;
	}

	template <>
	typename vector<unsigned long int>::iterator vector<unsigned long int>::Erase(typename vector<unsigned long int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(unsigned long int));
		--vector_size_;
		return iit;
	}

	template <>
	typename vector<long long int>::iterator vector<long long int>::Erase(typename vector<long long int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(long long int));
		--vector_size_;
		return iit;
	}

	template <>
	typename vector<unsigned long long int>::iterator vector<unsigned long long int>::Erase(typename vector<unsigned long long int>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(unsigned long long int));
		--vector_size_;
		return iit;
	}

	template <>
	typename vector<float>::iterator vector<float>::Erase(typename vector<float>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(float));
		--vector_size_;
		return iit;
	}

	template <>
	typename vector<double>::iterator vector<double>::Erase(typename vector<double>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(double));
		--vector_size_;
		return iit;
	}

	template <>
	typename vector<long double>::iterator vector<long double>::Erase(typename vector<long double>::const_iterator it) {
		iterator iit = &arr[it - arr];
		memmove(iit, iit + 1, (vector_size_ - (it - arr) - 1) * sizeof(long double));
		--vector_size_;
		return iit;
	}


	template <>
	typename vector<bool>::iterator vector<bool>::Erase(typename vector<bool>::const_iterator first, typename vector<bool>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr)) * sizeof(bool));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename vector<signed char>::iterator vector<signed char>::Erase(typename vector<signed char>::const_iterator first, typename vector<signed char>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr)) * sizeof(signed char));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename vector<unsigned char>::iterator vector<unsigned char>::Erase(typename vector<unsigned char>::const_iterator first, typename vector<unsigned char>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr)) * sizeof(unsigned char));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename vector<char>::iterator vector<char>::Erase(typename vector<char>::const_iterator first, typename vector<char>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr)) * sizeof(char));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename vector<short int>::iterator vector<short int>::Erase(typename vector<short int>::const_iterator first, typename vector<short int>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr)) * sizeof(short int));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename vector<unsigned short int>::iterator vector<unsigned short int>::Erase(typename vector<unsigned short int>::const_iterator first, typename vector<unsigned short int>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr)) * sizeof(unsigned short int));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename vector<int>::iterator vector<int>::Erase(typename vector<int>::const_iterator first, typename vector<int>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr)) * sizeof(int));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename vector<unsigned int>::iterator vector<unsigned int>::Erase(typename vector<unsigned int>::const_iterator first, typename vector<unsigned int>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr)) * sizeof(unsigned int));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename vector<long long int>::iterator vector<long long int>::Erase(typename vector<long long int>::const_iterator first, typename vector<long long int>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr)) * sizeof(long long int));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename vector<unsigned long long int>::iterator vector<unsigned long long int>::Erase(typename vector<unsigned long long int>::const_iterator first, typename vector<unsigned long long int>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr)) * sizeof(unsigned long long int));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename vector<float>::iterator vector<float>::Erase(typename vector<float>::const_iterator first, typename vector<float>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr)) * sizeof(float));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename vector<double>::iterator vector<double>::Erase(typename vector<double>::const_iterator first, typename vector<double>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr)) * sizeof(double));
		vector_size_ -= last - first;
		return f;
	}

	template <>
	typename vector<long double>::iterator vector<long double>::Erase(typename vector<long double>::const_iterator first, typename vector<long double>::const_iterator last) {
		iterator f = &arr[first - arr];
		if (first == last) return f;
		memmove(f, last, (vector_size_ - (last - arr)) * sizeof(long double));
		vector_size_ -= last - first;
		return f;
	}


	template <>
	void vector<bool>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void vector<signed char>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void vector<unsigned char>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void vector<char>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void vector<short int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void vector<unsigned short int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void vector<int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void vector<unsigned int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void vector<long int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void vector<unsigned long int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void vector<long long int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void vector<unsigned long long int>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void vector<float>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void vector<double>::Clear() noexcept {
		vector_size_ = 0;
	}

	template <>
	void vector<long double>::Clear() noexcept {
		vector_size_ = 0;
	}


}


