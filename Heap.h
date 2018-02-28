#pragma once

template<class T>
class Heap
{
public:
	Heap()
	{}
	//构造函数创建堆
	Heap(const T* a, size_t size)
	{
		//向_a中插入数据
		_a.reserve(sizeof(T)*size);//先开足够空间，可提高效率
		for (size_t i = 0; i < size; i++)
		{
			_a.push_back(a[i]);
		}
		_capacity = _a.size()*sizeof(T);

		//建大堆
		size_t i = 0;
		//while (i <= (_a.size() - 1) / 2)
		while (i <= 4)
		{
			AdjustDown(_a, _a.size(), i);
			i++;
		}
		for (i = 0; i <= 9; i++)
		{
			AdjustDown(_a, _a.size(), 0);

		}
	}
	
	//向下调整算法
	void AdjustDown(vector<T>& heap, T size, T root)
	{
		T parent = root;
		T child = parent * 2 + 1;
		while (child < size)
		{
			//保证child始终指向大的孩子
			if (((child+1) < size) && (heap[child] < heap[child + 1]))
			{
				++child;
			}
			if (heap[parent] < heap[child])
			{
				swap(heap[parent], heap[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
	void Display()
	{
		for (size_t i = 0; i < _a.size(); i++)
		{
			cout << _a[i] << " ";
		}
		cout << endl;
		cout << _a.size() << endl;
		cout << _capacity << endl;
	}
	~Heap()
	{}
private:
	vector<T> _a;
	size_t _capacity;
};