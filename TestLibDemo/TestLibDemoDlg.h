
// TestLibDemoDlg.h : ͷ�ļ�
//

#pragma once
#include <iostream>
using namespace std;

#include<vector>

//GDI+ ����
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;

#include "MyLib.h"
#ifdef DEBUG
#pragma comment(lib,"MyLibd.lib")
#else
#pragma comment(lib,"MyLib.lib")
#endif // DEBUG


//extern �÷�������Ҫ����ͷ�ļ�Ҳ����ʹ��


// CTestLibDemoDlg �Ի���
class CTestLibDemoDlg : public CDialogEx
{
// ����
public:
	CTestLibDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTLIBDEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	//����bat�ļ�
	void CTestLibDemoDlg::WriteStartBat1(CString strLoad);
public:
	BOOL m_bRed;
	BOOL m_bBlue;
	BOOL m_bGreen;

	//���Ʊ���ͼ��
	Gdiplus::GdiplusStartupInput m_GdiplusStarupInput;
	ULONG_PTR m_uGdiplusToken;
	Gdiplus::Image* m_img;

	int valueAA;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
