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
	// ָ���е������ַ
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

		// ָ����һ��λ��
		ptr++;
		i++;
	}
}

void testPoint2()
{
	int var[5] = { 0,1,2,3,4 };
	int *ptr = NULL;
	ptr = var;
	ptr++;//��ȷ
	*ptr = 1;
	*var = 5;
	//var++;

	const int MAX = 3;
	int  var2[MAX] = { 10, 100, 200 };
	int *ptr2[MAX];//�� ptr ����Ϊһ�����飬�� MAX ������ָ�����,ptr �е�ÿ��Ԫ�أ�����һ��ָ�� int ֵ��ָ�롣
	ptr2[0] = &var2[0];
	cout << *ptr2[0] << endl;

	const char *names[MAX] = { "Zara Ali", "Hina Ali", "Nuha Ali" };//��ָ������,�����Ǵ洢ָ�������,

	// 	 int *ptr[3];
	// 	 //���� C++ ����������ȼ��У�* С�� []������ ptr �Ⱥ� [] ��ϳ�Ϊ���飬Ȼ���ٺ� int * ����γ������Ԫ�������� int * ���ͣ�
	// 	 //�õ�һ����һ�������Ԫ����ָ�룬���ָ�����顣
	// 	 int *(ptr[3]);//ָ������
	// 
	// 	 int(*ptr)[3];//���ȼ�˳���� * С�� ()��() ���� []��() �� [] �����ȼ�һ�������ǽ��˳���Ǵ����ң��������� () ��� * �� ptr ��ϳ�Ϊһ��ָ�룬
	//Ȼ���� (*ptr) �� [] ���ϳ�Ϊһ�����飬����һ��ָ�� ptr ָ��һ�����飬�������ָ�롣
}
