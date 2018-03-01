#pragma once

template<class T>
class Vector
{
public:
	typedef T* VIterator;
	typedef const T* ConstVIterator;

	Vector()
		:_start(0)
		, _finish(0)
		, _end(0)
	{}
	~Vector()
	{
		delete[] _start;
		_start = NULL;
		_finish = NULL;
		_end = NULL;
	}
	size_t Size()
	{
		return _finish - _start;
	}
	size_t Capacity()
	{
		return _end - _start;
	}
	void Expand(size_t newcapacity)
	{
		size_t size = Size();
		size_t capacity = Capacity();
		if (newcapacity > capacity)
		{
			T* _tmp = new T[newcapacity];
			if (_start)
			{
				T* start = _start;
				T* tmp = _tmp;
				for (; start <= _start + size; start++)
				{
					//memcpy(tmp, _start, sizeof(T)*size);
					*tmp = *start;
					tmp++;
				}
			}
			delete[] _start;
			_start = _tmp;
			_finish = _start + size;
			_end = _start + newcapacity;
		}
	}
	void CheckCapacity()
	{
		if (Size() >= Capacity())
		{
			size_t newcapacity = Size() > 0 ? Capacity() * 2 : 3;
			Expand(newcapacity);
		}
	}
	void PushBack(const T x)
	{
		CheckCapacity();
		*_finish = x;
		_finish++;
	}

	VIterator Begin()
	{
		return _start;
	}
	ConstVIterator Begin() const
	{
		return _start;
	}
	VIterator End()
	{
		return _finish;
	}
	ConstVIterator End() const
	{
		return _finish;
	}

	void Resize(size_t n, const T& val = T())
	{
		if (n >= Capacity())
		{
			Expand(n);
			size_t i = Size();
			for (; i < Capacity(); i++)
			{
				*(_start + i) = val;
			}
			_finish = _start + i;
			_end = _start + i;
		}
		else if ((n < Capacity()) && (n>Size()))
		{
			size_t i = Size();
			for (; i < Capacity(); i++)
			{
				*(_start + i) = val;
			}
			_finish = _start + i;
			_end = _start + i;
		}
	}
	void Reserver(size_t n)
	{
		Expand(n);
	}
	void Insert(VIterator pos, const T& x)
	{
		assert((pos >= _start) && (pos < _finish));
		CheckCapacity();
		VIterator cur = _finish;
		//挪数据
		while (cur != pos)
		{
			*cur = *(cur - 1);
			cur--;
		}
		//插入
		*pos = x;
		_finish++;
	}
	VIterator Erase(VIterator pos)
	{
		assert((pos >= _start) && (pos < _finish));
		VIterator cur = pos;
		//挪数据
		while ((cur+1) != _finish)
		{
			*cur = *(cur + 1);
			cur++;
		}
		_finish--;
	}

private:
	VIterator _start;
	VIterator _finish;
	VIterator _end;
};