
// TestLibDemoDlg.cpp : ʵ���ļ�
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

// CTestLibDemoDlg ��Ϣ�������

BOOL CTestLibDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

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

	double i1 = 0.22;
	int i2 = (int)(float)i1;
	i2 = (float)(int)i1;
	testbooble();

	SetEvent(m_hTestEvent);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

	//˵��const����Ĭ�ϵ���const��Ա������
	Apple a(2);
	int anum = a.getCount() ;
	a.add(10);
	const Apple b(3);
	b.add(10);

}

void CTestLibDemoDlg::testVirtual()
{
	//Base b;  // error! ���ܴ���������Ķ���
	//Base *b = new Base(); //error!

	//������������ظ�����������ʹ��
	// virtualTest::Base * bp = new virtualTest::Derived(1,2);
	Base * bp2 = new Derived(2, 3);
	bp2->fun();// �������ָ������� -> �ɳ�����������������Ķ���

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



void CTestLibDemoDlg::testShellExecute()
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
	ShellExecute(NULL, _T("open"), _T("chrome.exe"), _T("http://tmxk.org/2012/"), NULL, SW_MINIMIZE);

}


 template <typename F>
 void Myprint(F const &f) {
	 std::cout << f() << std::endl;
 }

 void testlambda()
 {
	 // ����򵥵�lambda���ʽ
	 auto basicLambda = [] { cout << "Hello, world!" << endl; };
	 // ����
	 basicLambda();   // �����Hello, world!
 
	 auto addfun = [&](int a, int b) {return a + b; };
	 addfun(1, 2);

	 int x = 10;
	 auto mulitiple_x = [&x](int a) mutable{x *= 2; return a*x; };
	 cout << "x=%d" << x << endl;

// 	 IsJsonData( [&](const CString &str) {
// 		 return str;
// 	 });
 }

