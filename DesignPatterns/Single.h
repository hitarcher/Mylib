#pragma once
#include <iostream>
using namespace std;

//只能创建一个对象
class Single
{
private:
	Single();
	static Single *interface;//那这个对象必须是这个类独有的
public:
	static Single* getinerface();//只有一个出口
};