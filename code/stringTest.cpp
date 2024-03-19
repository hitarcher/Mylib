#include "stdafx.h"
#include "stringTest.h"

void testStr()
{
	//1 char[] -> 其他，直接赋值
	char sz1[] = "1";

	//char[] -> char*
	char *sz2 = sz1;

	//char[]->const char* 
	const char *sz3 = sz1;

	//char[]->string
	string sz4 = sz1;

	//char[]->CString
	CString sz5 = sz1;

	//2 其他 -> string 直接赋值
	string str3 = sz1;//char[]
	string str2 = sz2;//char *
	string str1 = sz3;//const char *

					  //string ->const char*
	const char *cst = str1.c_str();

	//stirng ->char*
	const char* cst2 = str1.c_str();
	sz2 = const_cast<char*>(cst2);

	//string ->char[]
	for (int i = 0; i<str1.length(); i++)
	{
		sz1[i] = str1[i];
	}

	//3 const char* ->

	// const char* -> char*
	sz2 = const_cast<char*>(cst2);

	//const char* ->char[]

	//char *转char[]：字符拷贝实现，不能进行赋值操作
	//char *-> char[]
	const char *st = "hehe";
	char st1[] = "lalalala";
	//下面3个等同
	strncpy(st1, st, strlen(st) + 1); // 注意加1操作
	strcpy(st1, st);//strcpy把含有'\0'结束符的字符串复制到另一个地址空间
	memcpy(st1, st, strlen(st) + 1);
	// tp = temp; //错误，不能实现
	{
		char s1[] = "abcd12349";
		char s2[] = "xyz";
		int i;
		strcpy(s1, s2);
		for (i = 0; i < 10; i++)
			printf("%c|", s1[i]);
	}

	//4 char* ->

	// char *->cosnt char *
	cst2 = sz2;

	//char *->char[]
	char *ss1 = "123";
	char ss2[] = "";
	strncpy(ss2, ss1, strlen(ss1) + 1);


}

void testStr2()
{
	char sz[100] = "123";
	char *st = "1234";
	const char * cst = "12345";
	string str = "123456";
	CString str2 = "1234567";
	/************************* string -> ************************************/
	//1 string ->char *
	cst = str.c_str();
	st = const_cast<char*>(cst);
	//2 string ->const char*
	cst = str.c_str();
	//3 string ->char []
	//如果sz过短，sz的\0被覆盖，再用sz会出错
	for (int i = 0; i<str.length(); i++)
	{
		sz[i] = str[i];
	}
	//4 string ->CString 
	str2 = str.c_str();
	/************************* char[] -> ************************************/
	// 1 char[] ->char*
	st = sz;
	//2 char [] ->const char *
	cst = sz;
	//3 char [] ->string 
	str = sz;
	//4 char [] ->CString 
	str2 = sz;
	/************************* char* -> ************************************/
	strcpy(st, "1234");

	//1 char * -> string
	str = st;
	//2 char * -> const char *
	cst = st;
	//3 char *-> char[]
	strncpy(sz, st, strlen(st) + 1);
	//4 char *  ->CString
	str2 = st;
	/*************************  const char* -> ************************************/
	cst = "12345";

	//1  const char* ->stirng 
	str = cst;
	//2  const char* ->char *
	st = const_cast<char*>(cst);
	//3  const char* ->char[]
	strncpy(sz, cst, strlen(cst) + 1);
	//4 const char * ->CString 
	str2 = cst;
	/************************* CString -> ************************************/
	str2 = "123456";

	//1 CString -> stirng 
	str = str2;
	//2.1 CString -> char *
	st = (LPTSTR)(LPCTSTR)str2;
	//2.2 
	st = str2.GetBuffer(str2.GetLength() + 1);
	//2.3
	int len1 = str2.GetLength() + 1;
	strncpy(st, str2, len1);
	strcpy(st, str2);
	memcpy(st, str2, str2.GetLength());
	//3 CString -> char[]
	memset(sz, 0, strlen(st));
	strncpy(sz, str2, len1);
	//4 CString -> const char *
	cst = str2;

}


void teststring()
{
	std::string stra = "123";
	int isize = stra.size();
	int ilen = stra.length();//size()与length()完全等同，遇到空字符不会被截断，可以返回字符串真实长度
	stra.append("4");
	int pos = stra.find("3");
	stra.replace(pos, 4, "");//从位置pos开始，之后的4个字符替换为空，即删除
							 //找子串runoob
	int first = stra.find_first_of("1"); //从头开始寻找字符'.'的位置
	int last = stra.find_last_of("4");   //从尾开始寻找字符'.'的位置
										 // substr() -- 返回某个子字符串
	string strb = stra.substr(first + 1, last - first - 1);


}


