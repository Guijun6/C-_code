#include<iostream>
#include<assert.h>
using namespace std;
typedef int DataType;
struct ListNode
{
	ListNode* next;
	ListNode* prev;
	DataType data;
	ListNode(DataType x)
		:next(NULL)
		, prev(NULL)
		, data(x)
	{}
};
class List
{
	typedef ListNode Node;
public:
	List(DataType x)
	{
		cout << "List()" << endl;
		_head = new Node(x);
		_tail = _head;
	}
	List(const List& l)
	{
		assert( l._head );
		Node *tmp = l._head;
		while (tmp)
		{
			PushBack(tmp->data);
			tmp = tmp->next;
		}
	}
	List& operator=(const List& l)
	{
		//先清理掉 *this
		if (_head)
		{
			Node* tmp = _head;
			Node* cur = _head;
			while (tmp)
			{
				cur = tmp->next;
				delete tmp;
				tmp = cur;
			}
			_head = _tail = NULL;
		}
		//再进行拷贝
		assert(l._head);
		if (_head != l._head)
		{
			Node *tmp = l._head;
			while (tmp)
			{
				PushBack(tmp->data);
				tmp = tmp->next;
			}
		}
		return *this;
	}
	~List()
	{
		cout << "~List" << endl;
		if (_head)
		{
			Node* tmp = _head;
			Node* cur = _head;
			while (tmp)
			{
				cur = tmp->next;
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
			_head = _tail = tmp;
			_head->next = _head->prev = NULL;
		}
		else
		{
			Node* tmp = new Node(x);
			_tail->next = tmp;
			tmp->prev = _tail;
			_tail = tmp;
			_tail->next = NULL;
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
			_tail = _tail->prev;
			delete _tail->next;
			_tail->next = NULL;
		}
	}
	void PushFront(DataType x)
	{
		if (_head == NULL)
		{
			_head = _tail = new Node(x);
		}
		else
		{
			Node* tmp = new Node(x);
			tmp->next = _head;
			_head->prev = tmp;
			_head = tmp;
			_head->prev = NULL;
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
			_head = _head->next;
			delete _head->prev;
			_head->prev = NULL;
		}
	}
		// 在pos的前面插入一个 
	void Insert(Node* pos, DataType x)
	{
		if (pos == _head)
		{
			PushFront(x);
		}
		else
		{
			Node* tmp = new Node(x);
			Node* cur = pos->prev;
			cur->next = tmp;
			tmp->prev = cur;
			tmp->next = pos;
			pos->prev = tmp;
		}

	}
	void Erase(Node* pos);
	Node* Find(DataType x)
	{
		Node* cur = _head;
		while ((cur->data != x)&&(cur))
		{
			cur = cur->next;
		}
		if (cur == NULL)
		{
			return NULL;
		}
		return cur;
	}
	void Reverse()
	{
		if ((_head == NULL) || (_head == _tail))
		{
			return;
		}
		else
		{
			Node* begin = _head;
			Node* end = _tail;
			while ((begin->next != end->prev)&&(begin->next != end))
			{
				DataType tmp = begin->data;
				begin->data = end->data;
				end->data = tmp;
				begin = begin->next;
				end = end->prev;
			}

		}
	}

	void Print()
	{
		if (_head)
		{
			Node* tmp = _head;
			while (tmp)
			{
				cout << tmp->data;
				tmp = tmp->next;
			}
			cout << endl;
			cout << "_head:"<<_head->data << endl;
			cout << "_tail:" << _tail->data << endl;
			cout << _tail->prev->data << endl;
		}
	}
private:
	Node* _head;
	Node* _tail;
};