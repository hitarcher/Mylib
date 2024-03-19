#include "stdafx.h"
#include<iostream>
using namespace std;

void testPoint()
{
	int *p = NULL;
	// *p = 3;
	const int MAX = 3;
	int  var[MAX] = { 10, 100, 200 };
	int  *ptr;
	// 指针中的数组地址
	ptr = var;
	ptr++;
	ptr--;

	ptr = var;
	int i = 0;
	while (ptr <= &var[MAX - 1])
	{
		cout << "Address of var[" << i << "] = ";
		cout << ptr << endl;

		cout << "Value of var[" << i << "] = ";
		cout << *ptr << endl;

		// 指向上一个位置
		ptr++;
		i++;
	}
}

void testPoint2()
{
	int var[5] = { 0,1,2,3,4 };
	int *ptr = NULL;
	ptr = var;
	ptr++;//正确
	*ptr = 1;
	*var = 5;
	//var++;

	const int MAX = 3;
	int  var2[MAX] = { 10, 100, 200 };
	int *ptr2[MAX];//把 ptr 声明为一个数组，由 MAX 个整数指针组成,ptr 中的每个元素，都是一个指向 int 值的指针。
	ptr2[0] = &var2[0];
	cout << *ptr2[0] << endl;

	const char *names[MAX] = { "Zara Ali", "Hina Ali", "Nuha Ali" };//是指针数组,本质是存储指针的数组,

	// 	 int *ptr[3];
	// 	 //由于 C++ 运算符的优先级中，* 小于 []，所以 ptr 先和 [] 结合成为数组，然后再和 int * 结合形成数组的元素类型是 int * 类型，
	// 	 //得到一个叫一个数组的元素是指针，简称指针数组。
	// 	 int *(ptr[3]);//指针数组
	// 
	// 	 int(*ptr)[3];//优先级顺序是 * 小于 ()，() 等于 []，() 和 [] 的优先级一样，但是结合顺序是从左到右，所以先是 () 里的 * 和 ptr 结合成为一个指针，
	//然后是 (*ptr) 和 [] 相结合成为一个数组，最后叫一个指针 ptr 指向一个数组，简称数组指针。
}
