#include "stdafx.h"
#include <exception>

template<typename Object>
class List
{
private:
	struct Node
	{
		Object data;
		Node* prev;
		Node* next;

		Node(const Object& d = Object{},
			Node* p = nullptr, Node* n = nullptr)
			: data(d)
			, prev(p)
			, next(n)
		{}

		Node(Object&& d, Node* p = nullptr, Node* n = nullptr)
			: data(std::move(d))
			, prev(p)
			, next(n)
		{}
	};

public:
	class const_iterator
	{
	public:
		const_iterator()
			: current(nullptr)
		{}

		const Object& operator* () const
		{
			return retrieve();
		}

		const_iterator& operator++ ()
		{
			current = current->next;
			return *this;
		}

		const_iterator& operator++ (int)
		{
			const_iterator old = *this;
			current = current->next;
			return old;
		}

		bool operator== (const_iterator& rhs) const
		{
			return current == rhs.current;
		}


		bool operator!= (const_iterator& rhs) const
		{
			return !(*this == rhs);
		}

	protected:
		const List<Object>* theList;
		Node * current;

		Object& retrieve() const
		{
			return current->data;
		}

		const_iterator(const List<Object>& lst, Node* p)
			: theList(&lst)
			, current(p)
		{}

		void assert_is_valid() const
		{
			if (theList == nullptr || current == nullptr || current == theList->head)
				throw std::out_of_range{ "Incorrect List Exception" };
		}



		friend class List<Object>;
	};

	class iterator : public const_iterator
	{
	public:
		iterator()
		{  }

		Object& operator* ()
		{
			return const_iterator::retrieve();
		}
		const Object & operator* () const
		{
			return const_iterator::operator*();
		}

		iterator operator++ (int)
		{
			iterator old = *this;
			this->current = this->current->next;
			return old;
		}

		bool operator!= (iterator& rhs) const
		{
			return !(*this == rhs);
		}

	protected:
		iterator(List& lst, Node* p)
			: const_iterator(lst, p)
		{}

		friend class List<Object>;
	};

	List()
	{
		init();
	}

	~List()
	{
		clear();
		delete head;
		delete tail;
	}

	List(const List & rhs)
	{
		init();
		for (auto & x : rhs)
			push_back(x);
	}

	List& operator= (const List& rhs)
	{
		List copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	List(List&& rhs)
		: theSize(rhs.theSize)
		, head(rhs.head)
		, tail(rhs.tail)
	{
		rhs.theSize = 0;
		rhs.head = nullptr;
		rhs.tails = nullptr;
	}

	List& operator= (List&& rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(head, rhs.head);
		std::swap(tail, rhs.tail);

		return *this;
	}

	iterator swap_adj(iterator it1, iterator it2)
	{
		Node* p1 = it1.current;
		Node* p2 = it2.current;
		auto temp = p2;

		p1->prev->next = p1->next;
		p1->next->prev = p1->prev;
		p1->next = temp->next;
		p1->prev = temp;
		p1->prev->next = p1;
		p1->next->prev = p1;

		return it1;
	}

	iterator begin()
	{
		return { *this, head->next };
	}

	const_iterator begin() const
	{
		const_iterator itr{ *this, head };
		return ++itr;
	}

	iterator end()
	{
		return iterator(*this, tail);
	}

	const_iterator end() const
	{
		return iterator(*this, tail);
	}

	int size() const
	{
		return theSize;
	}

	bool empty() const
	{
		return size() == 0;
	}

	void clear()
	{
		while (!empty())
		{
			pop_front();
		}
	}

	Object& front()
	{
		return *begin();
	}

	const Object& front() const
	{
		return *begin();
	}

	Object& back()
	{
		return *--end();
	}

	const Object& back() const
	{
		return *--end();
	}

	void push_front(const Object& x)
	{
		insert(begin(), x);
	}

	void push_front(Object&& x)
	{
		insert(begin(), std::move(x));
	}

	void push_back(const Object& x)
	{
		insert(end(), x);
	}

	void push_back(Object&& x)
	{
		insert(end(), std::move(x));
	}

	void pop_front()
	{
		erase(begin());
	}

	void pop_back()
	{
		erase(--end());
	}

	iterator insert(iterator itr, const Object& x)
	{
		checkIterator(itr);
		Node* p = itr.current;
		theSize++;
		Node* newNode = new Node(x, p->prev, p);
		p->prev->next = newNode;
		p->prev = newNode;
		return iterator{ *this, newNode };
	}

	iterator insert(iterator itr, Object&& x)
	{
		checkIterator(itr);
		Node* p = itr.current;
		theSize++;
		Node* newNode = new Node(x, p->prev, p);
		p->prev->next = newNode;
		p->prev = newNode;
		return iterator{ *this, newNode };
	}

	iterator erase(iterator itr)
	{
		Node* p = itr.current;
		iterator retVal{ *this, p->next };
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		theSize--;

		return retVal;
	}

	iterator erase(iterator from, iterator to)
	{
		for (iterator itr = from; itr != to; )
			itr = erase(itr);

		return to;
	}

private:
	int theSize;
	Node* head;
	Node* tail;

	void init()
	{
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->prev = head;
	}

	void checkIterator(const_iterator itr)
	{
		itr.assert_is_valid();
		if (itr.theList != this)
			throw std::out_of_range{ "The iterator doesn't point to current list" };
	}



};




