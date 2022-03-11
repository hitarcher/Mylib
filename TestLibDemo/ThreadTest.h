#pragma once
#include <iostream>
using namespace std;

#include<vector>

//GDI+ “¿¿µ
#include <gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;
class MyThread : public CDialogEx
{

public:
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


};
