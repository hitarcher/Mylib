#pragma once
#define LOG_NAME_DEBUG "debug.log"

#ifndef VIRTUALCLASS_H_
#define VIRTUALCLASS_H_
#include <iostream>
using namespace std;
#include "mylog.h"

//������������ظ�����������ʹ��
//namespace virtualTest{

// ������
class Base {
protected:
	int x;
public:
	virtual void fun() = 0;
	Base(int i) { x = i; }  // ���캯��
};

// ������
class Derived : public Base
{
	int y;
public:
	Derived(int i, int j) 
		: Base(i) { y = j; } // ���캯��
	void fun()
	{ 
		cout << "x = " << x << ", y = " << y;
	}
};

// ������
class Base1 {
public:
	Base1() {
		LOG(LOG_NAME_DEBUG, info, "Constructor: Base")
	};
	virtual ~Base1() {
		LOG(LOG_NAME_DEBUG, info, "Destructor: Base");
	}

	virtual void func() = 0;
};

class Derived1 : public Base1 {
public:
	Derived1() {
		LOG(LOG_NAME_DEBUG, info, "Constructor: Derived1");
	}
	~Derived1() {
		LOG(LOG_NAME_DEBUG, info, "Destructor: Derived1");
	}

	void func() {
		LOG(LOG_NAME_DEBUG, info, "In Derived.func().");
	}
};



//}
#endif