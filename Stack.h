#pragma once
#include<assert.h>

template<class T>
class Stack
{
public:
	Stack()
		:_head(NULL)
		, _size(0)
		, _capacity(0)
	{}

	~Stack()
	{
		delete[] _head;
		_head = NULL;
	}
	void CheckCapacity()
	{
		//À©ÈÝ
		if (_size >= _capacity)
		{
			_capacity = _capacity > 0 ? (_capacity * 2) : 3;
			T* tmp = new T[sizeof(T)*_capacity];
			//¿½±´Êý¾Ý
			if (_head)
			{
				for (size_t i = 0; i < _size; i++)
				{
					*(tmp + i) = *(_head + i);
				}
			}
			delete[] _head;
			_head = tmp;
		}
	}
	void Push(const T& x)
	{
		CheckCapacity();
		*(_head + _size) = x;
		_size++;
	}
	void Pop()
	{
		if (_head)
		{
			_size--;
		}
	}
	T& Top()
	{
		if (_head)
			return *(_head + _size - 1);
	}
	size_t Size()
	{
		return _size;
	}
	bool Empty()
	{
		return _size > 0;
	}
	void Swap(Stack<T>& s)
	{
		assert((s._head) && (_head));
		T* stmp = new T[sizeof(T)* s._capacity];
		for (size_t i = 0; i < s._size; i++)
		{
			*(stmp + i) = *(s._head + i);
		}

		T* tmp = new T[sizeof(T)* _capacity];
		for (size_t i = 0; i < _size; i++)
		{
			*(tmp + i) = *(_head + i);
		}
		delete[] s._head;
		delete[] _head;
		size_t ssize = s._size;
		size_t size = _size;
		size_t scapacity = s._capacity;
		size_t capacity = _capacity;
		s._head = tmp;
		s._capacity = capacity;
		s._size = size;
		_head = stmp;
		_size = ssize;
		_capacity = scapacity;
	}
private:
	T* _head;
	size_t _size;
	size_t _capacity;
};