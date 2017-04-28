#pragma once
#include <iterator>
#include <cstddef>
#include <utility>
#include <stdexcept>



#define SDIZO_VECTOR_MAX_SIZE 1000000000

namespace sdizo
{
	template <typename T>
	class Vector 
	{
		//Types:
		typedef T value_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;

		//Iterators

		typedef T* iterator;
		typedef const T* const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ptrdiff_t difference_type;
		typedef unsigned int size_type;

		//Constructors,Destructors,Memory Handling, Copying

		Vector() noexcept;
		explicit Vector(size_type n);
		Vector(size_type n, const T &val);		//change to const reference?
		Vector(typename vector<T>::iterator first, typename vector<T>::iterator last);
		Vector(std::initializer_list<T>);
		Vector(const vector<T> &);
		Vector(Vector<T> &);
		Vector(Vector<T> &&) noexcept;
		~Vector();

		Vector<T> & operator = (const vector<T> &);
		Vector<T> & operator = (std::initializer_list<T>);
		void Assign(size_type, const T &value);
		void Assign(typename vector<T>::iterator, typename vector<T>::iterator);
		void Assign(std::initializer_list<T>);

		// iterators : 

		iterator begin() noexcept;
		iterator end() noexcept;

		const_iterator const_begin() const noexcept;
		const_iterator const_end() const noexcept;

		reverse_iterator reverse_begin() noexcept;
		reverse_iterator reverse_end() noexcept;

		const_reverse_iterator const_reverse_begin() const noexcept;
		const_reverse_iterator const_reverse_end() const noexcept;

		//Capacity, Reallocation

		bool IsEmpty() const noexcept;
		size_type GetSize() const noexcept;
		size_type GetMaxSize() const noexcept;
		size_type GetCapacity() const noexcept;

		void Resize(size_type);
		void Resize(size_type, const T&);
		void Reserve(size_type);
		void ShrinkToFit();
		
		//Element access

		reference operator [](size_type);
		const_reference operator [](size_type) const;

		reference Get(size_type);
		const_reference Get(size_type) const;

		reference GetFirst();
		reference GetBack();

		reference GetFirst() const;		
		const_reference GetBack() const;

		//Data Access

		T* data() noexcept;
		const T * data() const noexcept;

		//Modifiers

		template <class ... Args> void EmplaceBack(Args && ... args);
		void PushBack(const T &);
		void PushBack(T&&);
		void PopBack();

		template <class ..Args> iterator emplace(const_iterator, Args && ...);

		iterator Insert(const_iterator, const T &);
		iterator Insert(const_iterator, T&&);
		iterator Insert(const_iterator, size_type, const T&);
		template <class InputIt> iterator Insert(const_iterator, InputIt, InputIt);
		iterator Insert(const_iterator, std::initializer_list<T>);
		iterator Erease(const_iterator);
		iterator Erease(const_iterator, const_iterator);
		void Swap(vector<T> &);
		void Clear()noexcept;

		//Comparision operators

		bool operator == (const vector<T> &) const;
		bool operator != (const vector<T> &) const;
		bool operator < (const vector<T> &) const;
		bool operator <= (const vector<T> &) const;
		bool operator > (const vector<T> &) const;
		bool operator >=(const vector<T>) const;

	private :

		size_type reserved_size_ = 4;
		size_type vector_size_ = 0;
		T * arr;

		inline void Reallocate();
	};

}
