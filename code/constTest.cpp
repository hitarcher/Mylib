#include "stdafx.h"
#include "constTest.h"

//δ��const���εı�������Ҫextern��ʽ������
int testint =1;
//��const����Ĭ��Ϊextern��Ҫʹconst�����ܹ��������ļ��з��ʣ��������ļ�����ʽ��ָ����Ϊextern
//��Ϊ�����ڶ����Ͳ��ܱ��޸ģ����Զ���ʱ�����ʼ����
extern const int testint2 = 2;

Myconst::Myconst()
{

}

Myconst::~Myconst()
{

}

Apple::Apple(int num)
	:apple_num(num)
{}
int Myconst:: ap =1;

//add�����ֵ�����const���ε�take������֤���˷�const������Է�������ĳ�Ա����,����const��Ա������
int Apple::add(int num) 
{
	take(num);
	return 0;
}

int Apple::add(int num) const 
{
	take(num+1);
	return 0;
}

void Apple::take(int num) const
{
	cout << "take func " << num << endl;
}

//getCount()�����е�����һ��add��������add��������const���Σ��������б���Ҳ����˵const����ֻ�ܷ���const��Ա����
int Apple::getCount() const
{
	take(1);
	//add(); //error
	return apple_num;
}

void getfun()
{
	//AfxMessageBox("happy");
}

void ConstFunc()
{
	const int *a ;
	const int b = 1;
	int c = 2;
	int *d;
	int e = 3;
	//const int i, j = 0//i Ϊ������������г�ʼ����(��Ϊ�����ڶ����Ͳ��ܱ��޸ģ����Զ���ʱ�����ʼ����)

	//1 const ����ĵ�ַֻ�ܸ�ֵ��ָ��const �����ָ��
	a = &b;
	//c = &b;//error

	//2 ����ѷ�const����ĵ�ַ����ָ��const�����ָ�롣
	a = &c;
	//*a = 2;//error *a��ֵ�̶�

	/*���Ҳ���������ģ�ʩ���ߣ����Ҳ��ֵ���Ƿ���ϡ�*/

	const void* vp = &b;
	//void* vp = &b; //error

	//constָ�������г�ʼ������constָ���ֵ�����޸ġ�
	int *const t1 = &c;
	*t1 = 3;
	int *t = &c;
	*t = 3;


}
 