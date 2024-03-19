#pragma once
#include "stdafx.h"
#include "TestC.h"

//�滻A��B��ֵ
void changeAB(int *x, int *y)
{
	int a = *x;
	*x = *y;
	*y = a;
}

//�����ַ���
void reversearray(char *str)
{
	char *a = str;
	char *b = str + strlen(str) - 1;
	for (; a < b; a++, b--)
	{
		char c = *a;
		*a = *b;
		*b = c;
	}

}
//�����ַ���
char *mystrcpy(char *dest, char *src)
{
	char *temp = dest;
	while (*dest++ = *src++);
	return temp;
}

// ���ţ���С����
int cmp(const void*x, const void *y)
{
	return *((const char *)x) < *((const char *)y);
}

// ƴ���ַ���
void myStrcat(char *src, const char* dest)
{
	char *tmp = src;
	while (*src)src++;
	while (*src++ = *dest++);

}
//
union data {
	int 	x;
	char 	y;
};


/**

* @brief ������һ������pFun����������Ǹ�ָ�룬ָ�򷵻�ֵ�Ͳ������ǿյĺ�����ָ�룡
*/
void(*pFun)(int);

/**
* @brief ����һ�������ͣ����Ǳ�����������������pFun��һ����
*/
typedef void(*func)(void);

void myfunc(void)
{
	cout << "asda" << endl;
}

void glFun(int a)
{
	cout << a << endl;
}


void TestC()
{
	/*******************************************************/
	func pfun = myfunc;/*��ֵ*/
	pfun();/*����*/
	pFun = glFun;
	(*pFun)(2);

	/*******************************************************/
	int a1 = 1, b1 = 2;
	changeAB(&a1, &b1);
	printf("a=%d,b=%d", a1, b1);

	/*******************************************************/
	char d[20] = { "abcde" };
	reversearray(d);
	printf("%s", d);

	/*******************************************************/
	char sz1[20] = { "good" };
	char sz2[20] = { "morning" };
	mystrcpy(sz1, sz2);
	puts(sz1);

	/*******************************************************/
	int  sza[10] = { 0,1,2,3,4,5,6,7,8,9 };
	qsort(sza, 10, sizeof(int), cmp);
	for (int i = 0; i < 10; i++)
	{
		printf("%d", sza[i]);
	}

	/*******************************************************/
	char ch1[10] = "123";
	char ch2[10] = "456";
	myStrcat(ch1, ch2);
	puts(ch1);

	/*******************************************************/
	int *p = (int*)malloc(sizeof(int) * 10);
	memset(p, 0, sizeof(sizeof p));
	printf("%d", sizeof p);
	for (int i = 0; i < 10; i++)
	{
		p[i] = i + 1;
	}
	free(p);
	p = NULL;

	/*******************************************************/
	int x = 9;
	char *ch = (char*)&x;
	printf("%p", ch);
	ch += 4;
	printf("%p", ch);
	/*******************************************************/
	printf("%d\n", sizeof(union data));		//4 + 4



}

