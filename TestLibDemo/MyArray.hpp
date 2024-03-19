#pragma once
#include <iostream>
using namespace std;

//1��ͨ����ģ��ʵ�ִ洢�����������ͺ��Զ����������͵�����
//2���ڹ��캯�����ڶ��������ڴ棬�������ݴ洢��ȥ
//3����������Ϊ�вι��캯���Ĳ������д���
//4���ṩ�������캯��ʱ���Ƚ�ԭ�������е��������Ȼ���ٽ���ֵ�Ŀ���
//4��ʹ��operator����=ʱ����Ҫ���������ͬʱ����ֵ������void����Ϊ��Ҫ��������
//5��ʹ��β�巨��βɾ��ʱҪ���ж����������Ƿ���/�Ƿ��
//6������[]ʵ��ͨ���±���������е�Ԫ�أ�ע�ⷵ��ֵҪΪ���ã���Ϊ����ֵ�������ܻ���Ϊ��ֵ
//7����ȡ��ǰ������Ԫ�ظ�������������ֱ�ӷ��س�Ա����m_Size��m_Capacity����

template<class T>
class MyArray
{
public:
	//���캯��
	MyArray(int capacity)
	{
		cout << "MyArray���вι������" << endl;
		this->m_Capacity = capacity;
		this->m_Size = 0;
		this->pAddress = new T[this->m_Capacity];
	}
	//�������캯��(��ֹǳ����)
	MyArray(const MyArray& arr)
	{
		cout << "MyArray���вι������" << endl;
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[arr.m_Capacity];//���
											   //��arr�е����ݶ���������
		for (int i = 0; i < this->m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
	}

	//operator=��ֹǳ��������
	MyArray& operator=(const MyArray& arr)
	{
		cout << "MyArray��operator=����" << endl;
		//���ж�ԭ�������Ƿ������ݣ���������ͷ�
		if (this->pAddress != NULL)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->m_Capacity = 0;
			this->m_Size = 0;
		}
		//���
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[arr.m_Capacity];
		for (int i = 0; i < this->m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}

	//β�巨
	void Push_Back(const T & value)
	{
		//�ж������Ƿ���ڴ�С
		if (this->m_Capacity == this->m_Size)
		{
			return;
		}
		this->pAddress[this->m_Size] = value; //������ĩβ��������
		this->m_Size++; //���������С
	}

	//βɾ��
	void Pop_Back()
	{
		//���û����ʲ������һ��Ԫ�ؼ�Ϊβɾ���߼�ɾ��
		if (this->m_Size == 0)
		{
			return;
		}
		this->m_Size--;
	}

	//ͨ���±귽ʽ���������е�Ԫ�أ��������ֵ����Ϊ��ֵ���ڣ���Ҫ����һ������
	T& operator[](int index)
	{
		return this->pAddress[index];
	}

	//������������
	int getCapacity()
	{
		return this->m_Capacity;
	}

	//���������С
	int getSize()
	{
		return this->m_Size;
	}

	//��������
	~MyArray()
	{
		if (this->pAddress != NULL)
		{
			cout << "MyArray��������������" << endl;
			delete[] this->pAddress;
			this->pAddress = NULL;
		}
	}

private:
	T * pAddress;   //ָ��ָ��������ٵ���ʵ����
	int m_Capacity; //��������
	int m_Size;     //�����С
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
//	//�������캯��
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