#pragma once
#ifndef INLINETEST_H_
#define INLINETEST_H_
#include <iostream>
using namespace std;

class InlineA
{
public:
	/**
	* @brief 类中定义了的函数是隐式内联函数,声明要想成为内联函数，必须在实现处(定义处)加inline关键字。
	*
	* @param x
	* @param y
	*/
	int Foo(int x, int y) ///< 定义即隐式内联函数！
	{
		return x + y;
	}
	void f1(int x); ///< 声明后，要想成为内联函数，必须在定义处加inline关键字。  

};

// 定义处加inline关键字，推荐这种写法！
inline void InlineA::f1(int x) {

}




#endif