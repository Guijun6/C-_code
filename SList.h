#include<iostream>
#include<assert.h>
using namespace std;

typedef int DataType;

struct SListNode
{
	SListNode* _next;
	DataType _data;

	SListNode(DataType x)
		:_data(x)
		, _next(NULL)
	{}
};

class SList
{
	typedef SListNode Node;
public:
	SList(DataType x)
		:_head(new Node(x))
		, _tail(_head)
	{
		cout << "SList()"<<endl;
	}
	SList(const SList& s)
		:_head(NULL)
		, _tail(NULL)
	{
		Node* cur = s._head;
		Node* tmp = NULL;
		while (cur)
		{
			PushBack(cur->_data);
			cur = cur->_next;
		}
	}
	SList& operator=(const SList& s)
	{
		if ((this->_head) != (s._head))
		{
			Node* tmp = _head;
			while (tmp)
			{
				Node* cur = tmp->_next;
				delete tmp;
				tmp = cur;
			}
			_head = NULL;
			Node* cur = s._head;
			while (cur)
			{
				PushBack(cur->_data);
				cur = cur->_next;
			}
		}
		return *this;
	}
	~SList()
	{
		cout << "~SList" << endl;
		if (_head)
		{
			Node* tmp = _head;
			while (tmp)
			{
				Node* cur = tmp->_next;
				delete tmp;
				tmp = cur;
			}
			_head = _tail = NULL;
		}
	}
	void PushBack(DataType x)
	{
		if (_head == NULL)
		{
			Node* tmp = new Node(x);
			tmp->_next = NULL;
			_head = _tail = tmp;
		}
		else
		{
			_tail->_next = new Node(x);
			_tail = _tail->_next;
		}
	}
	void PopBack()
	{
		if (_head == NULL)
		{
			return;
		}
		else if (_head == _tail)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			Node* prev = _head;
			while (prev->_next != _tail)
			{
				prev = prev->_next;
			}
			delete _tail;
			_tail = prev;
			_tail->_next = NULL;
		}
	}
	void PushFront(DataType x)
	{
		if (_head == NULL)
		{
			_head = new Node(x);
		}
		else
		{
			Node* tmp = new Node(x);
			tmp->_next = _head;
			_head = tmp;
		}
	}
	void PopFront()
	{
		if (_head == NULL)
		{
			return;
		}
		else if (_head == _tail)
		{
			delete _head;
			_head = _tail = NULL;
		}
		else
		{
			Node* tmp = _head->_next;
			delete _head;
			_head = tmp;
		}
	}
		// 插入一个节点在pos的前面 
	Node* FindNode(size_t n)
	{
		assert(n > 0);
		size_t i = 0;
		Node* cur = _head;
		while (i < n-1)
		{
			cur = cur->_next;
			i++;
		}
		return cur;
	}
	void Insert(Node* pos, DataType x)
	{
		if (pos == _head)
		{
			PushFront(x);
		}
		else
		{
			Node* cur = _head;
			while (cur->_next != pos)
			{
				cur = cur->_next;
			}
			Node* tmp = new Node(x);
			tmp->_next = pos;
			cur->_next = tmp;
		}
		
	}
	void Erase(Node* pos)
	{
		if (pos == _head)
		{
			PopFront();
		}
		else if (pos == _tail)
		{
			PopBack();
		}
		else
		{
			Node* tmp = _head;
			while (tmp->_next != pos)
			{
				tmp = tmp->_next;
			}
			tmp->_next = pos->_next;
			delete pos;
		}
	}
	void Print()
	{
		Node* tmp = _head;
		while (tmp)
		{
			cout << tmp->_data;
			tmp = tmp->_next;
		}
		cout << endl;
		if (_head)
		{
			cout << "_head: " << _head->_data << endl;
			cout << "_tail: " << _tail->_data << endl;
		}
	}

private:
	Node* _head;
	Node* _tail;
};
