// ���� ����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Sort.h"
#include <iostream>
using namespace std;

//����
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
	{//����n-1��ѡ��
		int index = i;
		for (int j = i + 1; j <= n; j++)//��������ѡȡ��С�ļ�¼
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

	//���ǿ�������һ����־λ��������ʾ��ǰ�� i ���Ƿ��н������������Ҫ���� i+1 �ˣ����û�У���˵����ǰ�����Ѿ��������
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

	//����һ����־λ����¼һ�µ�ǰ�� i �������������һ��λ�õ��±꣬�ڽ��е� i+1 �˵�ʱ��
	//ֻ��Ҫ��ѭ��������±��λ�þͿ����ˣ���Ϊ����λ���ϵ�Ԫ������һ����û�л�λ����һ��Ҳ�����ܻỻλ���ˡ�

	int c[] = { 6,4,7,5,1,3,2 };
	//int c[] = { 1,3,5,2,4,6,7 };
	int len3 = sizeof(c) / sizeof(int);
	int len4 = sizeof(c) / sizeof(int) - 1;

	int tempPostion = 0;  // ��¼���һ�ν�����λ��
						  // Ҫ�����Ĵ���
	for (int i = 0; i < len3; i++)
	{
		int flag = 0;
		//���εıȽ������������Ĵ�С������һ�κ󣬰������е�iС�������ڵ�i��λ����
		for (int j = 0; j < len4; j++)
		{
			if (c[j] < c[j + 1])
			{
				flag = 1;
				int temp = c[j];
				c[j] = c[j + 1];
				c[j + 1] = temp;
				tempPostion = j; //��¼������λ��
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

