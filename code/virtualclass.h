#pragma once
#ifndef VIRTUALCLASS_H_
#define VIRTUALCLASS_H_
#include <iostream>
using namespace std;

//如果担心类名重复，可以这样使用
//namespace virtualTest{

// 抽象类
class Base {
protected:
	int x;
public:
	virtual void fun() = 0;
	Base(int i) { x = i; }  // 构造函数
};

// 派生类
class Derived : public Base
{
	int y;
public:
	Derived(int i, int j) 
		: Base(i) { y = j; } // 构造函数
	void fun()
	{ 
		cout << "x = " << x << ", y = " << y;
	}
};

// 抽象类
class Base1 {
public:
	Base1() { cout << "Constructor: Base" << endl; }
	virtual ~Base1() { 
		OutputDebugString("Destructor : Base");
		cout << "Destructor : Base" << endl; }

	virtual void func() = 0;
};

class Derived1 : public Base1 {
public:
	Derived1() { cout << "Constructor: Derived" << endl; }
	~Derived1() { cout << "Destructor : Derived" << endl; }

	void func() { cout << "In Derived.func()." << endl; }
};



//}
#endif