
// TestLibDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestLibDemo.h"
#include "TestLibDemoDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "MyLib.h"
#ifdef DEBUG
#pragma comment(lib,"MyLibd.lib")
#else
#pragma comment(lib,"MyLib.lib")
#endif // DEBUG

//#include <Python.h>
// #pragma comment(lib,"python3_d.lib")
// #pragma comment(lib,"python37_d.lib")

CRITICAL_SECTION g_cs;
 
#include  <direct.h>  
#pragma comment(lib,"URlmon")

BOOL g_bExit = FALSE;

#include<functional>
#include "stringTest.h"

#include "constTest.h"
#include "virtualclass.h"







CTestLibDemoDlg::CTestLibDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTLIBDEMO_DIALOG, pParent)
	, m_static1(_T(""))
{

	Gdiplus::GdiplusStartupInput m_GdiplusStarupInput;
	ULONG_PTR m_uGdiplusToken;

	m_hTest = NULL;
	m_hTestEvent = CreateEvent(NULL, TRUE, FALSE, NULL);


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

BOOL CTestLibDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码

	testVirtual();
	testConst();

	DWORD dwThreadId = 0;
	m_hTest = CreateThread(NULL, 0, TestThreadProc, this, 0, &dwThreadId);


	CString sttt = "{\"serialNo\":\"1100121\",\"channnelType\":\"001\",\"transCode\":\"300001\",\"instNO\":\"320123\",\"winNO\":\"1\",\"tellrCode\":\"1001\",\"reqNO\":\"X003\",\"realBusType\":\"cashService\",\"discard\":3}";
	int lne = strlen(sttt);

	testlambda();


// 	char buffer[MAX_PATH];
// 	_getcwd(buffer, MAX_PATH);
// 	strcat_s(buffer, "//1.jpg");
// 	HRESULT Result = URLDownloadToFileA(NULL, "url=/search/detail?ct=503316480&z=0&tn=baiduimagedetailnojs&ipn=dnj&&word=%E5%9B%BE%E7%89%87&cl=&lm=-1&pn=0&di=169950&ln=30&amp", buffer, 0, NULL);
	 string downurl = "http://www.anyuer.club";
	 string savepath = "D://abc.index";
	 download(downurl, savepath);


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

	double i1 = 0.22;
	int i2 = (int)(float)i1;
	i2 = (float)(int)i1;
	testbooble();

	SetEvent(m_hTestEvent);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
/***********************************************************************************************************************************************************/
/***********************************************************************************************************************************************************/
/***********************************************************************************************************************************************************/
void CTestLibDemoDlg::testConst()
{
	extern int testint;
	extern void getfun();
	int tt1 = testint;
	getfun();
	extern const int testint2;
	int tt2 = testint2;

	//说明const对象默认调用const成员函数。
	Apple a(2);
	int anum = a.getCount() ;
	a.add(10);
	const Apple b(3);
	b.add(10);

}

void CTestLibDemoDlg::testVirtual()
{
	//Base b;  // error! 不能创建抽象类的对象
	//Base *b = new Base(); //error!

	//如果担心类名重复，可以这样使用
	// virtualTest::Base * bp = new virtualTest::Derived(1,2);
	Base * bp2 = new Derived(2, 3);
	bp2->fun();// 抽象类的指针和引用 -> 由抽象类派生出来的类的对象

	Base1*bp3 = new Derived1();
	bp3->func();


}

void CTestLibDemoDlg::testPC()
{
	CString strIp = CheckIP();
	CString strMac1 = GetMacAddress(2);
	char b[1024];
	char c[1024];
	ObtainCPUID(b);
	ObtainHDID(c);

}



/***********************************************************************************************************************************************************/
/***********************************************************************************************************************************************************/
/***********************************************************************************************************************************************************/


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


DWORD CTestLibDemoDlg::TestThreadProc(LPVOID pParam)
{
	CTestLibDemoDlg* pDlg = (CTestLibDemoDlg*)pParam;
	return pDlg->TestThreadContent(pParam);
}

DWORD CTestLibDemoDlg::TestThreadContent(LPVOID pParam)
{
	int iCount = 0;
	while (1)
	{
		DWORD dwResult = WaitForSingleObject(m_hTestEvent, INFINITE);
		//if (TRUE == 1) return TRUE;
		if (dwResult == WAIT_OBJECT_0)
		{
			char *a = new char[5];
			strcpy(a ,"1");
			delete a;
// 			delete a;
		}
		ResetEvent(m_hTestEvent);
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



void CTestLibDemoDlg::testShellExecute()
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
	ShellExecute(NULL, _T("open"), _T("chrome.exe"), _T("http://tmxk.org/2012/"), NULL, SW_MINIMIZE);

}


 template <typename F>
 void Myprint(F const &f) {
	 std::cout << f() << std::endl;
 }

 void testlambda()
 {
	 // 定义简单的lambda表达式
	 auto basicLambda = [] { cout << "Hello, world!" << endl; };
	 // 调用
	 basicLambda();   // 输出：Hello, world!
 
	 auto addfun = [&](int a, int b) {return a + b; };
	 addfun(1, 2);

	 int x = 10;
	 auto mulitiple_x = [&x](int a) mutable{x *= 2; return a*x; };
	 cout << "x=%d" << x << endl;

// 	 IsJsonData( [&](const CString &str) {
// 		 return str;
// 	 });
 }

