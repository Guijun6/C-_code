#pragma once 
#include<iostream>
#include<assert.h>
using namespace std;

template < class T >
struct ListNode
{
	T _data;
	ListNode<T>* _next;
	ListNode<T>* _prev;
	ListNode(const T& x)
		:_data(x)
		, _next(NULL)
		, _prev(NULL)
	{}
};

template < class T >
class List
{
	typedef ListNode<T> Node;
public:
	List()
		:_head(new Node(T()))
	{
		_head->_prev = _head;
		_head->_next = _head;
	}

	List(const List<T>& l)
		:_head(new Node(T()))
	{
		_head->_next = _head;
		_head->_prev = _head;
		Node* cur = _head;
		Node* tmp = l._head->_next;
		while (tmp != l._head)
		{
			this->PushBack(tmp->_data);
			tmp = tmp->_next;
		}
	}
	//List<T>& operator=(const List<T>& l)
	//{
	//	this->Clear();
	//	Node* cur = _head;
	//	Node* tmp = l._head->_next;
	//	while (tmp != l._head)
	//	{
	//		this->PushBack(tmp->_data);
	//		tmp = tmp->_next;
	//	}
	//	return *this;
	//}
	List<T>& operator=(List<T> l)
	{
		swap(this->_head, l._head);
		return *this;
	}
	void PushBack(const T x)
	{
		Node* tmp = new Node(x);
		Node* cur = _head->_prev;
		cur->_next = tmp;
		tmp->_next = _head;
		_head->_prev = tmp;
		tmp->_prev = cur;
	}
	void PushFront(const T x)
	{
		Node* tmp = new Node(x);
		Node* cur = _head->_next;
		_head->_next = tmp;
		tmp->_next = cur;
		cur->_prev = tmp;
		tmp->_prev = _head;
	}
	void PopBack()
	{
		if (_head->_next != _head)
		{
			Node* tail = _head->_prev->_prev;
			delete _head->_prev;
			tail->_next = _head;
			_head->_prev = tail;
		}
	}
	void PopFront()
	{
		if (_head->_next != _head)
		{
			Node* head = _head->_next->_next;
			delete _head->_next;
			_head->_next = head;
			head->_prev = _head;
		}
	}
	Node* Find(const T x)
	{
		Node* tmp = _head->_next;
		while (tmp != _head)
		{
			if (tmp->_data == x)
			{
				return tmp;
			}
			tmp = tmp->_next;
		}
		return NULL;
	}
	void Insert(const Node* pos, const T x)
	{
		assert(pos);
		Node* tmp = new Node(x);
		Node* prev = pos->_prev;

		prev->_next = tmp;
		tmp->_prev = prev;
		tmp->_next = pos;
		pos->_prev = tmp;
	}
	void Erase(Node* pos)
	{
		assert(pos && pos != _head);

		Node* prev = pos->_prev;
		Node* next = pos->_next;

		prev->_next = next;
		next->_prev = prev;

		delete pos;
	}
	void Clear()
	{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			Node* tmp = cur->_next;
			delete cur;
			cur = tmp;
		}
		_head->_next = _head;
		_head->_prev = _head;
	}
	~List()
	{
		Clear();
		delete _head;
		_head = NULL;
	}
	void Print()
	{
		Node* cur = _head->_next;
		while(cur != _head)
		{
			cout << cur->_data<< "->" ;
			cur = cur->_next;
		}
		cout << "NULL" << endl;
	}
private:
	Node* _head;
};