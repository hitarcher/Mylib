
// TestLibDemoDlg.h : 头文件
//

#pragma once
#include <iostream>
using namespace std;

#include<vector>

//GDI+ 依赖
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;

// CTestLibDemoDlg 对话框
class CTestLibDemoDlg : public CDialogEx
{
// 构造
public:
	CTestLibDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTLIBDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	HANDLE hTest;
	HANDLE hTestEvent;
	static DWORD WINAPI	 TestThreadProc(LPVOID pParam);
	DWORD WINAPI TestThreadContent(LPVOID pParam);

	HANDLE hTest2;
	HANDLE hTestEvent2;
	static DWORD WINAPI	 TestThreadProc2(LPVOID pParam);
	DWORD WINAPI TestThreadContent2(LPVOID pParam);

	HANDLE hThread[3];
	HANDLE hThreadEvent[3];
	static DWORD WINAPI	 TestMultipleThreadProc(LPVOID pParam);
	DWORD WINAPI TestMultipleThreadContent(LPVOID pParam);

	//创建bat文件
	void CTestLibDemoDlg::WriteStartBat1(CString strLoad);
public:
	BOOL m_bRed;
	BOOL m_bBlue;
	BOOL m_bGreen;

	//绘制背景图的
	Gdiplus::GdiplusStartupInput m_GdiplusStarupInput;
	ULONG_PTR m_uGdiplusToken;
	Gdiplus::Image* m_img;

	int valueAA;
	void  testconst() const;
	void testconst2()const;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_static1;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton1();

	void testShellExecute();

	void CTestLibDemoDlg::teststring();
};
void testStr();
void testStr2();
void testPython();
void testPython2();
int testPython4();
void testbooble();
void testUnicode();
