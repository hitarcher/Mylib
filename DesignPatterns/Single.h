#pragma once
#include <iostream>
using namespace std;

//ֻ�ܴ���һ������
class Single
{
private:
	Single();
	static Single *interface;//���������������������е�
public:
	static Single* getinerface();//ֻ��һ������
};