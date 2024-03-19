#include "stdafx.h"
#include "TestRegex.h"
#include <iostream>
using namespace std;
#include <regex>
// Email地址
bool CheckEmail(char *username)
{
	//要转义
	regex object("^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$");
	bool bResult = regex_match(username,object);
	return bResult;
}
//英文和数字
bool CheckEnAndNum(char * username)
{
	regex object("^[A-Za-z0-9]+$ ");
	bool bResult = regex_match(username, object);
	return bResult;

}