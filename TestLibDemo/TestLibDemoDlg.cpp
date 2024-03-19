
// TestLibDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestLibDemo.h"
#include "TestLibDemoDlg.h"
#include "afxdialogex.h"

#include "mystring.h"
#include "myos.h"
#include "mylog.h"
using namespace my_logger;

#include<functional>
#include "stringTest.h"
#include "constTest.h"
#include "virtualclass.h"
#include "sort.h"
#include "TestRegex.h"

#define TIMER_TEST 1001

BOOL g_bExit = FALSE;


CRITICAL_SECTION g_cs;
 
#include  <direct.h>  
#pragma comment(lib,"URlmon")


/*******************************************************/
#include "opencv2/opencv.hpp"
#include "opencv/cv.h"
#include "opencv/highgui.h"
using namespace cv;
//压缩视频，转成AVI
//int  testVideo()
//{
//	VideoCapture capture("D:\\1.mp4");//获取视频，根据自己的视频位置更改
//	if (!capture.isOpened())
//		return -1;
//
//	capture.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
//	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
//	//VideoWriter(const String & filename, int fourcc, double fps,Size frameSize, bool isColor = true);
//
//	//改变图像的帧速为30，图像帧的大小是（640，480）
//	VideoWriter videowriter("D:\\2.avi",/*VideoWriter::fourcc('M', 'J', 'P', 'G')*/CV_FOURCC('M', 'J', 'P', 'G'), 30, cv::Size(1920, 1080), true);
//
//	Mat image;
//	while (capture.read(image))
//	{
//		resize(image, image, cv::Size(1920,1080), INTER_LINEAR);
//		videowriter.write(image);
//	}
//	capture.release();
//	videowriter.release();
//	waitKey(0);
//	return 0;
//}
/*******************************************************/
// 
// #include <iostream>
// using namespace std;
// 
// #define __STDC_CONSTANT_MACROS
// // 
// extern "C"
// {
// #include "libavcodec/avcodec.h"
// #include "libavformat/avformat.h"
// #include "libswscale/swscale.h"
// #include "libavdevice/avdevice.h"
// };
// #pragma comment(lib,"avformat.lib")
// #pragma comment(lib,"avutil.lib")
// #pragma comment(lib,"avcodec.lib")
// #pragma comment(lib,"swscale.lib")
// 
// 
// 
// void ChangeType()
// {
// 	AVOutputFormat *ofmt = NULL;
// 	//Input AVFormatContext and Output AVFormatContext
// 	AVFormatContext *ifmt_ctx = NULL, *ofmt_ctx = NULL;
// 	AVPacket pkt;
// 	const char *in_filename, *out_filename;
// 	int ret, i;
// 	int frame_index = 0;
// 	in_filename = "ws.mp4";//Input file URL
// 	out_filename = "ws.avi";//Output file URL
// 
// 
// 
// 	av_register_all();
// 	//Input
// 	if ((ret = avformat_open_input(&ifmt_ctx, in_filename, 0, 0)) < 0) {//打开媒体文件
// 		printf("Could not open input file.");
// 		goto end;
// 	}
// 	if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0) {//获取视频信息
// 		printf("Failed to retrieve input stream information");
// 		goto end;
// 	}
// 	av_dump_format(ifmt_ctx, 0, in_filename, 0);
// 	//初始化输出视频码流的AVFormatContext。
// 	avformat_alloc_output_context2(&ofmt_ctx, NULL, NULL, out_filename);
// 	if (!ofmt_ctx) {
// 		printf("Could not create output context\n");
// 		ret = AVERROR_UNKNOWN;
// 		goto end;
// 	}
// 	ofmt = ofmt_ctx->oformat;
// 	for (i = 0; i < ifmt_ctx->nb_streams; i++) {
// 		//Create output AVStream according to input AVStream
// 		AVStream *in_stream = ifmt_ctx->streams[i];
// 		AVStream *out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);// 初始化AVStream 
// 		if (!out_stream) {
// 			printf("Failed allocating output stream\n");
// 			ret = AVERROR_UNKNOWN;
// 			goto end;
// 		}
// 		//关键：Copy the settings of AVCodecContext
// 		if (avcodec_copy_context(out_stream->codec, in_stream->codec) < 0) {
// 			printf("Failed to copy context from input to output stream codec context\n");
// 			goto end;
// 		}
// 		out_stream->codec->codec_tag = 0;
// 		if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
// 			out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
// 	}
// 	//Output information------------------
// 	av_dump_format(ofmt_ctx, 0, out_filename, 1);
// 	//Open output file
// 	if (!(ofmt->flags & AVFMT_NOFILE)) {
// 		ret = avio_open(&ofmt_ctx->pb, out_filename, AVIO_FLAG_WRITE);//打开输出文件。
// 		if (ret < 0) {
// 			printf("Could not open output file '%s'", out_filename);
// 			goto end;
// 		}
// 	}
// 	//Write file header
// 	if (avformat_write_header(ofmt_ctx, NULL) < 0) {
// 		printf("Error occurred when opening output file\n");
// 		goto end;
// 	}
// 
// 	while (1) {
// 		AVStream *in_stream, *out_stream;
// 		//Get an AVPacket
// 		ret = av_read_frame(ifmt_ctx, &pkt);
// 		if (ret < 0)
// 			break;
// 		in_stream = ifmt_ctx->streams[pkt.stream_index];
// 		out_stream = ofmt_ctx->streams[pkt.stream_index];
// 
// 		//Convert PTS/DTS
// 		pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
// 		pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
// 		pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
// 		pkt.pos = -1;
// 		//Write
// 		if (av_interleaved_write_frame(ofmt_ctx, &pkt) < 0) {//将AVPacket（存储视频压缩码流数据）写入文件
// 			printf("Error muxing packet\n");
// 			break;
// 		}
// 		printf("Write %8d frames to output file\n", frame_index);
// 		av_free_packet(&pkt);
// 		frame_index++;
// 	}
// 	//Write file trailer
// 	av_write_trailer(ofmt_ctx);
// end:
// 	avformat_close_input(&ifmt_ctx);
// 	/* close output */
// 	if (ofmt_ctx && !(ofmt->flags & AVFMT_NOFILE))
// 		avio_close(ofmt_ctx->pb);
// 	avformat_free_context(ofmt_ctx);
// 
// 	return ;
// }

/*******************************************************/


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
	ON_WM_TIMER()
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


	testC11();

	bool bret = CheckEmail("123@qq.com");
	bret = CheckEnAndNum("你好");
//	testVideo();

	ScreenShot();

	CString strmd516 = MD5Encrypt_16("123");

	testRelloc();

	//ChangeType();

	int iBTime = GetTickCount();
	DWORD g_dwTimeOut = 5;
	while (1)
	{
		//int istatus = START_PTR.GetStatusEnd();
		//当处于缺纸状态时，正好纸吐出来，这个时候通知填单机显示“打印完成”是最合适的。
		//if (istatus) break;
		int iBTime2 = GetTickCount();
		if ((iBTime2 - iBTime) >= DWORD(g_dwTimeOut))
		{
			break;
		}
		Sleep(100);
	}

	SetTimer(TIMER_TEST, 1000, NULL);



	testVirtual();
	testConst();

	DWORD dwThreadId = 0;
	m_hTest = CreateThread(NULL, 0, TestThreadProc, this, 0, &dwThreadId);


	CString sttt = "{\"serialNo\":\"1100121\",\"channnelType\":\"001\",\"transCode\":\"300001\",\"instNO\":\"320123\",\"winNO\":\"1\",\"tellrCode\":\"1001\",\"reqNO\":\"X003\",\"realBusType\":\"cashService\",\"discard\":3}";
	int lne = strlen(sttt);

	testlambda();


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

	delete bp3;
	/*
	调用顺序
	16:50:44.644 > info  | virtualclass.h[37] Constructor: Base
	16:50:44.644 > info  | virtualclass.h[49] Constructor: Derived1
	16:50:44.644 > info  | virtualclass.h[56] In Derived.func().
	16:50:45.645 > info  | virtualclass.h[52] Destructor: Derived1
	16:50:45.645 > info  | virtualclass.h[40] Destructor: Base
	*/


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

void testRelloc()
{
	int *p = (int*)calloc(5, sizeof(int));//申请5个空间
	assert(p);
	for (int i =0;i<10;i++)
	{
		if (i ==5)
		{
			p = (int*)realloc(p, sizeof(int) *10);//p的空间扩容到10个，并且p的实际地址变了
		}
		p[i] = i + 1;
	}
	free(p);
	p = NULL;

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
	auto mulitiple_x = [&x](int a) mutable {x *= 2; return a*x; };
	cout << "x=%d" << x << endl;

	// 	 IsJsonData( [&](const CString &str) {
	// 		 return str;
	// 	 });
}

void CTestLibDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString strTemporaryJsonPath = "";
	CRect largerect;

	KillTimer(nIDEvent);
	// GetDlgItem(IDC_BUTTON1)->SetWindowPos(NULL, 0, 0, 100, 80, SWP_NOZORDER | SWP_NOSIZE);

	CRect rectCtrl;
	CButton *p = (CButton*)GetDlgItem(IDC_BUTTON1);
	static int i = 100;
	p->MoveWindow(i--, 100, 100, 100);

	SetTimer(TIMER_TEST, 50, NULL);

	// 		 //第一种：
	// 		 GetWindowRect(&largerect);
	// 		 GetDlgItem(IDC_BUTTON1)->SetWindowPos(NULL, largerect.left + 10, largerect.top + 10, 0, 0,
	// 			 SWP_NOZORDER | SWP_NOSIZE);
	// 		 UpdateData(FALSE);
	// 		 Sleep(2000)
	// 		 SetTimer(TIMER_TEST, 2000, NULL);
	// CTestLibDemoDlg::OnTimer(nIDEvent);
}

//打开画图，并保存，存在一个问题，万一置顶不是它就麻烦了。
void MspaintSave(CString strFilePat)
{
	CString strPath = strFilePat;
	strPath.Replace("/", "\\");
	CString strEnd = ("\"") + strPath + ("\""); //加引号是为了避免路径有空格,因为cmd命令不认空格
	::ShellExecuteA(NULL, "open", "mspaint.exe", strEnd, NULL, SW_SHOWNORMAL); //只认'\\'路径
																			   //HWND hWin = ::FindWindow("画图(32位)", NULL);
	Sleep(5000);
	keybd_event(VK_CONTROL, 0, 0, 0);
	Sleep(50);
	keybd_event(83, 0, 0, 0);
	Sleep(2000);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);//抬起按键
	Sleep(50);
	keybd_event(83, 0, KEYEVENTF_KEYUP, 0);
	Sleep(2000);

	//KillProcess("mspaint.exe");
	Sleep(2000);
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

void testC11()
{
	auto a = 11;
	auto b = 1.2;



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

//一直在检测有没有颜色发生变化
HBRUSH CTestLibDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC1)
	{
		if (m_bRed)
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(255, 0, 0));
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		}
		else if (m_bBlue)
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(0, 0, 255));
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH);

		}
		else if (m_bGreen)
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(0, 255, 0));
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH);

		}
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CTestLibDemoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	m_static1 = "";
	UpdateData(FALSE);


	m_static1 = "连接成功";
	m_bRed = FALSE;
	m_bBlue = FALSE;
	m_bGreen = TRUE;

	UpdateData(FALSE);
}

