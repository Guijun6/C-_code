#pragma once

template<class T>
struct QueueNode
{
	T _data;
	QueueNode* _next;
	QueueNode* _prev;
	QueueNode(const T& x)
		:_data(x)
		, _next(NULL)
		, _prev(NULL)
	{}
};

template<class T>
class Queue
{
public:
	typedef QueueNode<T> Node;
	//Queue()
	//	:_head(new Node(T()))
	//{
	//	_head->_next = _head;
	//	_head->_prev = _head;
	//}
	Queue()
		:_head(NULL)
	{}
	~Queue()
	{
		Node* cur = _head->_next;
		while (cur != _head)
		{
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}
		delete _head;
		_head = NULL;
	}
	void Push(const T& x)
	{
		if (_head ==NULL)
		{
			_head = new Node(x);
			_head->_next = _head;
			_head->_prev = _head;
		}
		else
		{
			Node* tmp = new Node(x);
			Node* cur = _head->_prev;
			cur->_next = tmp;
			tmp->_next = _head;
			_head->_prev = tmp;
			tmp->_prev = cur;
		}
	}
	size_t Size()
	{
		if (_head == NULL)
			return 0;
		else if (_head->_next == _head)
			return 1;
		else
		{
			size_t i = 1;
			Node* tmp = _head->_next;
			while (tmp != _head)
			{
				i++;
				tmp = tmp->_next;
			}
			return i;
		}
	}
	void Pop()
	{
		size_t i = Size();
		if (i ==1)
		{
			delete _head;
			_head = NULL;
		}
		else if (i == 2)
		{
			Node* cur = _head->_next;
			delete _head;
			_head = cur;
			_head->_next = _head;
			_head->_prev = _head;
		}
		else if (i > 2)
		{
			Node* cur = _head->_next;
			Node* tail = _head->_prev;
			delete _head;
			_head = cur;
			_head->_prev = tail;
			tail->_next = _head;
		}
	}
	void Print()
	{
		if (Size() >= 1)
		{
			Node* tmp = _head;
			do
			{
				cout << tmp->_data << " ";
				tmp = tmp->_next;
			} while (tmp != _head);
			cout << endl;
		}
	}
	T& Front()
	{
		return _head->_data;
	}
	void Back();
	bool Empty();
private:
	Node* _head;
};