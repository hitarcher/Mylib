#include "stdafx.h"
#include "stringTest.h"

void testStr()
{
	//1 char[] -> ������ֱ�Ӹ�ֵ
	char sz1[] = "1";

	//char[] -> char*
	char *sz2 = sz1;

	//char[]->const char* 
	const char *sz3 = sz1;

	//char[]->string
	string sz4 = sz1;

	//char[]->CString
	CString sz5 = sz1;

	//2 ���� -> string ֱ�Ӹ�ֵ
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

	//char *תchar[]���ַ�����ʵ�֣����ܽ��и�ֵ����
	//char *-> char[]
	const char *st = "hehe";
	char st1[] = "lalalala";
	//����3����ͬ
	strncpy(st1, st, strlen(st) + 1); // ע���1����
	strcpy(st1, st);//strcpy�Ѻ���'\0'���������ַ������Ƶ���һ����ַ�ռ�
	memcpy(st1, st, strlen(st) + 1);
	// tp = temp; //���󣬲���ʵ��
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
	//���sz���̣�sz��\0�����ǣ�����sz�����
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
	int ilen = stra.length();//size()��length()��ȫ��ͬ���������ַ����ᱻ�ضϣ����Է����ַ�����ʵ����
	stra.append("4");
	int pos = stra.find("3");
	stra.replace(pos, 4, "");//��λ��pos��ʼ��֮���4���ַ��滻Ϊ�գ���ɾ��
							 //���Ӵ�runoob
	int first = stra.find_first_of("1"); //��ͷ��ʼѰ���ַ�'.'��λ��
	int last = stra.find_last_of("4");   //��β��ʼѰ���ַ�'.'��λ��
										 // substr() -- ����ĳ�����ַ���
	string strb = stra.substr(first + 1, last - first - 1);


}


