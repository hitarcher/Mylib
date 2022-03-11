#include "stdafx.h"
#include "constTest.h"

//未被const修饰的变量不需要extern显式声明！
int testint =1;
//非const变量默认为extern。要使const变量能够在其他文件中访问，必须在文件中显式地指定它为extern
//因为常量在定义后就不能被修改，所以定义时必须初始化。
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

//add方法又调用了const修饰的take方法，证明了非const对象可以访问任意的成员函数,包括const成员函数。
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

//getCount()方法中调用了一个add方法，而add方法并非const修饰，所以运行报错。也就是说const对象只能访问const成员函数
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
	//const int i, j = 0//i 为常量，必须进行初始化！(因为常量在定义后就不能被修改，所以定义时必须初始化。)

	//1 const 对象的地址只能赋值给指向const 对象的指针
	a = &b;
	//c = &b;//error

	//2 允许把非const对象的地址赋给指向const对象的指针。
	a = &c;
	//*a = 2;//error *a的值固定

	/*在右侧就是主动的，施加者，看右侧的值的是否符合。*/

	const void* vp = &b;
	//void* vp = &b; //error

	//const指针必须进行初始化，且const指针的值不能修改。
	int *const t1 = &c;
	*t1 = 3;
	int *t = &c;
	*t = 3;


}
 