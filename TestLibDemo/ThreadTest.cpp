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
		DWORD dwResult = WaitForSingleObject(hTestEvent, INFINITE); //�ȴ�һ�����̽���
																	//DWORD dwResult = WaitForSingleObject(hTestEvent, 5000); //�ȴ�5�룬�����յ���񣬶�����WAIT_TIMEOUT
		switch (dwResult)
		{
		case WAIT_OBJECT_0:
			// hProcess������Ľ�����5���ڽ���
			AfxMessageBox("2");
			break;

		case WAIT_TIMEOUT:
			// �ȴ�ʱ�䳬��5��
			AfxMessageBox("1");
			break;

		case WAIT_FAILED:
			// ��������ʧ�ܣ����紫����һ����Ч�ľ��,
			//hTestEvent ����ֵΪnull,Ȼ��setEvent(hTestEvent),����WaitForSingleObject,�����WAIT_FAILED
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
	DWORD dw = WaitForMultipleObjects(3, hThreadEvent, FALSE, INFINITE); //�ȴ�3�����̽���

	switch (dw)
	{
	case WAIT_FAILED:
		// ��������ʧ��
		break;

	case WAIT_TIMEOUT:
		// ��ʱ
		break;

	case WAIT_OBJECT_0 + 0:
		// h[0]��hProcess1��������Ľ��̽���
		AfxMessageBox("t1");
		break;

	case WAIT_OBJECT_0 + 1:
		// h[1]��hProcess2��������Ľ��̽���
		AfxMessageBox("t2");
		break;

	case WAIT_OBJECT_0 + 2:
		// h[2]��hProcess3��������Ľ��̽���
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
		DWORD dwResult = WaitForSingleObject(pthInfo->hEvent, INFINITE); //�ȴ�һ�����̽���
																		 //DWORD dwResult = WaitForSingleObject(hTestEvent, 5000); //�ȴ�5�룬�����յ���񣬶�����WAIT_TIMEOUT
		switch (dwResult)
		{
		case WAIT_OBJECT_0:
			// hProcess������Ľ�����5���ڽ���
			//AfxMessageBox("2");
			break;

		case WAIT_TIMEOUT:
			// �ȴ�ʱ�䳬��5��
			AfxMessageBox("1");
			break;

		case WAIT_FAILED:
			// ��������ʧ�ܣ����紫����һ����Ч�ľ��,
			//hTestEvent ����ֵΪnull,Ȼ��setEvent(hTestEvent),����WaitForSingleObject,�����WAIT_FAILED
			AfxMessageBox("3");
			break;
		}
		ResetEvent(hTestEvent);
	}
	return TRUE;
}
