
// TestLibDemoDlg.cpp : ʵ���ļ�
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

// CTestLibDemoDlg �Ի���
BOOL g_bExit = FALSE;
ThreadInfo g_pthInfo;

void 	testPoint();
void	testPoint2();
CTestLibDemoDlg::CTestLibDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTLIBDEMO_DIALOG, pParent)
	, m_static1(_T(""))
{
	hTest = NULL;
	
	/*	1 null // SECURITY_ATTRIBUTES�ṹָ�룬��ΪNULL | 4 null //�¼�������
	2 manual �ֶ� manualReset �ֶ���λ 
	3 initStatus ��λ״̬Ϊ�٣����� */
	hTestEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	hThread[3] = NULL;
	for (int i=0;i<3;i++)
	{
		hThreadEvent[i] = CreateEvent(NULL, FALSE, FALSE, NULL);//���ó��Ը�λ���ͣ������ƺ����������
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

// CTestLibDemoDlg ��Ϣ�������
#include "mylog.hpp"
#include "LogConfig.h"
#include "LogProvider.h"
#include "LogUserConfig.h"
BOOL CTestLibDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

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
	//1 ���߳�
	//����thisָ�룬this,����ص����� TestThreadProc
	hTest = CreateThread(NULL, 0, TestThreadProc, this, 0, &dwThreadId);
	//2 ���߳�
	for (int i = 0; i < 3; i++)
	{
		hThread[i] = CreateThread(NULL, 0, TestMultipleThreadProc, this, 0, &dwThreadId);
	}
	//3 ���߳� ���θı�
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
		m_static1 Ϊstatic��ֵ��bRed��ʼ����ԭ������Ϊ�����switch��
		�ǰ�˳�����ģ��Ҳ���ʼ����debugӦ����true״̬
		OnCtlColor �ڹ�����ܵ��Ӵ��ڱ��ػ�ʱ�����øó�Ա����
		����nCtlColor����ָ���ؼ�������,������:
		.CTLCOLOR_BTN                ��ť�ؼ�
		.CTLCOLOR_DLG                �Ի���
		.CTLCOLOR_EDIT               �༭��
		.CTLCOLOR_LISTBOX            �б�ؼ�
		.CTLCOLOR_MSGBOX             ��Ϣ�ؼ�
		.CTLCOLOR_SCROLLBAR �������ؼ�
		.CTLCOLOR_STATIC             ��̬�ؼ�
	*/
	m_bRed = FALSE;
	m_bGreen = FALSE;
	m_bBlue = TRUE;;
	m_static1 = "��㣡����";
	UpdateData(FALSE);

	//��ͼ
	Gdiplus::GdiplusStartup(&m_uGdiplusToken, &m_GdiplusStarupInput, nullptr);

	CString sss = getFullPath("2.jpg");//bmp��
	CStringW s(sss);   //תΪ���ַ�
	m_img = Image::FromFile(s);  //����ͼƬ

	//���̶߳����ݵĲٿ�
	/*����̲߳�����ͬ������ʱ��һ������Ҫ��˳����ʵģ�������������ݴ��ң��޷��������ݣ�������������
	Ϊ���������⣬����Ҫ���뻥���������ÿ���̶߳���˳��ط��ʱ�����*/
	InitializeCriticalSection(&g_cs);//��ʼ���ٽ��� 
	EnterCriticalSection(&g_cs);
	//�ڲ������ݽ��вٿ�
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void CTestLibDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//���ر���ͼ
		CPaintDC dc(this);
		CRect rect = { 0 };
		GetClientRect(&rect);   //��ȡ�ͻ�����С
		Graphics g(dc);
		g.DrawImage(m_img, 0, 0, rect.Width(), rect.Height());

		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
		DWORD dwResult = WaitForSingleObject(hTestEvent, INFINITE); //�ȴ�һ�����̽���
		//DWORD dwResult = WaitForSingleObject(hTestEvent, 5000); //�ȴ�5�룬�����յ���񣬶�����WAIT_TIMEOUT
		switch (dwResult)
		{
		case WAIT_OBJECT_0:
			// hProcess������Ľ�����5���ڽ���
			AfxMessageBox("2");
			break;

		case WAIT_TIMEOUT:
			// �ȴ�ʱ�䳬��5��
			AfxMessageBox("1");
			break;

		case WAIT_FAILED:
			// ��������ʧ�ܣ����紫����һ����Ч�ľ��,
			//hTestEvent ����ֵΪnull,Ȼ��setEvent(hTestEvent),����WaitForSingleObject,�����WAIT_FAILED
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
	DWORD dw = WaitForMultipleObjects(3, hThreadEvent, FALSE, INFINITE); //�ȴ�3�����̽���

	switch (dw)
	{
	case WAIT_FAILED:
		// ��������ʧ��
		break;

	case WAIT_TIMEOUT:
		// ��ʱ
		break;

	case WAIT_OBJECT_0 + 0:
		// h[0]��hProcess1��������Ľ��̽���
		AfxMessageBox("t1");
		break;

	case WAIT_OBJECT_0 + 1:
		// h[1]��hProcess2��������Ľ��̽���
		AfxMessageBox("t2");
		break;

	case WAIT_OBJECT_0 + 2:
		// h[2]��hProcess3��������Ľ��̽���
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
		DWORD dwResult = WaitForSingleObject(pthInfo->hEvent, INFINITE); //�ȴ�һ�����̽���
																	//DWORD dwResult = WaitForSingleObject(hTestEvent, 5000); //�ȴ�5�룬�����յ���񣬶�����WAIT_TIMEOUT
		switch (dwResult)
		{
		case WAIT_OBJECT_0:
			// hProcess������Ľ�����5���ڽ���
			//AfxMessageBox("2");
			break;

		case WAIT_TIMEOUT:
			// �ȴ�ʱ�䳬��5��
			AfxMessageBox("1");
			break;

		case WAIT_FAILED:
			// ��������ʧ�ܣ����紫����һ����Ч�ľ��,
			//hTestEvent ����ֵΪnull,Ȼ��setEvent(hTestEvent),����WaitForSingleObject,�����WAIT_FAILED
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
	CString strTemp = "";//cd /d E:\SVN\develop\example\AI����\�ƴ�Ѷ��\ASR\bin
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

//һֱ�ڼ����û����ɫ�����仯
HBRUSH CTestLibDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
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


	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CTestLibDemoDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	m_static1 = "���ӳɹ�";
	m_bRed = FALSE;
	m_bBlue = FALSE;
	m_bGreen = TRUE;

	UpdateData(FALSE);
}

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
	for (int i=0;i<str1.length();i++)
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

void testPython()
{
	//***python����***//
	Py_SetPythonHome(L"E:\\software\\Anaconda3");
	//��ʼ��pythonģ��
	Py_Initialize();
	// ����ʼ���Ƿ�ɹ�  
	if (!Py_IsInitialized())
	{
		cout << "��ʼ��ʧ��" << endl;
		Py_Finalize();
	}

	PyObject *pModule;
	PyObject*pFunc = NULL;
	PyObject*pArg = NULL;
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");//����pythonģ�飬��Ѱλ�ã��ļ�����.cpp�ļ�һ��

	//ʹ��PyObject* pModule���洢�����.py�ļ�ģ��, 
	pModule = PyImport_ImportModule("tt1");//Python�ļ���  �����ļ�     
	if (!pModule) {
		cout << "py�ļ�����ʧ��" << endl;
		Py_Finalize();
	}
	else {
		pFunc = PyObject_GetAttrString(pModule, "run");//Python�ļ��еĺ�����  
		if (!pFunc) {
			cout << "��������ʧ��" << endl;
			Py_Finalize();
		}

		PyObject* pyParams = Py_BuildValue("(s)", "helllo world!");//c++����תpython����

		char * result1;
		pArg = PyEval_CallObject(pFunc, pyParams);//���ú���
		PyArg_Parse(pArg, "s", &result1);//python����תc++����
		cout << result1 << endl;
	}
}

void testPython2()
{
	Py_SetPythonHome(L"E:\\software\\Anaconda3");

	Py_Initialize(); // ��ʼ��python�����
	PyObject* pyMod = PyImport_ImportModule("test4"); //  ����test.py�ļ�
	//ʹ��PyObject* pDict���洢����ģ���еķ����ֵ�
	PyObject* pyDict = PyModule_GetDict(pyMod); //  ��ȡtestģ���е��ֵ�
	PyObject* pyCls = PyDict_GetItemString(pyDict, "tester"); // ���ֵ��в���tester��
	//PyObject* PyIns = PyInstance_New(pyCls, NULL, NULL); // ����tester��
	PyObject* pConstruct = PyInstanceMethod_New(pyCls);
	PyObject* pIns = PyObject_CallObject(pConstruct, nullptr);
	PyObject* pyRet = PyObject_CallMethod(pIns, "add", "ii", 5, 6); // ����tester.add����������2��int�Ͳ���
	int ok = -1;
	int retok = PyArg_Parse(pyRet, "i", &ok); // �ӷ���ֵ��ȡ��int�ͷ���ֵ
	Py_Finalize();
}

int testPython3()
{
	Py_Initialize();//ʹ��python֮ǰ��Ҫ����Py_Initialize();����������г�ʼ��
	if (!Py_IsInitialized())
	{
		printf("��ʼ��ʧ�ܣ�");
		return 0;
	}

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");//��һ������Ҫ���޸�Python·��


	PyObject * pModule = NULL;//��������
	PyObject * pFunc1 = NULL;// ��������
	PyObject * pFunc2 = NULL;// ��������
	PyObject * pFunc3 = NULL;// ��������
	pModule = PyImport_ImportModule("mytest");//������Ҫ���õ��ļ���hello.py
	if (pModule == NULL)
	{
		cout << "û�ҵ�" << endl;
	}
	//1
	pFunc1 = PyObject_GetAttrString(pModule, "zip_file");//������Ҫ���õĺ�����
	PyEval_CallObject(pFunc1, NULL);//�����޲����޷���ֵ��python����

	//2
	pFunc2 = PyObject_GetAttrString(pModule, "zip_file");//������Ҫ���õĺ�����
	string readpath = R"(C:\Users\admin\Desktop\TestData)";
	string writepath = R"(C:\Users\admin\Desktop\TestData.zip)";
	PyObject* args = Py_BuildValue("ss", readpath.c_str(), writepath.c_str());//��python����������ֵ

	PyObject_CallObject(pFunc2, args);//���ú���
	//3
	pFunc3 = PyObject_GetAttrString(pModule, "_getValue");//������Ҫ���õĺ�����
	PyObject* args2 = Py_BuildValue("ii", 28, 103);//��python����������ֵ

	PyObject* pRet = PyObject_CallObject(pFunc3, args2);//���ú���
	int res = 0;
	PyArg_Parse(pRet, "i", &res);//ת����������

	cout << "res:" << res << endl;//������

	Py_Finalize(); // ���ʼ����Ӧ
	system("pause");
	return 0;


}

int testPython4()
{
	Py_SetPythonHome(L"E:\\software\\Anaconda3");
	Py_Initialize();//ʹ��python֮ǰ��Ҫ����Py_Initialize();����������г�ʼ��
	if (!Py_IsInitialized())
	{
		AfxMessageBox("��ʼ��ʧ�ܣ�");
		return 0;
	}
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('./')");//��һ������Ҫ���޸�Python·��


	PyObject * pModule = NULL;//��������
	PyObject * pFunc = NULL;// ��������
	pModule = PyImport_ImportModule("hello");//������Ҫ���õ��ļ���hello.py
	if (pModule == NULL)
	{
		AfxMessageBox("û�ҵ���");
	}
	pFunc = PyObject_GetAttrString(pModule, "add_num");//������Ҫ���õĺ�����
	if (!pFunc || !PyCallable_Check(pFunc))  // ��֤�Ƿ���سɹ�
	{
		AfxMessageBox("[ERROR] Can't find funftion (add_num)");
		return 0;
	}
	//��python����������ֵ
	/******************��ʽ1***********************/
	PyObject* args = Py_BuildValue("(ii)", 28, 103);

	/******************��ʽ2***********************/
	// 	PyObject *pArgs = PyTuple_New(2);//�������õĲ������ݾ�����Ԫ�����ʽ�����,2��ʾ��������
	// 	PyTuple_SetItem(pArgs, 0, Py_BuildValue("i", 2));
	// 	PyTuple_SetItem(pArgs, 1, Py_BuildValue("i", 4));

	PyObject* pRet = PyEval_CallObject(pFunc, args);//���ú���

	int res = 0;
	PyArg_Parse(pRet, "i", &res);//ת����������

	cout << "res:" << res << endl;//������
	Py_Finalize();//����Py_Finalize�������Py_Initialize���Ӧ�ġ�

}


void CTestLibDemoDlg ::testShellExecute()
{
/*
 hWnd:

	����ָ�������ڵľ�������������ù����г��ִ���ʱ��������ΪWindows��Ϣ���ڵĸ����ڡ�
	hWnd,������ΪNULL

lpOperation��

	����ָ��Ҫ���еĲ�����������ΪNULLʱ��Ĭ�ϲ���"open"��
	"open"����ʾִ����lpFile����ָ���ĳ��򣬻��ߴ���lpFile����ָ�����ļ����ļ��С�
	"explort"����ʾ����lpFile����ָ�����ļ��С�
	"print",��ʾ��ӡ��lpFile����ָ�����ļ���

lpParameters��

	��lpFile������һ����ִ���ļ�����˲���ָ�������в���������˲���Ӧ��ΪNULL��

lpDirectory��

	����ָ��Ĭ��Ŀ¼��

nShowCmd��

	����ָ�����򴰿ڳ�ʼ��ʾ��ʽ��
*/
//#define SW_HIDE             0		 /*���ش��壬��������һ������*/
//#define SW_SHOWNORMAL       1		 /*��SW_RESTORE��ͬ*/
//#define SW_SHOWMINIMIZED    2		 /*�������С������ʽ��ʾ����*/
//#define SW_SHOWMAXIMIZED    3		 /*�������󻯵���ʽ��ʾ����*/
//#define SW_MAXIMIZE         3		 /*���ָ���Ĵ���*/
//#define SW_SHOWNOACTIVATE   4        /*���ϴε�״̬��ʾָ���Ĵ��壬����������*/
//#define SW_SHOW             5		 /*����壬��������ʾ�ڵ�ǰ�Ĵ�С��λ����*/
//#define SW_MINIMIZE         6		 /*��С��ָ���Ĵ��壬��������һ������*/
//#define SW_SHOWMINNOACTIVE  7		 /*����С����ʽ��ʾָ���Ĵ��壬����������*/
//#define SW_SHOWNA           8		 /*�Ե�ǰ��״̬��ʾָ���Ĵ��壬����������*/
//#define SW_RESTORE          9		 /*��ԭ���Ĵ�С��λ�ã������ʾָ���Ĵ���*/
//#define SW_SHOWDEFAULT      10		 /*������ʾ��״̬��STARTUPINFO�ṹ��ָ��*/

	//1 �򿪼�����

	ShellExecute(this->m_hWnd, "open", "calc.exe", NULL, NULL, SW_SHOWMAXIMIZED);
	//2 ��һ��ָ���ĳ���

	ShellExecute(this->m_hWnd, "open", "E:\\���\\notepad\\Notepad++\\notpad++.exe", NULL, NULL, SW_SHOWMAXIMIZED);
	ShellExecute(this->m_hWnd, "open", "notpad++.exe", NULL, "E:\\���\\notepad\\Notepad++\\", SW_SHOWMAXIMIZED);
	ShellExecute(this->m_hWnd, "open", "notpad++.exe", NULL, "E:\\���\\notepad\\Notepad++", SW_SHOWMAXIMIZED);
	//3 ��һ�� URL
	ShellExecute(this->m_hWnd, "open", "http://tmxk.org/2012/", NULL, NULL, SW_SHOWMAXIMIZED);
	//hWnd,������ΪNULL
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

	int c[] = { 6,4,7,5,1,3,2};
	//int c[] = { 1,3,5,2,4,6,7 };
	int len3 = sizeof(c) / sizeof(int) ;
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

void testConst()
{
	const int *a1 = 0;
	const int b1 = 1;
	int c1 = 2;
	int *d1;
	int e = 3;
	a1 = &b1;	//  ���⣺ע�ⲻ��ͨ��a ���޸� bֵ ��const ����ĵ�ַֻ�ܸ�ֵ��ָ��const �����ָ��
	//c1 = &b1;	//const ����ĵ�ַ ֻ�ܸ�ֵ�� ָ��const�����ָ��
	a1 =&e;		//��const�����ܵ���const��Ա����
	a1 = &c1;	//  ���⣺��Ȼc������һ������
	//*a1 = 2;	//error Ϊ�������������޸�ͨ�� *a ��ָ��Ķ���ֵ�����ֵ�ö�����c����˲���ͨ��*a ���޸�cֵ��

}

 void CTestLibDemoDlg:: testconst()const
{
	//valueAA = 1; ����ĩβ����const ���޷��Գ�Ա�������޸��ˡ�
	 //testShellExecute();//�޷����÷�const ���εĳ�Ա������
	 testconst2();
	// m_bRed = 1;//�޷����÷�const ���εĳ�Ա������

	 int a = 0;
	 int &a1 = a;
	 a1 = 1;

	 const int &a2 = a;
	// r1 = 2;//const���ι���,r1�������޸�
	 a = 2;

	 int const b = 1;
	 //int &b1 = b;// ��const�������԰󶨱�const���ι���

	 int const &b2 = b;
	 //b = 2; // const���ι���,�����Ը�
	 //b2 = 2;// const���ι���,�����Ը�

	 // int &b3 = 5;//��const�����ܰ󶨳���
	 int const &b4 = 5;


}

 void CTestLibDemoDlg::testconst2()const
 {

 }

 void CTestLibDemoDlg::teststring()
 {
	 std::string stra = "123";
	 int isize = stra.size();
	 int ilen = stra.length();//size()��length()��ȫ��ͬ���������ַ����ᱻ�ضϣ����Է����ַ�����ʵ����
	 stra.append("4");
	 int pos = stra.find("3");
	 stra.replace(pos,4, "");//��λ��pos��ʼ��֮���4���ַ��滻Ϊ�գ���ɾ��
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

	 const char *names[MAX] = { "Zara Ali", "Hina Ali", "Nuha Ali"};//��ָ������,�����Ǵ洢ָ�������,

// 	 int *ptr[3];
// 	 //���� C++ ����������ȼ��У�* С�� []������ ptr �Ⱥ� [] ��ϳ�Ϊ���飬Ȼ���ٺ� int * ����γ������Ԫ�������� int * ���ͣ�
// 	 //�õ�һ����һ�������Ԫ����ָ�룬���ָ�����顣
// 	 int *(ptr[3]);//ָ������
// 
// 	 int(*ptr)[3];//���ȼ�˳���� * С�� ()��() ���� []��() �� [] �����ȼ�һ�������ǽ��˳���Ǵ����ң��������� () ��� * �� ptr ��ϳ�Ϊһ��ָ�룬
	 //Ȼ���� (*ptr) �� [] ���ϳ�Ϊһ�����飬����һ��ָ�� ptr ָ��һ�����飬�������ָ�롣
 }
