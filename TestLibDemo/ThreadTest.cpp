#include "stdafx.h"



DWORD MyThread::TestThreadProc(LPVOID pParam)
{
	MyThread *pDlg = (MyThread *)pParam;
	return pDlg->TestThreadContent(pParam);
}

DWORD MyThread::TestThreadContent(LPVOID pParam)
{
	while (FALSE == g_bExit)
	{
		DWORD dwResult = WaitForSingleObject(hTestEvent, INFINITE); //等待一个进程结束
																	//DWORD dwResult = WaitForSingleObject(hTestEvent, 5000); //等待5秒，无论收到与否，都进入WAIT_TIMEOUT
		switch (dwResult)
		{
		case WAIT_OBJECT_0:
			// hProcess所代表的进程在5秒内结束
			AfxMessageBox("2");
			break;

		case WAIT_TIMEOUT:
			// 等待时间超过5秒
			AfxMessageBox("1");
			break;

		case WAIT_FAILED:
			// 函数调用失败，比如传递了一个无效的句柄,
			//hTestEvent 被赋值为null,然后setEvent(hTestEvent),触发WaitForSingleObject,会进入WAIT_FAILED
			AfxMessageBox("3");
			break;
		}
		ResetEvent(hTestEvent);
	}
	return TRUE;
}

DWORD MyThread::TestMultipleThreadProc(LPVOID pParam)
{
	MyThread *pDlg = (MyThread *)pParam;
	return pDlg->TestMultipleThreadContent(pParam);
}

DWORD MyThread::TestMultipleThreadContent(LPVOID pParam)
{
	DWORD dw = WaitForMultipleObjects(3, hThreadEvent, FALSE, INFINITE); //等待3个进程结束

	switch (dw)
	{
	case WAIT_FAILED:
		// 函数呼叫失败
		break;

	case WAIT_TIMEOUT:
		// 超时
		break;

	case WAIT_OBJECT_0 + 0:
		// h[0]（hProcess1）所代表的进程结束
		AfxMessageBox("t1");
		break;

	case WAIT_OBJECT_0 + 1:
		// h[1]（hProcess2）所代表的进程结束
		AfxMessageBox("t2");
		break;

	case WAIT_OBJECT_0 + 2:
		// h[2]（hProcess3）所代表的进程结束
		AfxMessageBox("t3");

		break;
	}
	return TRUE;
}

DWORD MyThread::TestThreadProc2(LPVOID pParam)
{
	ThreadInfo *pDlg = (ThreadInfo *)pParam;
	return pDlg->pThis->TestThreadContent2(pParam);
}

DWORD MyThread::TestThreadContent2(LPVOID pParam)
{
	ThreadInfo*pthInfo = (ThreadInfo*)pParam;

	while (FALSE == g_bExit)
	{
		DWORD dwResult = WaitForSingleObject(pthInfo->hEvent, INFINITE); //等待一个进程结束
																		 //DWORD dwResult = WaitForSingleObject(hTestEvent, 5000); //等待5秒，无论收到与否，都进入WAIT_TIMEOUT
		switch (dwResult)
		{
		case WAIT_OBJECT_0:
			// hProcess所代表的进程在5秒内结束
			//AfxMessageBox("2");
			break;

		case WAIT_TIMEOUT:
			// 等待时间超过5秒
			AfxMessageBox("1");
			break;

		case WAIT_FAILED:
			// 函数调用失败，比如传递了一个无效的句柄,
			//hTestEvent 被赋值为null,然后setEvent(hTestEvent),触发WaitForSingleObject,会进入WAIT_FAILED
			AfxMessageBox("3");
			break;
		}
		ResetEvent(hTestEvent);
	}
	return TRUE;
}
