#pragma once
#include <iostream>
using namespace std;
class Student
{
public:
	virtual void takeTest() = 0;
};

class Cheater :public Student
{
public:
	void takeTest();
};

class Proxy :public Student
{
private:
	Student &pch;
public:
	Proxy(Student &stu);
	void takeTest();
};