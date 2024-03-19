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
	//隐式实例化   
	Swap(a, b);
	Swap(c, d);

	//显式实例化
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
	Person3<string, int>p1("孙悟空", 100);
	PrintPerson1(p1);//孙悟空100
	Person3<string, int>p2("猪八戒", 90);
	PrintPerson2(p2);//猪八戒90，T1为string，T2,为int
	Person3<string, int>p3("唐僧", 30);
	PrintPerson3(p3);//唐僧30 T的类型为 class Person<string,int>
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
	//测试内置数据类型
	MyArray<int>arr1(5);
	for (int i = 0; i < 5; i++)
	{
		arr1.Push_Back(i);
	}
	cout << "arr1的打印输出为：" << endl;
	printIntArray(arr1);
	cout << "arr1的容量为：" << arr1.getCapacity() << endl;
	cout << "arr1的大小为：" << arr1.getSize() << endl;
	MyArray<int> arr2(arr1);
	cout << "arr2的打印输出为：" << endl;
	printIntArray(arr1);
	arr2.Pop_Back();
	cout << "arr2尾删后的输出为：" << endl;
	cout << "arr2的容量为：" << arr2.getCapacity() << endl;
	cout << "arr2的大小为：" << arr2.getSize() << endl;

	MyArray<int>arr3(100);
	arr3 = arr1;

}


void printPersonArray(MyArray<Person4>& arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << "姓名： "<< arr[i].m_Name.c_str() << " 年龄： " << arr[i].m_Age << endl;
	}
}
void test05()
{
	MyArray<Person4> arr(10);
	Person4 p1("孙悟空", 999);
	Person4 p2("韩信", 30);
	Person4 p3("妲己", 20);
	Person4 p4("赵云", 25);
	Person4 p5("安其拉", 27);

	//将数据插入到数组中
	arr.Push_Back(p1);
	arr.Push_Back(p2);
	arr.Push_Back(p3);
	arr.Push_Back(p4);
	arr.Push_Back(p5);

	//打印数组
	printPersonArray(arr);

	//输出容量
	cout << "arr容量为： " << arr.getCapacity() << endl;

	//输出大小
	cout << "arr大小为： " << arr.getSize() << endl;
}
