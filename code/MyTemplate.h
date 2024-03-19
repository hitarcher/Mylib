#ifndef MYTEMPLATE_H_
#define MYTEMPLATE_H_
#include <iostream>
using namespace std;
#include"MyArray.hpp"

/*****************************************************************************/	
template <typename T>
class A
{
public:
	A(T t1)
	{
		t = t1;
	}
	T& getT()
	{
		return t;
	}

private:
	T t;
};
void PrintA(A<int> & a);
void testt();

/*****************************************************************************/
//����ģ��
template <class T>
void Swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}
void test0();


/*****************************************************************************/
//Template<typename T> ��ģ������
//T ��ʾ��������

 template<typename T>
 class Myarray
 {
 private:
 	T data[20];
 	int len;
 public:
	Myarray();
 	T indexof(int index);
 	void addValue(T value);
 };

//��ģ���ػ�
template<>
class Myarray<float>
{
public:
	Myarray();

};
Myarray<float>::Myarray()
{
	cout << "MyArray<float>::Myarray()" << endl;
}

/*****************************************************************************/
//��ģ��ƫ�ػ�

 //�����β� �ڲ����б��У�����class��typename����Ĳ������͵����ơ�(T1��T2����)
template<typename T1, typename T2>
class Pair
{
public:
	Pair();
};

template<typename T1, typename T2>
Pair<T1, T2>::Pair()
{
	cout << "Pair<T1,T2>::Pair()" << endl;
}

//�������β� ��һ������ȥ��Ϊ��/����ģ���һ��������
template<typename T2>
class Pair<char, T2>
{
public:
	Pair();
};

template<typename T2>
Pair<char, T2>::Pair()
{
	cout << "Pair<char,T2>::Pair()" << endl;
}

/*****************************************************************************/

template<class NameType,class AgeType>
//template<typename NameType, typename AgeType>
class Person
{
public:
	Person(NameType name, AgeType age)
	{
		m_name = name;
		m_age - age;
	}
	void showResult()
	{
		cout << m_name.c_str() << m_age << endl;
	}
private:
	NameType m_name;
	AgeType m_age;
};

void test02()
{
	Person<string, int> p1("�����",999);
	p1.showResult();
}

/*****************************************************************************/
template<class T1,class T2>
class Person3
{
public:
	Person3(T1 name, T2 age)
	{
		m_name =name;
		m_age =age;
	}
	void showResult()
	{
		cout << m_name.c_str() << m_age << endl;
	}

	T1 m_name;
	T2 m_age;
};

//1.ָ�����������
void PrintPerson1(Person3<string, int> & p1)
{
	p1.showResult();
}

//2.����ģ�廯����ģ��+����ģ�壩
template<class T1,class T2>
void PrintPerson2(Person3<T1,T2> &p2)
{
	p2.showResult();
	cout << "T1�����������ǣ�" << typeid(T1).name() << endl;
	cout << "T2�����������ǣ�" << typeid(T2).name() << endl;
}

//3.������ģ�廯����ģ��+����ģ�壩
template<class T>
void PrintPerson3(T &p)
{
	p.showResult();
	cout << "T����������: " << typeid(T).name() << endl;
}

void test03();

/*****************************************************************************/
void printIntArray(MyArray<int>& arr);
void test04();


//�����Զ�����������
class Person4
{
public:
	Person4() {};
	Person4(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	string m_Name;
	int m_Age;
};
void printPersonArray(MyArray<Person4>& arr);
void test05();




































#endif
