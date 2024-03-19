
// TestLibDemoDlg.cpp : ʵ���ļ�
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
//ѹ����Ƶ��ת��AVI
//int  testVideo()
//{
//	VideoCapture capture("D:\\1.mp4");//��ȡ��Ƶ�������Լ�����Ƶλ�ø���
//	if (!capture.isOpened())
//		return -1;
//
//	capture.set(CV_CAP_PROP_FRAME_WIDTH, 1920);
//	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
//	//VideoWriter(const String & filename, int fourcc, double fps,Size frameSize, bool isColor = true);
//
//	//�ı�ͼ���֡��Ϊ30��ͼ��֡�Ĵ�С�ǣ�640��480��
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
// 	if ((ret = avformat_open_input(&ifmt_ctx, in_filename, 0, 0)) < 0) {//��ý���ļ�
// 		printf("Could not open input file.");
// 		goto end;
// 	}
// 	if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0) {//��ȡ��Ƶ��Ϣ
// 		printf("Failed to retrieve input stream information");
// 		goto end;
// 	}
// 	av_dump_format(ifmt_ctx, 0, in_filename, 0);
// 	//��ʼ�������Ƶ������AVFormatContext��
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
// 		AVStream *out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);// ��ʼ��AVStream 
// 		if (!out_stream) {
// 			printf("Failed allocating output stream\n");
// 			ret = AVERROR_UNKNOWN;
// 			goto end;
// 		}
// 		//�ؼ���Copy the settings of AVCodecContext
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
// 		ret = avio_open(&ofmt_ctx->pb, out_filename, AVIO_FLAG_WRITE);//������ļ���
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
// 		if (av_interleaved_write_frame(ofmt_ctx, &pkt) < 0) {//��AVPacket���洢��Ƶѹ���������ݣ�д���ļ�
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

// CTestLibDemoDlg ��Ϣ�������

BOOL CTestLibDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	testC11();

	bool bret = CheckEmail("123@qq.com");
	bret = CheckEnAndNum("���");
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
		//������ȱֽ״̬ʱ������ֽ�³��������ʱ��֪ͨ�����ʾ����ӡ��ɡ�������ʵġ�
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

	delete bp3;
	/*
	����˳��
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
	int *p = (int*)calloc(5, sizeof(int));//����5���ռ�
	assert(p);
	for (int i =0;i<10;i++)
	{
		if (i ==5)
		{
			p = (int*)realloc(p, sizeof(int) *10);//p�Ŀռ����ݵ�10��������p��ʵ�ʵ�ַ����
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

	// 		 //��һ�֣�
	// 		 GetWindowRect(&largerect);
	// 		 GetDlgItem(IDC_BUTTON1)->SetWindowPos(NULL, largerect.left + 10, largerect.top + 10, 0, 0,
	// 			 SWP_NOZORDER | SWP_NOSIZE);
	// 		 UpdateData(FALSE);
	// 		 Sleep(2000)
	// 		 SetTimer(TIMER_TEST, 2000, NULL);
	// CTestLibDemoDlg::OnTimer(nIDEvent);
}

//�򿪻�ͼ�������棬����һ�����⣬��һ�ö����������鷳�ˡ�
void MspaintSave(CString strFilePat)
{
	CString strPath = strFilePat;
	strPath.Replace("/", "\\");
	CString strEnd = ("\"") + strPath + ("\""); //��������Ϊ�˱���·���пո�,��Ϊcmd����Ͽո�
	::ShellExecuteA(NULL, "open", "mspaint.exe", strEnd, NULL, SW_SHOWNORMAL); //ֻ��'\\'·��
																			   //HWND hWin = ::FindWindow("��ͼ(32λ)", NULL);
	Sleep(5000);
	keybd_event(VK_CONTROL, 0, 0, 0);
	Sleep(50);
	keybd_event(83, 0, 0, 0);
	Sleep(2000);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);//̧�𰴼�
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

void testC11()
{
	auto a = 11;
	auto b = 1.2;



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

//һֱ�ڼ����û����ɫ�����仯
HBRUSH CTestLibDemoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
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

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void CTestLibDemoDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	m_static1 = "";
	UpdateData(FALSE);


	m_static1 = "���ӳɹ�";
	m_bRed = FALSE;
	m_bBlue = FALSE;
	m_bGreen = TRUE;

	UpdateData(FALSE);
}

