#pragma once

#include <iostream>
using namespace std;
/*************************************************************************************************/

class Operation
{
	//构造就用默认构造函数就够了
public:
	void setA(double value) { _numberA = value; }
	void setB(double value) { _numberB = value; }

	double _numberA;
	double	_numberB;
	virtual double getResult()//重写
	{
		return 0;
	}
};

class OperationADD :public Operation
{
public:
	double getResult()
	{
		return _numberA + _numberB;
	}
};

class SimpleFactory
{
public:
	Operation * Createoperator(char sign)
	{
		Operation *op = NULL;
		switch (sign)
		{
		case '+':
			op = new OperationADD();
			break;
		default:
			break;
		}
		return op;
	}
};
/*************************************************************************************************/
