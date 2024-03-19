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
//函数模板
template <class T>
void Swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}
void test0();


/*****************************************************************************/
//Template<typename T> 类模版声明
//T 表示任意类型

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

//类模板特化
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
//类模板偏特化

 //类型形参 在参数列表中，跟在class或typename后面的参数类型的名称。(T1，T2就是)
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

//非类型形参 用一个常量去作为类/函数模板的一个参数。
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
	Person<string, int> p1("孙悟空",999);
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

//1.指定传入的类型
void PrintPerson1(Person3<string, int> & p1)
{
	p1.showResult();
}

//2.参数模板化（类模板+函数模板）
template<class T1,class T2>
void PrintPerson2(Person3<T1,T2> &p2)
{
	p2.showResult();
	cout << "T1的数据类型是：" << typeid(T1).name() << endl;
	cout << "T2的数据类型是：" << typeid(T2).name() << endl;
}

//3.整个类模板化（类模板+函数模板）
template<class T>
void PrintPerson3(T &p)
{
	p.showResult();
	cout << "T的数据类型: " << typeid(T).name() << endl;
}

void test03();

/*****************************************************************************/
void printIntArray(MyArray<int>& arr);
void test04();


//测试自定义数据类型
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
