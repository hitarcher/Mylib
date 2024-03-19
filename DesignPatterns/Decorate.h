#pragma once
#include <iostream>
using namespace std;

class Coffee
{
protected:
	string name;
	double cost;
public:
	Coffee() {};
	virtual string get_name()
	{
		return name;
	}
	virtual double get_cost()
	{
		return cost;
	}

};

class whiteCoffee :public Coffee
{
public:
	whiteCoffee()
	{
		name = "whiteCoffee";
		cost = 12;
	}
};

class blackCoffee :public Coffee
{
public:
	blackCoffee()
	{
		name = "blackCoffee";
		cost = 13;
	}

};

class Add_things :public Coffee
{
public:
	virtual string get_name() = 0;
	virtual double get_cost() = 0;
};

class Milk :public Add_things
{
private:
	Coffee *coff;
public:
	Milk(Coffee *coffee)
	{
		coff = coffee;
	}
	virtual string get_name()
	{
		string A;
		A = coff->get_name() + " add milk";
		return A;
	}
	virtual double get_cost()
	{
		return coff->get_cost() + 3;
	}
};

class Suger :public Add_things
{
private: 
	Coffee *coff;
public:
	Suger(Coffee *coffee)
	{
		coff = coffee;
	}
	virtual string get_name()
	{
		string A;
		A = coff->get_name() + " add suger";
		return A;
	}
	virtual double get_cost()
	{
		return coff->get_cost() + 2;
	}
};