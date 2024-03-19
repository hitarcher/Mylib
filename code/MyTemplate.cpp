#include "stdafx.h"
#include "MyTemplate.h"

void PrintA(A<int> & a)
{
	cout << a.getT() << endl;
}

void testt()
{
	A<int> a(666);
	cout << a.getT() << endl;
	PrintA(a);
}
/*****************************************************************************/
void test0()
{
	int a = 1;
	int b = 2;
	double c = 1.1;
	double d = 1.2;
	//��ʽʵ����   
	Swap(a, b);
	Swap(c, d);

	//��ʽʵ����
	Swap<int>(a, b);
	Swap<double>(c, d);

}


/*****************************************************************************/

template<typename T>
Myarray<T>::Myarray()
	:len(0)
{
	data = new T[20];
}

template<typename T>
T Myarray<T>::indexof(int index)
{
	return data[index];
}

template<typename T>
void Myarray<T>::addValue(T value)
{
	data[len + 1] = value;
}



/*****************************************************************************/
void test03()
{
	Person3<string, int>p1("�����", 100);
	PrintPerson1(p1);//�����100
	Person3<string, int>p2("��˽�", 90);
	PrintPerson2(p2);//��˽�90��T1Ϊstring��T2,Ϊint
	Person3<string, int>p3("��ɮ", 30);
	PrintPerson3(p3);//��ɮ30 T������Ϊ class Person<string,int>
}

/*****************************************************************************/

void printIntArray(MyArray<int>& arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << arr[i] << endl;
	}
}
void test04()
{
	//����������������
	MyArray<int>arr1(5);
	for (int i = 0; i < 5; i++)
	{
		arr1.Push_Back(i);
	}
	cout << "arr1�Ĵ�ӡ���Ϊ��" << endl;
	printIntArray(arr1);
	cout << "arr1������Ϊ��" << arr1.getCapacity() << endl;
	cout << "arr1�Ĵ�СΪ��" << arr1.getSize() << endl;
	MyArray<int> arr2(arr1);
	cout << "arr2�Ĵ�ӡ���Ϊ��" << endl;
	printIntArray(arr1);
	arr2.Pop_Back();
	cout << "arr2βɾ������Ϊ��" << endl;
	cout << "arr2������Ϊ��" << arr2.getCapacity() << endl;
	cout << "arr2�Ĵ�СΪ��" << arr2.getSize() << endl;

	MyArray<int>arr3(100);
	arr3 = arr1;

}


void printPersonArray(MyArray<Person4>& arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << "������ "<< arr[i].m_Name.c_str() << " ���䣺 " << arr[i].m_Age << endl;
	}
}
void test05()
{
	MyArray<Person4> arr(10);
	Person4 p1("�����", 999);
	Person4 p2("����", 30);
	Person4 p3("槼�", 20);
	Person4 p4("����", 25);
	Person4 p5("������", 27);

	//�����ݲ��뵽������
	arr.Push_Back(p1);
	arr.Push_Back(p2);
	arr.Push_Back(p3);
	arr.Push_Back(p4);
	arr.Push_Back(p5);

	//��ӡ����
	printPersonArray(arr);

	//�������
	cout << "arr����Ϊ�� " << arr.getCapacity() << endl;

	//�����С
	cout << "arr��СΪ�� " << arr.getSize() << endl;
}
