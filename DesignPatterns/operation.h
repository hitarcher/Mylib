#pragma once

#include <iostream>
using namespace std;
/*************************************************************************************************/

class Operation
{
	//�������Ĭ�Ϲ��캯���͹���
public:
	void setA(double value) { _numberA = value; }
	void setB(double value) { _numberB = value; }

	double _numberA;
	double	_numberB;
	virtual double getResult()//��д
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
