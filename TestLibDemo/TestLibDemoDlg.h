
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

#include "MyLib.h"
#ifdef DEBUG
#pragma comment(lib,"MyLibd.lib")
#else
#pragma comment(lib,"MyLib.lib")
#endif // DEBUG


//extern 用法，不需要包含头文件也可以使用


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


	HANDLE m_hTest;
	HANDLE m_hTestEvent;
	static DWORD WINAPI	TestThreadProc(LPVOID pParam);
	DWORD WINAPI TestThreadContent(LPVOID pParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);


	//void CTestLibDemoDlg::teststring();
	void testConst();
	void testVirtual();
	void testPC();
	void testC11();
};
void testRelloc();
void testlambda();
