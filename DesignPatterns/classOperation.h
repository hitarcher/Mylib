#pragma once
#include <iostream>
using namespace std;
#include <functional>
#include <vector>

class Base
{
public:
	virtual void test(int a)//无virtual就执行这个
	{
		cout << "this is base" << endl;
	}
};

class Ship :public Base
{
public:
	void test(int a)
	{
		cout << "this is Base overwrite function" << endl;
	}
};
/*************************************************************************************************/
class Ex
{
private:
	int val;
public:
	static int y;

	void display()const
	{
		//this->val = 10;//const Ex*this ,表达式必须是可修改的左值
	}
	static void fun();
};
/*************************************************************************************************/

//可以自己定义Exception 
class myexception : public exception
{
	virtual const char* what() const throw()
	{
		return "My exception happened";
	}
};
/*************************************************************************************************/

class Point
{
private:
	int x;
	int y;
public:
	int getx() const { return this->x; }
	int gety() const { return this->y; }

	void setx(int x) { this->x = x; }
	void sety(int y) { this->y = y; }

	Point(int x = 0, int y = 0);
	~Point();
	const Point operator +(const Point &rhs);
	//const Point operator +(const Point &lhs, const Point &rhs);//似乎不能同时存在
	const Point operator-(const Point &rhs);

	const Point &operator++();
	const Point operator++(int);
};


// std::function<int(int)> add_x(int x)
// {
// 	return [&](int a) { return x + a; };//x为临时变量
// }
/*************************************************************************************************/

class Filter
{
public:
	Filter(int divisorVal, int a, int b) :
		divisor{ divisorVal }, a(a), b(b)
	{}

	// 	std::function<bool(int)> getFilter()
	// 	{
	// 		return [=](int value) {return value % this->divisor == 0; };
	// 	}
	// 	std::function<bool(int)> getFilter()
	// 	{
	// 		return [divisor](int value) {return value % divisor == 0; };
	// 	}
	// 	std::function<int(int, int)>getInt()
	// 	{
	// 		return[=](int a, int b) {return a + b; };
	// 	}
private:
	int divisor;
	int a;
	int b;
};
// std::function<int(int, int)>getInt()
// {
// 	return[=](int a, int b) {return a + b; };
// }
/*************************************************************************************************/



/*************************************************************************************************/

class Person
{
private:
	string name;
public:
	Person(const string & str) { name = str; }
};

class student :public Person
{
private:
	int age;
public:
	student(const string &name, int age)
		:Person(name), age(age) {}
};

class Master :public student
{
private:
	int id;
public:
	Master(const string &name, int age, int id)
		:student(name, age), id(id) {}
};

/*************************************************************************************************/
class Bird
{
public:
	virtual void fly() = 0;
};

class WildGossse :public Bird
{
public:
	WildGossse() {}
	~WildGossse() {}

	virtual void fly()
	{
		cout << "WildGosses fly" << endl;
	}

};

class Parrot :public Bird
{
public:
	Parrot() {}
	~Parrot() {}

	virtual void fly()
	{
		cout << "Parrot fly" << endl;
	}

};

class Cage :public Bird
{
private:
	vector<Bird*>vecBird;
public:

};

/*************************************************************************************************/
class Stu
{
public:
	Stu() {}
	~Stu() {}
};


class MyString
{private:
	char* m_data;
public:
	MyString(const char* strTemp);
	~MyString();
	char* data();
	MyString(MyString & rhs);
};