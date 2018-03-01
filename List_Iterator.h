#pragma once

template<class T>
struct ListNode
{
	ListNode<T>* _next;
	ListNode<T>* _prev;
	T _data;

	ListNode(const T& x)
		:_data(x)
		, _next(NULL)
		, _prev(NULL)
	{}
};

template<class T, class Ref, class Ptr>
struct ListIterator;

template<class T>
class List
{
	typedef ListNode<T> Node;
public:
	typedef ListIterator<T, T&, T*> LIterator;
	typedef ListIterator<T, const T&, const T*> ConstLIterator;
	List()
		:_head(new Node(T()))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}
	void clear()
	{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}
		_head->_next = _head;
		_head->_prev = _head;
	}
	~List()
	{
		clear();
		delete _head;
		_head = NULL;
	}

	void PushBack(const T& x)
	{
		Node* tmp = new Node(x);
		Node* tail = _head->_prev;

		_head->_prev = tmp;
		tmp->_prev = tail;
		tail->_next = tmp;
		tmp->_next = _head;
	}
	void Insert(LIterator pos, const T& x)
	{
		Node* tmp = new Node(x);
		Node* prev = (pos._node)->_prev;
		Node* cur = pos._node;
		prev->_next = tmp;
		tmp->_next = cur;
		cur->_prev = tmp;
		tmp->_prev = prev;
	}
	LIterator Erease(LIterator& pos)
	{
		//assert((pos._node) != _head);
		assert(pos != End());
		Node* prev = (pos._node)->_prev;
		Node* next = (pos._node)->_next;
		prev->_next = next;
		next->_prev = prev;
		delete pos._node;
		return LIterator(next);
	}
	LIterator Begin()
	{
		return LIterator(_head->_next);
	}
	ConstLIterator Begin() const
	{
		return ConstLIterator(_head->_next);
	}

	LIterator End()
	{
		return LIterator(_head);
	}
	ConstLIterator End() const
	{
		return ConstLIterator(_head);
	}

private:
	Node* _head;
};

template<class T, class Ref, class Ptr>
struct ListIterator
{
	typedef ListNode<T> Node;
	typedef ListIterator<T, Ref, Ptr> Self;

	ListIterator(Node* node)
		:_node(node)
	{}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &(_node->_data);
	}

	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}

	bool operator==(const Self& s)
	{
		return _node == s._node;
	}

	Self& operator++()
	{
		_node = _node->_next;
		return *this;
	}
	Self& operator++(int)
	{
		Self tmp(_node);
		_node = _node->_next;
		return tmp;
	}

	Self& operator--()
	{
		return _node = _node->_prev;
	}
	Self& operator--(int)
	{
		Self tmp(_node);
		_node = _node->_prev;
		return tmp;
	}

	Node* _node;
};
