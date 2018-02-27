#include<iostream>
#include<assert.h>
using namespace std;

#pragma once;
typedef int DataType;
class SeqList
{
public:
	SeqList()
	{
		//cout << "SeqList" << endl;
		_arry = new DataType[sizeof(DataType*)];
		_capacity = sizeof(DataType*);
		_size = 0;
	}
	SeqList(const SeqList& s)
	{
		_arry = new DataType[s._capacity];
		memcpy(_arry, s._arry, sizeof(DataType)*s._size);
		_size = s._size;
		_capacity = s._capacity;

	}
	SeqList& operator=(SeqList s)
	{
		delete[] _arry;
		_arry = new DataType[s._capacity];
		for (DataType i = 0; i < s._size; i++)
		{
			_arry[i] = s._arry[i];
		}
		_size = s._size;
		_capacity = s._capacity;
		return *this;
	}

	~SeqList()
	{
		//cout << "~SeqList" << endl;
		if (_arry)
		{
			delete[] _arry;
			_arry = NULL;
			_size = 0;
			_capacity = 0;
		}
	}

	void Swap(SeqList& s)
	{
		SeqList tmp(*this);
		*this = s;
		s = tmp;
	}

	void PushBack(DataType x)
	{
		if (_size >= _capacity)
		{
			CheckCapcacity();
		}
		_arry[_size++] = x;
	}
	void PopBack()
	{
		if (_size>=1)
		_size--;

	}
	void PushFront(DataType x)
	{
		if (_size == 0)
		{
			PushBack(x);
		}
		else
		{
			if (_size >= _capacity)
			{
				CheckCapcacity();
			}
			int tmp = (int)_size;
			while (tmp > 0)
			{
				_arry[tmp] = _arry[tmp - 1];
				tmp--;
			}
			_arry[0] = x;
			_size++;
		}
	}
	void PopFront()
	{
		if (_size > 1)
		{
			size_t tmp = 0;
			while (tmp < _size-1)
			{
				_arry[tmp] = _arry[tmp + 1];
				tmp++;
			}
			_size--;
		}
		else if (_size = 1)
		{
			PopBack();
		}
	}
	void Insert(size_t pos, DataType x)
	{
		if (_size == 0)
		{
			PushBack(x);
		}
		else if (_size > 0)
		{
			assert(pos < _size);
			if (_size >= _capacity)
			{
				CheckCapcacity();
			}
			size_t tmp = _size;
			while (tmp > pos)
			{
				_arry[tmp] = _arry[tmp - 1];
				tmp--;
			}
			_arry[pos] = x;
			_size++;
		}
	}
	void Erase(size_t pos)
	{
		if (_size > 1)
		{
			assert(pos < _size);
			size_t tmp = pos;
			while (tmp < _size - 1)
			{
				_arry[tmp] = _arry[tmp + 1];
				tmp++;
			}
			_size--;
		}
		else if (_size == 1)
		{
			PopBack();
		}
	}
	DataType& operator[](size_t pos)
	{
		assert(pos < _size);
		return _arry[pos];
	}
	void CheckCapcacity()
	{
		DataType* tmp = new DataType[_capacity * 2];
		memcpy(tmp, _arry, _size*sizeof(DataType));
		delete[] _arry;
		_arry = tmp;
		_capacity = _capacity * 2;
	}
	void Print()
	{
		for ( size_t i = 0; i < _size; i++)
		{
			cout << _arry[i];
		}
		cout << endl;
		cout << "_size=" << _size << endl;
		cout << "_capacity=" << _capacity << endl;
	}
private:
	DataType* _arry;
	size_t _size;
	size_t _capacity;
};