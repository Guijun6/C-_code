#pragma once

template<class T>
class Heap
{
public:
	Heap()
	{}
	//���캯��������
	Heap(const T* a, size_t size)
	{
		//��_a�в�������
		_a.reserve(sizeof(T)*size);//�ȿ��㹻�ռ䣬�����Ч��
		for (size_t i = 0; i < size; i++)
		{
			_a.push_back(a[i]);
		}
		_capacity = _a.size()*sizeof(T);

		//�����
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
	
	//���µ����㷨
	void AdjustDown(vector<T>& heap, T size, T root)
	{
		T parent = root;
		T child = parent * 2 + 1;
		while (child < size)
		{
			//��֤childʼ��ָ���ĺ���
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