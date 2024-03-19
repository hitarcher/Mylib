#pragma once
#include <iostream>
using namespace std;

class Mystring
{
private:
	char *m_data;

public:
	Mystring(char *str = 0);
	~Mystring();
	Mystring(const Mystring &rhs);
	Mystring &operator =(const Mystring &rhs);
	const Mystring operator +(const Mystring &rhs);
	const char* data() { return m_data; }
	Mystring & operator +=(const Mystring &rhs);
	const char& operator[](int index);
	bool operator ==(const Mystring &rhs);
	bool operator >(const Mystring &rhs);
	bool operator <(const Mystring &rhs);
};
