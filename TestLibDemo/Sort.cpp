// 测试 排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Sort.h"
#include <iostream>
using namespace std;

//降序
int Compare(const void *x, const void *y)
{
	return *((int*)x) < *((int*)y);
}

void BoobleSort(int ary[], int len)
{
	int temp = 0, j = 0, i = 0;

	for (i = 0; i < len - 1; i++)
	{
		for (j = 0; j < len - 1 - i; j++)
		{
			if (ary[j] < ary[j + 1])
			{
				temp = ary[j];
				ary[j] = ary[j + 1];
				ary[j + 1] = temp;
			}
		}
	}
}

void selectSort(int a[], int n)
{
	for (int i = 1; i <= n - 1; i++)
	{//进行n-1趟选择
		int index = i;
		for (int j = i + 1; j <= n; j++)//从无序区选取最小的记录
			if (a[index] > a[j])
				index = j;
		if (index != i)
			swap(a[i], a[index]);
	}
}


void testbooble()
{
	int a[] = { 5,4,3,1,2 };
	int len = sizeof(a) / sizeof(int);
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (a[j] < a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}

	//我们可以设置一个标志位，用来表示当前第 i 趟是否有交换，如果有则要进行 i+1 趟，如果没有，则说明当前数组已经完成排序。
	int b[] = { 5,4,3,1,2 };
	int len2 = sizeof(b) / sizeof(int);
	for (int i = 0; i < len - 1; i++)
	{
		int flag = 0;
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (b[j] < b[j + 1])
			{
				flag = 1;
				int temp = b[j];
				b[j] = b[j + 1];
				b[j + 1] = temp;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}

	//利用一个标志位，记录一下当前第 i 趟所交换的最后一个位置的下标，在进行第 i+1 趟的时候，
	//只需要内循环到这个下标的位置就可以了，因为后面位置上的元素在上一趟中没有换位，这一次也不可能会换位置了。

	int c[] = { 6,4,7,5,1,3,2 };
	//int c[] = { 1,3,5,2,4,6,7 };
	int len3 = sizeof(c) / sizeof(int);
	int len4 = sizeof(c) / sizeof(int) - 1;

	int tempPostion = 0;  // 记录最后一次交换的位置
						  // 要遍历的次数
	for (int i = 0; i < len3; i++)
	{
		int flag = 0;
		//依次的比较相邻两个数的大小，遍历一次后，把数组中第i小的数放在第i个位置上
		for (int j = 0; j < len4; j++)
		{
			if (c[j] < c[j + 1])
			{
				flag = 1;
				int temp = c[j];
				c[j] = c[j + 1];
				c[j + 1] = temp;
				tempPostion = j; //记录交换的位置
			}
		}
		len4 = tempPostion;
		if (flag == 0)
		{
			break;
		}
	}



}

void  testSort()
{
	int ary[10] = { 1,2,3,4,5,6,7,8,9,10 };
	qsort(ary, 10, sizeof(int), Compare);

}

