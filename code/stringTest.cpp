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
//
//void testPython()
//{
//	//***python调用***//
//	Py_SetPythonHome(L"E:\\software\\Anaconda3");
//	//初始化python模块
//	Py_Initialize();
//	// 检查初始化是否成功  
//	if (!Py_IsInitialized())
//	{
//		cout << "初始化失败" << endl;
//		Py_Finalize();
//	}
//
//	PyObject *pModule;
//	PyObject*pFunc = NULL;
//	PyObject*pArg = NULL;
//	PyRun_SimpleString("import sys");
//	PyRun_SimpleString("sys.path.append('./')");//设置python模块，搜寻位置，文件放在.cpp文件一起
//
//	//使用PyObject* pModule来存储导入的.py文件模块, 
//	pModule = PyImport_ImportModule("tt1");//Python文件名  加载文件     
//	if (!pModule) {
//		cout << "py文件导入失败" << endl;
//		Py_Finalize();
//	}
//	else {
//		pFunc = PyObject_GetAttrString(pModule, "run");//Python文件中的函数名  
//		if (!pFunc) {
//			cout << "函数导入失败" << endl;
//			Py_Finalize();
//		}
//
//		PyObject* pyParams = Py_BuildValue("(s)", "helllo world!");//c++类型转python类型
//
//		char * result1;
//		pArg = PyEval_CallObject(pFunc, pyParams);//调用函数
//		PyArg_Parse(pArg, "s", &result1);//python类型转c++类型
//		cout << result1 << endl;
//	}
//}
//
//void testPython2()
//{
//	Py_SetPythonHome(L"E:\\software\\Anaconda3");
//
//	Py_Initialize(); // 初始化python虚拟机
//	PyObject* pyMod = PyImport_ImportModule("test4"); //  加载test.py文件
//	//使用PyObject* pDict来存储导入模块中的方法字典
//	PyObject* pyDict = PyModule_GetDict(pyMod); //  获取test模块中的字典
//	PyObject* pyCls = PyDict_GetItemString(pyDict, "tester"); // 从字典中查找tester类
//	//PyObject* PyIns = PyInstance_New(pyCls, NULL, NULL); // 创建tester类
//	PyObject* pConstruct = PyInstanceMethod_New(pyCls);
//	PyObject* pIns = PyObject_CallObject(pConstruct, nullptr);
//	PyObject* pyRet = PyObject_CallMethod(pIns, "add", "ii", 5, 6); // 调用tester.add方法，传入2个int型参数
//	int ok = -1;
//	int retok = PyArg_Parse(pyRet, "i", &ok); // 从返回值从取出int型返回值
//	Py_Finalize();
//}
//
//int testPython3()
//{
//	Py_Initialize();//使用python之前，要调用Py_Initialize();这个函数进行初始化
//	if (!Py_IsInitialized())
//	{
//		printf("初始化失败！");
//		return 0;
//	}
//
//	PyRun_SimpleString("import sys");
//	PyRun_SimpleString("sys.path.append('./')");//这一步很重要，修改Python路径
//
//
//	PyObject * pModule = NULL;//声明变量
//	PyObject * pFunc1 = NULL;// 声明变量
//	PyObject * pFunc2 = NULL;// 声明变量
//	PyObject * pFunc3 = NULL;// 声明变量
//	pModule = PyImport_ImportModule("mytest");//这里是要调用的文件名hello.py
//	if (pModule == NULL)
//	{
//		cout << "没找到" << endl;
//	}
//	//1
//	pFunc1 = PyObject_GetAttrString(pModule, "zip_file");//这里是要调用的函数名
//	PyEval_CallObject(pFunc1, NULL);//调用无参数无返回值的python函数
//
//	//2
//	pFunc2 = PyObject_GetAttrString(pModule, "zip_file");//这里是要调用的函数名
//	string readpath = R"(C:\Users\admin\Desktop\TestData)";
//	string writepath = R"(C:\Users\admin\Desktop\TestData.zip)";
//	PyObject* args = Py_BuildValue("ss", readpath.c_str(), writepath.c_str());//给python函数参数赋值
//
//	PyObject_CallObject(pFunc2, args);//调用函数
//	//3
//	pFunc3 = PyObject_GetAttrString(pModule, "_getValue");//这里是要调用的函数名
//	PyObject* args2 = Py_BuildValue("ii", 28, 103);//给python函数参数赋值
//
//	PyObject* pRet = PyObject_CallObject(pFunc3, args2);//调用函数
//	int res = 0;
//	PyArg_Parse(pRet, "i", &res);//转换返回类型
//
//	cout << "res:" << res << endl;//输出结果
//
//	Py_Finalize(); // 与初始化对应
//	system("pause");
//	return 0;
//
//
//}
//
//int testPython4()
//{
//	Py_SetPythonHome(L"E:\\software\\Anaconda3");
//	Py_Initialize();//使用python之前，要调用Py_Initialize();这个函数进行初始化
//	if (!Py_IsInitialized())
//	{
//		AfxMessageBox("初始化失败！");
//		return 0;
//	}
//	PyRun_SimpleString("import sys");
//	PyRun_SimpleString("sys.path.append('./')");//这一步很重要，修改Python路径
//
//
//	PyObject * pModule = NULL;//声明变量
//	PyObject * pFunc = NULL;// 声明变量
//	pModule = PyImport_ImportModule("hello");//这里是要调用的文件名hello.py
//	if (pModule == NULL)
//	{
//		AfxMessageBox("没找到！");
//	}
//	pFunc = PyObject_GetAttrString(pModule, "add_num");//这里是要调用的函数名
//	if (!pFunc || !PyCallable_Check(pFunc))  // 验证是否加载成功
//	{
//		AfxMessageBox("[ERROR] Can't find funftion (add_num)");
//		return 0;
//	}
//	//给python函数参数赋值
//	/******************方式1***********************/
//	PyObject* args = Py_BuildValue("(ii)", 28, 103);
//
//	/******************方式2***********************/
//	// 	PyObject *pArgs = PyTuple_New(2);//函数调用的参数传递均是以元组的形式打包的,2表示参数个数
//	// 	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 2));
//	// 	PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 4));
//
//	PyObject* pRet = PyEval_CallObject(pFunc, args);//调用函数
//
//	int res = 0;
//	PyArg_Parse(pRet, "i", &res);//转换返回类型
//
//	cout << "res:" << res << endl;//输出结果
//	Py_Finalize();//调用Py_Finalize，这个根Py_Initialize相对应的。
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

	//我们可以设置一个标志位，用来表示当前第 i 趟是否有交换，如果有则要进行 i+1 趟，如果没有，则说明当前数组已经完成排序。
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

	//利用一个标志位，记录一下当前第 i 趟所交换的最后一个位置的下标，在进行第 i+1 趟的时候，
	//只需要内循环到这个下标的位置就可以了，因为后面位置上的元素在上一趟中没有换位，这一次也不可能会换位置了。

	int c[] = { 6,4,7,5,1,3,2 };
	//int c[] = { 1,3,5,2,4,6,7 };
	int len3 = sizeof(c) / sizeof(int);
	int len4 = sizeof(c) / sizeof(int) - 1;

	int tempPostion = 0;  // 记录最后一次交换的位置
						  // 要遍历的次数
	for (int i = 0; i < len3; i++)
	{
		int flag = 0;
		//依次的比较相邻两个数的大小，遍历一次后，把数组中第i小的数放在第i个位置上
		for (int j = 0; j < len4; j++)
		{
			if (c[j] < c[j + 1])
			{
				flag = 1;
				int temp = c[j];
				c[j] = c[j + 1];
				c[j + 1] = temp;
				tempPostion = j; //记录交换的位置
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

void testPoint()
{
	int *p = NULL;
	// *p = 3;
	const int MAX = 3;
	int  var[MAX] = { 10, 100, 200 };
	int  *ptr;
	// 指针中的数组地址
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

		// 指向上一个位置
		ptr++;
		i++;
	}
}

void testPoint2()
{
	int var[5] = { 0,1,2,3,4 };
	int *ptr = NULL;
	ptr = var;
	ptr++;//正确
	*ptr = 1;
	*var = 5;
	//var++;

	const int MAX = 3;
	int  var2[MAX] = { 10, 100, 200 };
	int *ptr2[MAX];//把 ptr 声明为一个数组，由 MAX 个整数指针组成,ptr 中的每个元素，都是一个指向 int 值的指针。
	ptr2[0] = &var2[0];
	cout << *ptr2[0] << endl;

	const char *names[MAX] = { "Zara Ali", "Hina Ali", "Nuha Ali" };//是指针数组,本质是存储指针的数组,

																	// 	 int *ptr[3];
																	// 	 //由于 C++ 运算符的优先级中，* 小于 []，所以 ptr 先和 [] 结合成为数组，然后再和 int * 结合形成数组的元素类型是 int * 类型，
																	// 	 //得到一个叫一个数组的元素是指针，简称指针数组。
																	// 	 int *(ptr[3]);//指针数组
																	// 
																	// 	 int(*ptr)[3];//优先级顺序是 * 小于 ()，() 等于 []，() 和 [] 的优先级一样，但是结合顺序是从左到右，所以先是 () 里的 * 和 ptr 结合成为一个指针，
																	//然后是 (*ptr) 和 [] 相结合成为一个数组，最后叫一个指针 ptr 指向一个数组，简称数组指针。
}


