#pragma once
#include "stdafx.h"
#include "pfun.h"

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
{ cout << a << endl; }

int main() {
	func pfun = myfunc;/*��ֵ*/
	pfun();/*����*/
	pFun = glFun;
	(*pFun)(2);
}