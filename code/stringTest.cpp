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
//
//void testPython()
//{
//	//***python����***//
//	Py_SetPythonHome(L"E:\\software\\Anaconda3");
//	//��ʼ��pythonģ��
//	Py_Initialize();
//	// ����ʼ���Ƿ�ɹ�  
//	if (!Py_IsInitialized())
//	{
//		cout << "��ʼ��ʧ��" << endl;
//		Py_Finalize();
//	}
//
//	PyObject *pModule;
//	PyObject*pFunc = NULL;
//	PyObject*pArg = NULL;
//	PyRun_SimpleString("import sys");
//	PyRun_SimpleString("sys.path.append('./')");//����pythonģ�飬��Ѱλ�ã��ļ�����.cpp�ļ�һ��
//
//	//ʹ��PyObject* pModule���洢�����.py�ļ�ģ��, 
//	pModule = PyImport_ImportModule("tt1");//Python�ļ���  �����ļ�     
//	if (!pModule) {
//		cout << "py�ļ�����ʧ��" << endl;
//		Py_Finalize();
//	}
//	else {
//		pFunc = PyObject_GetAttrString(pModule, "run");//Python�ļ��еĺ�����  
//		if (!pFunc) {
//			cout << "��������ʧ��" << endl;
//			Py_Finalize();
//		}
//
//		PyObject* pyParams = Py_BuildValue("(s)", "helllo world!");//c++����תpython����
//
//		char * result1;
//		pArg = PyEval_CallObject(pFunc, pyParams);//���ú���
//		PyArg_Parse(pArg, "s", &result1);//python����תc++����
//		cout << result1 << endl;
//	}
//}
//
//void testPython2()
//{
//	Py_SetPythonHome(L"E:\\software\\Anaconda3");
//
//	Py_Initialize(); // ��ʼ��python�����
//	PyObject* pyMod = PyImport_ImportModule("test4"); //  ����test.py�ļ�
//	//ʹ��PyObject* pDict���洢����ģ���еķ����ֵ�
//	PyObject* pyDict = PyModule_GetDict(pyMod); //  ��ȡtestģ���е��ֵ�
//	PyObject* pyCls = PyDict_GetItemString(pyDict, "tester"); // ���ֵ��в���tester��
//	//PyObject* PyIns = PyInstance_New(pyCls, NULL, NULL); // ����tester��
//	PyObject* pConstruct = PyInstanceMethod_New(pyCls);
//	PyObject* pIns = PyObject_CallObject(pConstruct, nullptr);
//	PyObject* pyRet = PyObject_CallMethod(pIns, "add", "ii", 5, 6); // ����tester.add����������2��int�Ͳ���
//	int ok = -1;
//	int retok = PyArg_Parse(pyRet, "i", &ok); // �ӷ���ֵ��ȡ��int�ͷ���ֵ
//	Py_Finalize();
//}
//
//int testPython3()
//{
//	Py_Initialize();//ʹ��python֮ǰ��Ҫ����Py_Initialize();����������г�ʼ��
//	if (!Py_IsInitialized())
//	{
//		printf("��ʼ��ʧ�ܣ�");
//		return 0;
//	}
//
//	PyRun_SimpleString("import sys");
//	PyRun_SimpleString("sys.path.append('./')");//��һ������Ҫ���޸�Python·��
//
//
//	PyObject * pModule = NULL;//��������
//	PyObject * pFunc1 = NULL;// ��������
//	PyObject * pFunc2 = NULL;// ��������
//	PyObject * pFunc3 = NULL;// ��������
//	pModule = PyImport_ImportModule("mytest");//������Ҫ���õ��ļ���hello.py
//	if (pModule == NULL)
//	{
//		cout << "û�ҵ�" << endl;
//	}
//	//1
//	pFunc1 = PyObject_GetAttrString(pModule, "zip_file");//������Ҫ���õĺ�����
//	PyEval_CallObject(pFunc1, NULL);//�����޲����޷���ֵ��python����
//
//	//2
//	pFunc2 = PyObject_GetAttrString(pModule, "zip_file");//������Ҫ���õĺ�����
//	string readpath = R"(C:\Users\admin\Desktop\TestData)";
//	string writepath = R"(C:\Users\admin\Desktop\TestData.zip)";
//	PyObject* args = Py_BuildValue("ss", readpath.c_str(), writepath.c_str());//��python����������ֵ
//
//	PyObject_CallObject(pFunc2, args);//���ú���
//	//3
//	pFunc3 = PyObject_GetAttrString(pModule, "_getValue");//������Ҫ���õĺ�����
//	PyObject* args2 = Py_BuildValue("ii", 28, 103);//��python����������ֵ
//
//	PyObject* pRet = PyObject_CallObject(pFunc3, args2);//���ú���
//	int res = 0;
//	PyArg_Parse(pRet, "i", &res);//ת����������
//
//	cout << "res:" << res << endl;//������
//
//	Py_Finalize(); // ���ʼ����Ӧ
//	system("pause");
//	return 0;
//
//
//}
//
//int testPython4()
//{
//	Py_SetPythonHome(L"E:\\software\\Anaconda3");
//	Py_Initialize();//ʹ��python֮ǰ��Ҫ����Py_Initialize();����������г�ʼ��
//	if (!Py_IsInitialized())
//	{
//		AfxMessageBox("��ʼ��ʧ�ܣ�");
//		return 0;
//	}
//	PyRun_SimpleString("import sys");
//	PyRun_SimpleString("sys.path.append('./')");//��һ������Ҫ���޸�Python·��
//
//
//	PyObject * pModule = NULL;//��������
//	PyObject * pFunc = NULL;// ��������
//	pModule = PyImport_ImportModule("hello");//������Ҫ���õ��ļ���hello.py
//	if (pModule == NULL)
//	{
//		AfxMessageBox("û�ҵ���");
//	}
//	pFunc = PyObject_GetAttrString(pModule, "add_num");//������Ҫ���õĺ�����
//	if (!pFunc || !PyCallable_Check(pFunc))  // ��֤�Ƿ���سɹ�
//	{
//		AfxMessageBox("[ERROR] Can't find funftion (add_num)");
//		return 0;
//	}
//	//��python����������ֵ
//	/******************��ʽ1***********************/
//	PyObject* args = Py_BuildValue("(ii)", 28, 103);
//
//	/******************��ʽ2***********************/
//	// 	PyObject *pArgs = PyTuple_New(2);//�������õĲ������ݾ�����Ԫ�����ʽ�����,2��ʾ��������
//	// 	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 2));
//	// 	PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 4));
//
//	PyObject* pRet = PyEval_CallObject(pFunc, args);//���ú���
//
//	int res = 0;
//	PyArg_Parse(pRet, "i", &res);//ת����������
//
//	cout << "res:" << res << endl;//������
//	Py_Finalize();//����Py_Finalize�������Py_Initialize���Ӧ�ġ�
//
//}


void testbooble()
{
	int a[] = { 5,4,3,1,2 };
	int len = sizeof(a) / sizeof(int);
	for (int i = 0; i<len - 1; i++)
	{
		for (int j = 0; j<len - 1 - i; j++)
		{
			if (a[j] < a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}

	//���ǿ�������һ����־λ��������ʾ��ǰ�� i ���Ƿ��н������������Ҫ���� i+1 �ˣ����û�У���˵����ǰ�����Ѿ��������
	int b[] = { 5,4,3,1,2 };
	int len2 = sizeof(b) / sizeof(int);
	for (int i = 0; i < len - 1; i++)
	{
		int flag = 0;
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (b[j] < b[j + 1])
			{
				flag = 1;
				int temp = b[j];
				b[j] = b[j + 1];
				b[j + 1] = temp;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}

	//����һ����־λ����¼һ�µ�ǰ�� i �������������һ��λ�õ��±꣬�ڽ��е� i+1 �˵�ʱ��
	//ֻ��Ҫ��ѭ��������±��λ�þͿ����ˣ���Ϊ����λ���ϵ�Ԫ������һ����û�л�λ����һ��Ҳ�����ܻỻλ���ˡ�

	int c[] = { 6,4,7,5,1,3,2 };
	//int c[] = { 1,3,5,2,4,6,7 };
	int len3 = sizeof(c) / sizeof(int);
	int len4 = sizeof(c) / sizeof(int) - 1;

	int tempPostion = 0;  // ��¼���һ�ν�����λ��
						  // Ҫ�����Ĵ���
	for (int i = 0; i < len3; i++)
	{
		int flag = 0;
		//���εıȽ������������Ĵ�С������һ�κ󣬰������е�iС�������ڵ�i��λ����
		for (int j = 0; j < len4; j++)
		{
			if (c[j] < c[j + 1])
			{
				flag = 1;
				int temp = c[j];
				c[j] = c[j + 1];
				c[j + 1] = temp;
				tempPostion = j; //��¼������λ��
			}
		}
		len4 = tempPostion;
		if (flag == 0)
		{
			break;
		}
	}



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

void testPoint()
{
	int *p = NULL;
	// *p = 3;
	const int MAX = 3;
	int  var[MAX] = { 10, 100, 200 };
	int  *ptr;
	// ָ���е������ַ
	ptr = var;
	ptr++;
	ptr--;

	ptr = var;
	int i = 0;
	while (ptr <= &var[MAX - 1])
	{
		cout << "Address of var[" << i << "] = ";
		cout << ptr << endl;

		cout << "Value of var[" << i << "] = ";
		cout << *ptr << endl;

		// ָ����һ��λ��
		ptr++;
		i++;
	}
}

void testPoint2()
{
	int var[5] = { 0,1,2,3,4 };
	int *ptr = NULL;
	ptr = var;
	ptr++;//��ȷ
	*ptr = 1;
	*var = 5;
	//var++;

	const int MAX = 3;
	int  var2[MAX] = { 10, 100, 200 };
	int *ptr2[MAX];//�� ptr ����Ϊһ�����飬�� MAX ������ָ�����,ptr �е�ÿ��Ԫ�أ�����һ��ָ�� int ֵ��ָ�롣
	ptr2[0] = &var2[0];
	cout << *ptr2[0] << endl;

	const char *names[MAX] = { "Zara Ali", "Hina Ali", "Nuha Ali" };//��ָ������,�����Ǵ洢ָ�������,

																	// 	 int *ptr[3];
																	// 	 //���� C++ ����������ȼ��У�* С�� []������ ptr �Ⱥ� [] ��ϳ�Ϊ���飬Ȼ���ٺ� int * ����γ������Ԫ�������� int * ���ͣ�
																	// 	 //�õ�һ����һ�������Ԫ����ָ�룬���ָ�����顣
																	// 	 int *(ptr[3]);//ָ������
																	// 
																	// 	 int(*ptr)[3];//���ȼ�˳���� * С�� ()��() ���� []��() �� [] �����ȼ�һ�������ǽ��˳���Ǵ����ң��������� () ��� * �� ptr ��ϳ�Ϊһ��ָ�룬
																	//Ȼ���� (*ptr) �� [] ���ϳ�Ϊһ�����飬����һ��ָ�� ptr ָ��һ�����飬�������ָ�롣
}


