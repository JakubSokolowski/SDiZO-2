#pragma once
#include <iostream>

namespace dts
{
	template <typename T>
	struct ListNode
	{
		ListNode(const T &val)
			: data_(val)
			, next_(0)
			, prev_(0)
		{}

		T data_;
		ListNode<T> *next_;
		ListNode<T> *prev_;
	};

	template <typename T>
	class List
	{
	public:

		class iterator
		{
		public:
			iterator(ListNode<T> *p = 0) : pos_(p) { }

			T &operator*()
			{
				return pos_->data_;
			}

			T *operator->()
			{
				return &(pos_->data_);
			}

			bool operator!=(const iterator &rhs)
			{
				return this->pos_ != rhs.pos_;
			}

			iterator operator++(int)
			{
				pos_ = pos_->next_; return *this;
			}

			iterator operator--(int)
			{
				pos_ = pos_->prev_; return *this;
			}

		private:
			ListNode<T> *pos_;
		};
		iterator begin()
		{
			return iterator(head_);
		}
		iterator end()
		{
			return iterator(0);
		}

		class reverse_iterator
		{
		public:
			reverse_iterator(ListNode<T> *p = 0) : pos_(p) { }

			T &operator*()
			{
				return pos_->data_;
			}

			T *operator->()
			{
				return &(pos_->data_);
			}

			bool operator!=(const reverse_iterator &rhs)
			{
				return this->pos_ != rhs.pos_;
			}

			reverse_iterator operator++(int)
			{
				pos_ = pos_->prev_; return *this;
			}

			reverse_iterator operator--(int)
			{
				pos_ = pos_->next_; return *this;
			}

		private:
			ListNode<T> *pos_;
		};
		reverse_iterator rbegin()
		{
			return reverse_iterator(tail_);
		}
		reverse_iterator rend()
		{
			return reverse_iterator(0);
		}
		

		List()
			: head_(0)
			, tail_(0)
			, size_(0)
		{}
		~List();

		int GetSize() { return size_; }
		
		ListNode<T>* Insert(const T& e, ListNode<T> *pos);
		void PushBack(const T &e);
		void PushFront(const T& e);
		void Remove(ListNode<T> *position);
		void PopBack();
		void PopFront();
		T &front();
		T &back();

		

	

	private:
		ListNode<T> *head_;
		ListNode<T> *tail_;

		int size_;

	};



	template<typename T>
	inline List<T>::~List()
	{
		ListNode<T> *current(head_);

		while (current)
		{
			ListNode<T> *next(current->next_);
			current->data_.~T();
			delete current;
			current = next;
		}
	}

	template<typename T>
	inline ListNode<T>* List<T>::Insert(const T & e, ListNode<T>* pos)
	{
		ListNode<T> *n = new ListNode<T>(e);

		size_++;
		// no operation below this should throw
		// as state of the list has changed and memory allocated

		n->next_ = pos;

		if (pos)
		{
			n->prev_ = pos->prev_;
			pos->prev_ = n;
		}
		else
		{
			// pos is null that is at the very end of the list
			n->prev_ = tail_;
			tail_ = n;
		}

		if (n->prev_)
		{
			n->prev_->next_ = n;
		}
		else
		{
			// at the very begining of the list
			head_ = n;
		}

		return n;
	}

	template<typename T>
	inline void List<T>::PushBack(const T & e)
	{
		Insert(e, 0);
	}

	template<typename T>
	inline void List<T>::PushFront(const T & e)
	{
		Insert(e, head_);
	}

	template<typename T>
	inline void List<T>::Remove(ListNode<T>* pos)
	{
		if (pos)
		{
			if (pos->prev_)
				pos->prev_->next = pos->next_;

			if (pos->next_)
				pos->next_->prev_ = pos->prev_;

			if (pos == head_)
				head_ = pos->next_;

			if (pos == tail_)
				tail_ = pos->prev_;

			delete pos;

			size_--;
		}
	}

	template<typename T>
	inline void List<T>::PopBack()
	{
		Remove(tail_);
	}

	template<typename T>
	inline void List<T>::PopFront()
	{
		Remove(head_);
	}

	template<typename T>
	inline T & List<T>::front()
	{
		return head_->data_;
	}

	template<typename T>
	inline T & List<T>::back()
	{
		returnt tail_->data_;
	}

	

	

	


}
