
// TestLibDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestLibDemoApp: 
// �йش����ʵ�֣������ TestLibDemo.cpp
//

class CTestLibDemoApp : public CWinApp
{
public:
	CTestLibDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestLibDemoApp theApp;