#include "stdafx.h"
#include "TestRegex.h"
#include <iostream>
using namespace std;
#include <regex>
// Email��ַ
bool CheckEmail(char *username)
{
	//Ҫת��
	regex object("^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$");
	bool bResult = regex_match(username,object);
	return bResult;
}
//Ӣ�ĺ�����
bool CheckEnAndNum(char * username)
{
	regex object("^[A-Za-z0-9]+$ ");
	bool bResult = regex_match(username, object);
	return bResult;

}