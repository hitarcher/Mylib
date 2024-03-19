#pragma once
#include <iostream>
using namespace std;

class Animal
{
public:
	virtual void act() =0 ;
};

class Dog :public Animal
{
public:
	void act()
	{
		cout << "dog jump" << endl;
	}
};

class Cat :public Animal
{
public:
	void act()
	{
		cout << "cat miao" << endl;
	}

};

class Trainer
{
private:
	Animal *an[10];
	int num;
public:
	Trainer();
	void addAn(Animal *a1);
	void deleteAN(Animal *a2);
	void allAct();

};

