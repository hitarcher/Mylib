#pragma once
#include <iostream>
using namespace std;

class Travel
{
public:
	virtual void travel() = 0;
};

class Plane :public Travel
{
public:
	void travel() {
		cout << "fly" <<endl;
	}
};

class Foot :public Travel
{
public:
	void travel()
	{
		cout << "walk" << endl;
	}
};
class Boot :public Travel
{
public:
	void travel()
	{
		cout << "swim" << endl;
	}

};

class Traveler
{
private:
	Travel *ways;
public:
	Traveler(Travel *way);
	void taketravl();
	void setTravel(Travel *way) { this->ways = way; }
	Travel* returneTravel() { return ways; }
};