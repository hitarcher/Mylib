#pragma once
#include "stdafx.h"
#include "Mystring.h"


Mystring::Mystring(char* data)
{
	if (data)
	{
		int len = strlen(data);
		this->m_data = new char[len + 1];
		strcpy(m_data, data);
		m_data[len] = '\0';
	}
	else
	{
		this->m_data = new char[1];
		m_data[0] = '\0';
	}
}
Mystring::~Mystring()
{
	if (m_data)
	{
		delete[] m_data;
	}
}
Mystring::Mystring(const Mystring &rhs)
{
	int len = strlen(rhs.m_data);
	this->m_data = new char[len + 1]();
	strcpy(this->m_data, rhs.m_data);
	this->m_data[len] = '\0';
}

Mystring& Mystring:: operator =(const Mystring &rhs)
{
	delete[]m_data;
	int len = strlen(rhs.m_data);
	this->m_data = new char[len + 1];
	strcpy(m_data, rhs.m_data);
	m_data[len] = '\0';
	return *this;
}

const Mystring Mystring:: operator+(const Mystring &rhs)
{
	int len = strlen(rhs.m_data) + strlen(this->m_data);
	char *tmp = new char[len + 1]();
	strcpy(tmp, this->m_data);
	strcat(tmp, rhs.m_data);
	Mystring st(tmp);
	delete[] tmp;
	return st;
}
Mystring & Mystring:: operator +=(const Mystring &rhs)
{
	*this = *this + rhs;
	return *this;
}

const char& Mystring::operator[](int index)
{
	return m_data[index];
}
bool Mystring ::operator== (const Mystring &rhs)
{
	return strcmp(m_data, rhs.m_data) == 0;
}

bool Mystring ::operator> (const Mystring &rhs)
{
	return strcmp(m_data, rhs.m_data) > 0;
}

bool Mystring ::operator< (const Mystring &rhs)
{
	return strcmp(m_data, rhs.m_data) < 0;
}

