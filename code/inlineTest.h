#pragma once
#ifndef INLINETEST_H_
#define INLINETEST_H_
#include <iostream>
using namespace std;

class InlineA
{
public:
	/**
	* @brief ���ж����˵ĺ�������ʽ��������,����Ҫ���Ϊ����������������ʵ�ִ�(���崦)��inline�ؼ��֡�
	*
	* @param x
	* @param y
	*/
	int Foo(int x, int y) ///< ���弴��ʽ����������
	{
		return x + y;
	}
	void f1(int x); ///< ������Ҫ���Ϊ���������������ڶ��崦��inline�ؼ��֡�  

};

// ���崦��inline�ؼ��֣��Ƽ�����д����
inline void InlineA::f1(int x) {

}




#endif