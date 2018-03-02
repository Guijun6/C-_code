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
////传统的拷贝构造s2(s1)
//	String(const String& str)
//		:_str(new char[strlen(str._str)+1])//	？
//	{
//		strcpy(_str, str._str);
//	}
//现代的拷贝构造s2(s1)
	String(const String& str)
		:_str(NULL)
	{
		String tmp(str._str);//创建一个临时对象在调用构造函数时就已开了空间
		swap(_str, tmp._str);
	}
////传统的赋值运算符重载s2=s1
//	String& operator=(const String& str)
//	{
//		if (this != &str)
//		{
//			_str=new char[strlen(str._str) + 1];
//			strcpy(_str, str._str);
//		}
//		return *this;
//	}
//现代的赋值运算符重载
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


	//增删查改

	//扩容
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
		//检查容量 
		if (_size >= _capacity)
		{
			Expand(_capacity * 2);
		}
		//插入数据
		_str[_size++] = ch;
		_str[_size] = '\0';
	}
	void PushBack(const char* str)
	{
		assert(str);
		size_t len = strlen(str);
		//检查容量
		if ((_size + len) > _capacity)
		{
			Expand(_size + len + 1);
		}
		//插入数据
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
		//检查容量 
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
		//挪数据
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
			//插入数据
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