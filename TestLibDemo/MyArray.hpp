#pragma once
#include <iostream>
using namespace std;

//1、通过类模板实现存储内置数据类型和自定义数据类型的数据
//2、在构造函数中在堆区开辟内存，并将数据存储上去
//3、将容量作为有参构造函数的参数进行传入
//4、提供拷贝构造函数时，先将原来对象中的数据清除然后再进行值的拷贝
//4、使用operator重载=时，需要进行深拷贝，同时返回值不能是void，因为需要进行连等
//5、使用尾插法和尾删法时要先判断数组数据是否满/是否空
//6、重载[]实现通过下标访问数组中的元素，注意返回值要为引用，因为返回值后续可能会作为左值
//7、获取当前数组中元素个数和容量可以直接返回成员变量m_Size和m_Capacity即可

template<class T>
class MyArray
{
public:
	//构造函数
	MyArray(int capacity)
	{
		cout << "MyArray的有参构造调用" << endl;
		this->m_Capacity = capacity;
		this->m_Size = 0;
		this->pAddress = new T[this->m_Capacity];
	}
	//拷贝构造函数(防止浅拷贝)
	MyArray(const MyArray& arr)
	{
		cout << "MyArray的有参构造调用" << endl;
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[arr.m_Capacity];//深拷贝
											   //将arr中的数据都拷贝过来
		for (int i = 0; i < this->m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
	}

	//operator=防止浅拷贝问题
	MyArray& operator=(const MyArray& arr)
	{
		cout << "MyArray的operator=调用" << endl;
		//先判断原来堆区是否有数据，如果有先释放
		if (this->pAddress != NULL)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->m_Capacity = 0;
			this->m_Size = 0;
		}
		//深拷贝
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[arr.m_Capacity];
		for (int i = 0; i < this->m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}

	//尾插法
	void Push_Back(const T & value)
	{
		//判断容量是否等于大小
		if (this->m_Capacity == this->m_Size)
		{
			return;
		}
		this->pAddress[this->m_Size] = value; //在数组末尾插入数据
		this->m_Size++; //更新数组大小
	}

	//尾删法
	void Pop_Back()
	{
		//让用户访问不到最后一个元素即为尾删，逻辑删除
		if (this->m_Size == 0)
		{
			return;
		}
		this->m_Size--;
	}

	//通过下标方式访问数组中的元素，如果返回值想作为左值存在，需要返回一个引用
	T& operator[](int index)
	{
		return this->pAddress[index];
	}

	//返回数组容量
	int getCapacity()
	{
		return this->m_Capacity;
	}

	//返回数组大小
	int getSize()
	{
		return this->m_Size;
	}

	//析构函数
	~MyArray()
	{
		if (this->pAddress != NULL)
		{
			cout << "MyArray的析构函数调用" << endl;
			delete[] this->pAddress;
			this->pAddress = NULL;
		}
	}

private:
	T * pAddress;   //指针指向堆区开辟的真实数组
	int m_Capacity; //数组容量
	int m_Size;     //数组大小
};

//template<class T>
//class Myarray
//{
//private: 
//	int m_capacity;
//	int m_size;
//	T* pAddress;
//public:
//	Myarray(int capacity)
//	{
//		m_capacity = capacity;
//		m_size = 0;
//		pAddress = new T[capacity];
//	}
//	//拷贝构造函数
//	Myarray(const Myarray &rhs)
//	{
//		m_size = rhs.m_size;
//		m_capacity = rhs.m_capacity;
//		pAddress = new T[m_capacity];
//		for (int i =0;i<m_size;i++)
//		{
//			pAddress[i] = rhs.pAddress[i];
//		}
//	}
//	Myarray & operator =(const Myarray &rsh)
//	{
//		m_size = rhs.m_size;
//		m_capacity = rhs.m_capacity;
//		pAddress = new T[m_capacity];
//		for (int i = 0; i < m_size; i++)
//		{
//			pAddress[i] = rhs.pAddress[i];
//		}
//		return *this;
//	}
//	void push_back(const &T value)
//	{
//		if (value.m_size == m_capacity)
//		{
//			return;
//		}
//		pAddress[m_size++] = value;
//	}
//	void pop_back()
//	{
//		if (m_size == 0)
//		{
//			return
//		}
//		m_size--;
//	}
//
//	T & operator[](int index)
//	{
//		return pAddress[index];
//	}
//};