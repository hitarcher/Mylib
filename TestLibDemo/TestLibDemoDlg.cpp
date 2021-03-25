
// TestLibDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestLibDemo.h"
#include "TestLibDemoDlg.h"
#include "afxdialogex.h"

#include "MyLib.h"
#ifdef DEBUG
#pragma comment(lib,"MyLibd.lib")
#else
#pragma comment(lib,"MyLib.lib")
#endif // DEBUG

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <Python.h>
#pragma comment(lib,"python3_d.lib")
#pragma comment(lib,"python37_d.lib")
CRITICAL_SECTION g_cs;
 

#include  <direct.h>  
#pragma comment(lib,"URlmon")

struct ThreadInfo
{
	HANDLE hEvent;
	CString strPicPath;
	CString strIpsource;
	BOOL bcoustomState;
	int faceId;
	CTestLibDemoDlg* pThis;
	CString strBase64;
};

// CTestLibDemoDlg 对话框
BOOL g_bExit = FALSE;
ThreadInfo g_pthInfo;

void 	testPoint();
void	testPoint2();
CTestLibDemoDlg::CTestLibDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTLIBDEMO_DIALOG, pParent)
	, m_static1(_T(""))
{
	hTest = NULL;
	
	/*	1 null // SECURITY_ATTRIBUTES结构指针，可为NULL | 4 null //事件的名称
	2 manual 手动 manualReset 手动复位 
	3 initStatus 复位状态为假，阻塞 */
	hTestEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	hThread[3] = NULL;
	for (int i=0;i<3;i++)
	{
		hThreadEvent[i] = CreateEvent(NULL, FALSE, FALSE, NULL);//设置成自复位类型，否则，似乎会调用三次
	}

	hTest2 =NULL;
	hTestEvent2 = CreateEvent(NULL, TRUE, FALSE, NULL);

	Gdiplus::GdiplusStartupInput m_GdiplusStarupInput;
	ULONG_PTR m_uGdiplusToken;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestLibDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC1, m_static1);
}

BEGIN_MESSAGE_MAP(CTestLibDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CTestLibDemoDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

// CTestLibDemoDlg 消息处理程序
#include "mylog.hpp"
#include "LogConfig.h"
#include "LogProvider.h"
#include "LogUserConfig.h"
BOOL CTestLibDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码

	CString strIp = CheckIP();
	CString strMac1 = GetMacAddress(2);
	char a[1024];
	char b[1024];
	char c[1024];

// 	ObtainMAC(a);
// 	ObtainCPUID(b);
// 	ObtainHDID(c);

	auto aaa = new auto (1);


	InitLog();
	TakeLog("OnInitDialog", "fffffffffffffffffuck");
	//MYTVLog(strContent.GetBuffer(0));1
	MYTVLog("123","222");
	MYTVError("123");
	MYTVTraceBegin("123");
	MYTVTraceEnd("123");
	MYTVLogEx("123","456","2222");
	KKLogInfo("123", "456");
	DWORD dwThreadId = 0;
	//1 单线程
	//传入this指针，this,传入回调函数 TestThreadProc
	hTest = CreateThread(NULL, 0, TestThreadProc, this, 0, &dwThreadId);
	//2 多线程
	for (int i = 0; i < 3; i++)
	{
		hThread[i] = CreateThread(NULL, 0, TestMultipleThreadProc, this, 0, &dwThreadId);
	}
	//3 单线程 传参改变
	g_pthInfo.pThis = this;
	g_pthInfo.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	hTest2 = CreateThread(NULL, 0, TestThreadProc2, &g_pthInfo, 0, &dwThreadId);

// 	char buffer[MAX_PATH];
// 	_getcwd(buffer, MAX_PATH);
// 	strcat_s(buffer, "//1.jpg");
// 	HRESULT Result = URLDownloadToFileA(NULL, "url=/search/detail?ct=503316480&z=0&tn=baiduimagedetailnojs&ipn=dnj&&word=%E5%9B%BE%E7%89%87&cl=&lm=-1&pn=0&di=169950&ln=30&amp", buffer, 0, NULL);
	 string downurl = "http://www.anyuer.club";
	 string savepath = "D://abc.index";
	 download(downurl, savepath);

	//SetEvent(hTestEvent);
	SetEvent(hThreadEvent[2]);

// 	for (int i=0;i<10;i++)
// 	{
// 		CString str1 = GetCurTime(i);
// 	}
	CString str1 = getFullPath("1.txt");
	CString str2 = GetAppPathW();
	RemoveDir(getFullPath("21"));

	/*
		m_static1 为static的值，bRed初始化的原因是因为下面的switch，
		是按顺序来的，且不初始化，debug应该是true状态
		OnCtlColor 在工作框架的子窗口被重画时将调用该成员函数
		参数nCtlColor用于指定控件的类型,可以是:
		.CTLCOLOR_BTN                按钮控件
		.CTLCOLOR_DLG                对话框
		.CTLCOLOR_EDIT               编辑框
		.CTLCOLOR_LISTBOX            列表控件
		.CTLCOLOR_MSGBOX             消息控件
		.CTLCOLOR_SCROLLBAR 滚动条控件
		.CTLCOLOR_STATIC             静态控件
	*/
	m_bRed = FALSE;
	m_bGreen = FALSE;
	m_bBlue = TRUE;;
	m_static1 = "快点！！！";
	UpdateData(FALSE);

	//绘图
	Gdiplus::GdiplusStartup(&m_uGdiplusToken, &m_GdiplusStarupInput, nullptr);

	CString sss = getFullPath("2.jpg");//bmp可
	CStringW s(sss);   //转为宽字符
	m_img = Image::FromFile(s);  //加载图片

	//多线程对数据的操控
	/*多个线程操作相同的数据时，一般是需要按顺序访问的，否则会引导数据错乱，无法控制数据，变成随机变量。
	为解决这个问题，就需要引入互斥变量，让每个线程都按顺序地访问变量。*/
	InitializeCriticalSection(&g_cs);//初始化临界区 
	EnterCriticalSection(&g_cs);
	//内部对数据进行操控
	LeaveCriticalSection(&g_cs);
	DeleteCriticalSection(&g_cs);

// 	testPoint();
// 	testPoint2();
// 	teststring();

	double i1 = 0.22;
	int i2 = (int)(float)i1;
	i2 = (float)(int)i1;
	testconst();
	testbooble();

	//testStr();
	//testStr2();
// 	testPython4();
// 	testPython2();
// 	testPython();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CTestLibDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//加载背景图
		CPaintDC dc(this);
		CRect rect = { 0 };
		GetClientRect(&rect);   //获取客户区大小
		Graphics g(dc);
		g.DrawImage(m_img, 0, 0, rect.Width(), rect.Height());

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestLibDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD CTestLibDemoDlg:: TestThreadProc(LPVOID pParam)
{
	CTestLibDemoDlg *pDlg = (CTestLibDemoDlg *)pParam;
	return pDlg->TestThreadContent(pParam);
}

DWORD CTestLibDemoDlg::TestThreadContent(LPVOID pParam)
{
	while (FALSE == g_bExit)
	{
		DWORD dwResult = WaitForSingleObject(hTestEvent, INFINITE); //等待一个进程结束
		//DWORD dwResult = WaitForSingleObject(hTestEvent, 5000); //等待5秒，无论收到与否，都进入WAIT_TIMEOUT
		switch (dwResult)
		{
		case WAIT_OBJECT_0:
			// hProcess所代表的进程在5秒内结束
			AfxMessageBox("2");
			break;

		case WAIT_TIMEOUT:
			// 等待时间超过5秒
			AfxMessageBox("1");
			break;

		case WAIT_FAILED:
			// 函数调用失败，比如传递了一个无效的句柄,
			//hTestEvent 被赋值为null,然后setEvent(hTestEvent),触发WaitForSingleObject,会进入WAIT_FAILED
			AfxMessageBox("3");
			break;
		}
		ResetEvent(hTestEvent);
	}
	return TRUE;
}

DWORD CTestLibDemoDlg::TestMultipleThreadProc(LPVOID pParam)
{
	CTestLibDemoDlg *pDlg = (CTestLibDemoDlg *)pParam;
	return pDlg->TestMultipleThreadContent(pParam);
}

DWORD CTestLibDemoDlg::TestMultipleThreadContent(LPVOID pParam)
{
	DWORD dw = WaitForMultipleObjects(3, hThreadEvent, FALSE, INFINITE); //等待3个进程结束

	switch (dw)
	{
	case WAIT_FAILED:
		// 函数呼叫失败
		break;

	case WAIT_TIMEOUT:
		// 超时
		break;

	case WAIT_OBJECT_0 + 0:
		// h[0]（hProcess1）所代表的进程结束
		AfxMessageBox("t1");
		break;

	case WAIT_OBJECT_0 + 1:
		// h[1]（hProcess2）所代表的进程结束
		AfxMessageBox("t2");
		break;

	case WAIT_OBJECT_0 + 2:
		// h[2]（hProcess3）所代表的进程结束
		AfxMessageBox("t3");

		break;
	}
	return TRUE;
}

DWORD CTestLibDemoDlg::TestThreadProc2(LPVOID pParam)
{
	ThreadInfo *pDlg = (ThreadInfo *)pParam;
	return pDlg->pThis->TestThreadContent2(pParam);
}

DWORD CTestLibDemoDlg::TestThreadContent2(LPVOID pParam)
{
	ThreadInfo*pthInfo = (ThreadInfo*)pParam;

	while (FALSE == g_bExit)
	{
		DWORD dwResult = WaitForSingleObject(pthInfo->hEvent, INFINITE); //等待一个进程结束
																	//DWORD dwResult = WaitForSingleObject(hTestEvent, 5000); //等待5秒，无论收到与否，都进入WAIT_TIMEOUT
		switch (dwResult)
		{
		case WAIT_OBJECT_0:
			// hProcess所代表的进程在5秒内结束
			//AfxMessageBox("2");
			break;

		case WAIT_TIMEOUT:
			// 等待时间超过5秒
			AfxMessageBox("1");
			break;

		case WAIT_FAILED:
			// 函数调用失败，比如传递了一个无效的句柄,
			//hTestEvent 被赋值为null,然后setEvent(hTestEvent),触发WaitForSingleObject,会进入WAIT_FAILED
			AfxMessageBox("3");
			break;
		}
		ResetEvent(hTestEvent);
	}
	return TRUE;
}

void CTestLibDemoDlg::WriteStartBat1(CString strLoad)
{
	vector<CString>vecLoad = SplitString(strLoad, "|");

	int iSleepTime = GetIntgFromCfg("CONFIG", "SleepTime");
	CString strTemp = "";//cd /d E:\SVN\develop\example\AI语音\科大讯飞\ASR\bin
	CString strDisk = getFullPath("").Left(1);

	FILE * fp = fopen(getFullPath("start.bat"), "wb");
	strTemp.Format("cd /d %s", getFullPath("..\\"));
	fwrite(strTemp.GetBuffer(0), sizeof(char), strTemp.GetLength(), fp);
	fwrite("\r\n", 1, 2, fp);
	for (int i = 0; i < vecLoad.size(); i++)
	{
		strTemp.Format("start %s", getFullPath("..\\") + vecLoad[i]);
		fwrite(strTemp.GetBuffer(0), sizeof(char), strTemp.GetLength(), fp);
		fwrite("\r\n", 1, 2, fp);
		if (i + 1 == vecLoad.size())continue;
		strTemp.Format("ping 127.0.0.1 -n %d > nul", iSleepTime);
		fwrite(strTemp.GetBuffer(0), sizeof(char), strTemp.GetLength(), fp);
		fwrite("\r\n", 1, 2, fp);
	}

	fclose(fp);

}

//一直在检测有没有颜色发生变化
HBRUSH CTestLibDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC1)
	{
		if (m_bRed)
		{
			pDC->SetTextColor(RGB(255, 0, 0));
		}
		else if (m_bBlue)
		{
			pDC->SetTextColor(RGB(0, 0, 255));
		}
		else if (m_bGreen)
		{
			pDC->SetTextColor(RGB(0, 255, 0));
		}
	}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CTestLibDemoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	m_static1 = "连接成功";
	m_bRed = FALSE;
	m_bBlue = FALSE;
	m_bGreen = TRUE;

	UpdateData(FALSE);
}

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
	for (int i=0;i<str1.length();i++)
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

void testPython()
{
	//***python调用***//
	Py_SetPythonHome(L"E:\\software\\Anaconda3");
	//初始化python模块
	Py_Initialize();
	// 检查初始化是否成功  
	if (!Py_IsInitialized())
	{
		cout << "初始化失败" << endl;
		Py_Finalize();
	}

	PyObject *pModule;
	PyObject*pFunc = NULL;
	PyObject*pArg = NULL;
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");//设置python模块，搜寻位置，文件放在.cpp文件一起

	//使用PyObject* pModule来存储导入的.py文件模块, 
	pModule = PyImport_ImportModule("tt1");//Python文件名  加载文件     
	if (!pModule) {
		cout << "py文件导入失败" << endl;
		Py_Finalize();
	}
	else {
		pFunc = PyObject_GetAttrString(pModule, "run");//Python文件中的函数名  
		if (!pFunc) {
			cout << "函数导入失败" << endl;
			Py_Finalize();
		}

		PyObject* pyParams = Py_BuildValue("(s)", "helllo world!");//c++类型转python类型

		char * result1;
		pArg = PyEval_CallObject(pFunc, pyParams);//调用函数
		PyArg_Parse(pArg, "s", &result1);//python类型转c++类型
		cout << result1 << endl;
	}
}

void testPython2()
{
	Py_SetPythonHome(L"E:\\software\\Anaconda3");

	Py_Initialize(); // 初始化python虚拟机
	PyObject* pyMod = PyImport_ImportModule("test4"); //  加载test.py文件
	//使用PyObject* pDict来存储导入模块中的方法字典
	PyObject* pyDict = PyModule_GetDict(pyMod); //  获取test模块中的字典
	PyObject* pyCls = PyDict_GetItemString(pyDict, "tester"); // 从字典中查找tester类
	//PyObject* PyIns = PyInstance_New(pyCls, NULL, NULL); // 创建tester类
	PyObject* pConstruct = PyInstanceMethod_New(pyCls);
	PyObject* pIns = PyObject_CallObject(pConstruct, nullptr);
	PyObject* pyRet = PyObject_CallMethod(pIns, "add", "ii", 5, 6); // 调用tester.add方法，传入2个int型参数
	int ok = -1;
	int retok = PyArg_Parse(pyRet, "i", &ok); // 从返回值从取出int型返回值
	Py_Finalize();
}

int testPython3()
{
	Py_Initialize();//使用python之前，要调用Py_Initialize();这个函数进行初始化
	if (!Py_IsInitialized())
	{
		printf("初始化失败！");
		return 0;
	}

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");//这一步很重要，修改Python路径


	PyObject * pModule = NULL;//声明变量
	PyObject * pFunc1 = NULL;// 声明变量
	PyObject * pFunc2 = NULL;// 声明变量
	PyObject * pFunc3 = NULL;// 声明变量
	pModule = PyImport_ImportModule("mytest");//这里是要调用的文件名hello.py
	if (pModule == NULL)
	{
		cout << "没找到" << endl;
	}
	//1
	pFunc1 = PyObject_GetAttrString(pModule, "zip_file");//这里是要调用的函数名
	PyEval_CallObject(pFunc1, NULL);//调用无参数无返回值的python函数

	//2
	pFunc2 = PyObject_GetAttrString(pModule, "zip_file");//这里是要调用的函数名
	string readpath = R"(C:\Users\admin\Desktop\TestData)";
	string writepath = R"(C:\Users\admin\Desktop\TestData.zip)";
	PyObject* args = Py_BuildValue("ss", readpath.c_str(), writepath.c_str());//给python函数参数赋值

	PyObject_CallObject(pFunc2, args);//调用函数
	//3
	pFunc3 = PyObject_GetAttrString(pModule, "_getValue");//这里是要调用的函数名
	PyObject* args2 = Py_BuildValue("ii", 28, 103);//给python函数参数赋值

	PyObject* pRet = PyObject_CallObject(pFunc3, args2);//调用函数
	int res = 0;
	PyArg_Parse(pRet, "i", &res);//转换返回类型

	cout << "res:" << res << endl;//输出结果

	Py_Finalize(); // 与初始化对应
	system("pause");
	return 0;


}

int testPython4()
{
	Py_SetPythonHome(L"E:\\software\\Anaconda3");
	Py_Initialize();//使用python之前，要调用Py_Initialize();这个函数进行初始化
	if (!Py_IsInitialized())
	{
		AfxMessageBox("初始化失败！");
		return 0;
	}
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");//这一步很重要，修改Python路径


	PyObject * pModule = NULL;//声明变量
	PyObject * pFunc = NULL;// 声明变量
	pModule = PyImport_ImportModule("hello");//这里是要调用的文件名hello.py
	if (pModule == NULL)
	{
		AfxMessageBox("没找到！");
	}
	pFunc = PyObject_GetAttrString(pModule, "add_num");//这里是要调用的函数名
	if (!pFunc || !PyCallable_Check(pFunc))  // 验证是否加载成功
	{
		AfxMessageBox("[ERROR] Can't find funftion (add_num)");
		return 0;
	}
	//给python函数参数赋值
	/******************方式1***********************/
	PyObject* args = Py_BuildValue("(ii)", 28, 103);

	/******************方式2***********************/
	// 	PyObject *pArgs = PyTuple_New(2);//函数调用的参数传递均是以元组的形式打包的,2表示参数个数
	// 	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 2));
	// 	PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 4));

	PyObject* pRet = PyEval_CallObject(pFunc, args);//调用函数

	int res = 0;
	PyArg_Parse(pRet, "i", &res);//转换返回类型

	cout << "res:" << res << endl;//输出结果
	Py_Finalize();//调用Py_Finalize，这个根Py_Initialize相对应的。

}


void CTestLibDemoDlg ::testShellExecute()
{
/*
 hWnd:

	用于指定父窗口的句柄。当函数调用过程中出现错误时，它将作为Windows消息窗口的父窗口。
	hWnd,可以设为NULL

lpOperation：

	用于指定要进行的操作，当参数为NULL时，默认操作"open"。
	"open"，表示执行由lpFile参数指定的程序，或者打开由lpFile参数指定的文件或文件夹。
	"explort"，表示打开由lpFile参数指定的文件夹。
	"print",表示打印由lpFile参数指定的文件。

lpParameters：

	若lpFile参数是一个可执行文件，则此参数指定命令行参数，否则此参数应设为NULL。

lpDirectory：

	用于指定默认目录。

nShowCmd：

	用于指定程序窗口初始显示方式。
*/
//#define SW_HIDE             0		 /*隐藏窗体，并激活另一个窗体*/
//#define SW_SHOWNORMAL       1		 /*与SW_RESTORE相同*/
//#define SW_SHOWMINIMIZED    2		 /*激活并以最小化的形式显示窗体*/
//#define SW_SHOWMAXIMIZED    3		 /*激活并以最大化的形式显示窗体*/
//#define SW_MAXIMIZE         3		 /*最大化指定的窗体*/
//#define SW_SHOWNOACTIVATE   4        /*以上次的状态显示指定的窗体，但不激活它*/
//#define SW_SHOW             5		 /*激活窗体，并将其显示在当前的大小和位置上*/
//#define SW_MINIMIZE         6		 /*最小化指定的窗体，并激活另一个窗体*/
//#define SW_SHOWMINNOACTIVE  7		 /*以最小化形式显示指定的窗体，但不激活它*/
//#define SW_SHOWNA           8		 /*以当前的状态显示指定的窗体，但不激活它*/
//#define SW_RESTORE          9		 /*以原本的大小和位置，激活并显示指定的窗体*/
//#define SW_SHOWDEFAULT      10		 /*设置显示的状态由STARTUPINFO结构体指定*/

	//1 打开计算器

	ShellExecute(this->m_hWnd, "open", "calc.exe", NULL, NULL, SW_SHOWMAXIMIZED);
	//2 打开一个指定的程序

	ShellExecute(this->m_hWnd, "open", "E:\\软件\\notepad\\Notepad++\\notpad++.exe", NULL, NULL, SW_SHOWMAXIMIZED);
	ShellExecute(this->m_hWnd, "open", "notpad++.exe", NULL, "E:\\软件\\notepad\\Notepad++\\", SW_SHOWMAXIMIZED);
	ShellExecute(this->m_hWnd, "open", "notpad++.exe", NULL, "E:\\软件\\notepad\\Notepad++", SW_SHOWMAXIMIZED);
	//3 打开一个 URL
	ShellExecute(this->m_hWnd, "open", "http://tmxk.org/2012/", NULL, NULL, SW_SHOWMAXIMIZED);
	//hWnd,可以设为NULL
	ShellExecute(NULL, _T("open"), _T("chrome.exe"),_T("http://tmxk.org/2012/"), NULL, SW_MINIMIZE);

}

void testbooble()
{
	int a[] = {5,4,3,1,2};
	int len = sizeof(a) / sizeof(int);
	for (int i =0;i<len -1;i++)
	{
		for (int j=0;j<len-1-i;j++)
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

	int c[] = { 6,4,7,5,1,3,2};
	//int c[] = { 1,3,5,2,4,6,7 };
	int len3 = sizeof(c) / sizeof(int) ;
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

void testConst()
{
	const int *a1 = 0;
	const int b1 = 1;
	int c1 = 2;
	int *d1;
	int e = 3;
	a1 = &b1;	//  额外：注意不能通过a 来修改 b值 、const 对象的地址只能赋值给指向const 对象的指针
	//c1 = &b1;	//const 对象的地址 只能赋值给 指向const对象的指针
	a1 =&e;		//非const对象能调用const成员函数
	a1 = &c1;	//  额外：虽然c本身不是一个常量
	//*a1 = 2;	//error 为题就在这里，不能修改通过 *a 所指向的对象值，最后赋值得对象是c，因此不能通过*a 来修改c值。

}

 void CTestLibDemoDlg:: testconst()const
{
	//valueAA = 1; 函数末尾加了const 就无法对成员变量做修改了。
	 //testShellExecute();//无法调用非const 修饰的成员函数。
	 testconst2();
	// m_bRed = 1;//无法调用非const 修饰的成员变量。

	 int a = 0;
	 int &a1 = a;
	 a1 = 1;

	 const int &a2 = a;
	// r1 = 2;//const修饰过的,r1不可以修改
	 a = 2;

	 int const b = 1;
	 //int &b1 = b;// 非const，不可以绑定被const修饰过的

	 int const &b2 = b;
	 //b = 2; // const修饰过的,不可以改
	 //b2 = 2;// const修饰过的,不可以改

	 // int &b3 = 5;//非const，不能绑定常量
	 int const &b4 = 5;


}

 void CTestLibDemoDlg::testconst2()const
 {

 }

 void CTestLibDemoDlg::teststring()
 {
	 std::string stra = "123";
	 int isize = stra.size();
	 int ilen = stra.length();//size()与length()完全等同，遇到空字符不会被截断，可以返回字符串真实长度
	 stra.append("4");
	 int pos = stra.find("3");
	 stra.replace(pos,4, "");//从位置pos开始，之后的4个字符替换为空，即删除
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

	 const char *names[MAX] = { "Zara Ali", "Hina Ali", "Nuha Ali"};//是指针数组,本质是存储指针的数组,

// 	 int *ptr[3];
// 	 //由于 C++ 运算符的优先级中，* 小于 []，所以 ptr 先和 [] 结合成为数组，然后再和 int * 结合形成数组的元素类型是 int * 类型，
// 	 //得到一个叫一个数组的元素是指针，简称指针数组。
// 	 int *(ptr[3]);//指针数组
// 
// 	 int(*ptr)[3];//优先级顺序是 * 小于 ()，() 等于 []，() 和 [] 的优先级一样，但是结合顺序是从左到右，所以先是 () 里的 * 和 ptr 结合成为一个指针，
	 //然后是 (*ptr) 和 [] 相结合成为一个数组，最后叫一个指针 ptr 指向一个数组，简称数组指针。
 }
