#include<iostream>
using namespace std;

#define NEW(ptr,type,n)												\
	do{																\
		ptr = (type*)operator new(sizeof(type)*n);					\
		new(ptr)type;												\
				}while(0)
#define DELETE(ptr,type)											\
	do{																\
		ptr-> ~type();												\
		operator delete(ptr);										\
				}while(0)
#define NEW_ARRY(ptr,type,n)										\
	do{																\
		ptr=(type*)operator new char[sizeof(type)+sizeof(ptr)];		\
		*ptr = n;													\
		for(size_t i=1;i<=n;i++)									\
			new(ptr+i)type;											\
				}while(0)
#define DELETE_ARRY(ptr,type)										\
	do{																\
		size_t n=*((char*ptr)-sizeof(ptr));							\
		for(size_t i=0;i<n;i++)										\
		(ptr+i)->~type;												\
		operator delete((char*)ptr-sizeof(ptr));					\
				}while(0)
#define DELETE_ARRY_2(ptr,type,n)									\
	do{																\
		for(size_t i=0;i<n;i++)										\
		(ptr+i)->~type;												\
		operator delete((char*)ptr-sizeof(ptr));					\
	}while(0)
class String
{
public:
	String(const char* str="")
	{
		_str=new char[strlen(str) + 1];
		cout << "String()" << endl;
		strcpy(_str, str);
		_size=strlen(str);
		_capacity = strlen(_str);
	}
////��ͳ�Ŀ�������s2(s1)
//	String(const String& str)
//		:_str(new char[strlen(str._str)+1])//	��
//	{
//		strcpy(_str, str._str);
//	}
//�ִ��Ŀ�������s2(s1)
	String(const String& str)
		:_str(NULL)
	{
		String tmp(str._str);//����һ����ʱ�����ڵ��ù��캯��ʱ���ѿ��˿ռ�
		swap(_str, tmp._str);
	}
////��ͳ�ĸ�ֵ���������s2=s1
//	String& operator=(const String& str)
//	{
//		if (this != &str)
//		{
//			_str=new char[strlen(str._str) + 1];
//			strcpy(_str, str._str);
//		}
//		return *this;
//	}
//�ִ��ĸ�ֵ���������
	String& operator=(const String& str)
	{
		if (this != &str)
		{
			String tmp(str._str);
			swap(_str, tmp._str);
		}
		return *this;
	}

	void Getchar()
	{
		cout <<_str<< endl;
		cout << "_size=" << _size << endl;
		cout << "_capacity=" << _capacity << endl;

	}


	//��ɾ���

	//����
	void Expand(size_t n)
	{
		char* tmp = new char[n];
		strcpy(tmp,_str);
		delete[] _str;
		_str = tmp;
		_capacity = n;
	}
	void PushBack(const char ch)
	{
		//������� 
		if (_size >= _capacity)
		{
			Expand(_capacity * 2);
		}
		//��������
		_str[_size++] = ch;
		_str[_size] = '\0';
	}
	void PushBack(const char* str)
	{
		assert(str);
		size_t len = strlen(str);
		//�������
		if ((_size + len) > _capacity)
		{
			Expand(_size + len + 1);
		}
		//��������
		for (int i = 0; i < (int)len; i++)
		{
			_str[_size] = str[i];
			_size++;
		}
		_str[_size] = '\0';
	}
	void PopBack()
	{
		_str[_size - 1] = _str[_size];
		_size--;
	}
	void PopBack(size_t pop)
	{
		_str[_size-pop] = '\0';
		_size = _size - pop;
	}
	void Insert(size_t pos, const char ch)
	{
		//������� 
		if (_size >= _capacity)
		{
			Expand(_capacity * 2);
		}
		int end = _size;
		if (pos >= _size)
		{
			PushBack(ch);
		}
		else if (pos < _size)
		{
			while (end >= (int)pos)
			{
				_str[end + 1] = _str[end];
				end--;
			}
			_str[pos] = ch;
			_size++;
		}
	}
	void Insert(size_t pos, const char* str)
	{
		int len = strlen(str);
		if ((_size + len) > _capacity)
		{
			Expand(_size + len);
		}
		//Ų����
		if (pos >= _size)
		{
			PushBack(str);
		}
		else if (pos < _size)
		{
			int end = _size;
			while (end >= (int)pos)
			{
				_str[end + len] = _str[end];
				end--;
			}
			//��������
			while (len--)
			{
				_str[pos++] = *str++;
			}
			_size += len;
		}
	}
	void Erase(size_t pos, size_t count)
	{
		char* str1 = _str + pos;
		char* str2 = _str + pos + count;
		while (*str2)
		{
			*str1 = *str2;
			str1++;
			str2++;
		}
		*str1 = *str2;
		_size = _size - count;
	}
	size_t Find(char ch) const
	{
		char* str = _str;
		for (int i = 0; i < _size;i++)
		{
			if (*str == ch)
				return i;
			str++;
		}
		return false;
	}
	int Find(const char* str) const
	{
		const char* str1 = _str;
		const char* str2 = str;
		while (*str1)
		{
			int tmp = 0;
			const char* str4 = str;
			while (*str1 == *str4)
			{
				tmp = 1;
				str1++;
				str4++;
			}
			if (*str4 == '\0')
			{
				return 1;
			}
			if (tmp==0)
				str1++;
		}
		return -1;
	}
	char& operator[](size_t pos)
	{
		return _str[pos];
	}
	bool operator<(const String& s) const
	{
		char* str1 = _str;
		const char* str2 = s._str;
		while (*str1 < *str2)
		{
			if (*str1)
			{
				return true;
			}
			str1++;
			str2++;
		}
		return false;
	}
	bool operator<=(const String& s) const
	{
		char* str1 = _str;
		const char* str2 = s._str;
		while (*str1 <= *str2)
		{
			if (*str1)
			{
				return true;
			}
			str1++;
			str2++;
		}
		return false;
	}
	bool operator>(const String& s) const
	{
		return !(*this <= s);
	}
	bool operator>=(const String& s) const
	{
		return !(*this < s);
	}
	bool operator==(const String& s) const
	{
		char* str1 = _str;
		const char* str2 = s._str;
		while (*str1 == *str2)
		{
			if (*str1 == '\0')
			{
				return true;
			}
			str1++;
			str2++;
		}
		return false;
	}
	bool operator!=(const String& s)const
	{
		return !(*this == s);
	}

	~String()
	{
		cout << "~String()" << endl;
		if (_str)
		{
			delete[] _str;
			_size = 0;
			_capacity = 0;
			_str = NULL;
		}
	}
private:
	char* _str;
	size_t _size;
	size_t _capacity;
};