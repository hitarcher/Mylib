#include "stdafx.h"
#include "httpclient.h"


CHttpClient::CHttpClient()
{
}

CHttpClient::~CHttpClient()
{
}

//封装协议头  
CString MakeRequestHeaders(CString &strBoundary)// strBoundary 为协议中的boundary  
{
	CString strFormat = _T("");
	CString strData = _T("");
	//strFormat += "User-Agent: Mozilla/4.0\r\n";   
	strFormat += "Connection: Keep-Alive\r\n";
	strFormat += "Accept:*/*\r\n";
	strFormat += "Accept-Language: zh-cn\r\n";
	strFormat += _T("Accept-Encoding:gzip,deflate\r\n");
	strFormat += _T("enctype:multipart/form-data\r\n");
	strFormat += _T("Content-Type: multipart/form-data; boundary=%s");
	strData.Format(strFormat, strBoundary);
	return strData;
}

//封装数据前面的描述部分  
//CString MakePreFileData(CString &strBoundary, CString &strFileName, CString strMsgID)
//{
//	CString strFormat=_T("");  
//	CString strData=_T("");  
//	strFormat += _T("--%s");  
//	strFormat += _T("\r\n");
//	strFormat += _T("Content-Disposition: form-data; name=\"file\"; filename=\"%s\"");
//	strFormat += _T("\r\n");
//	strFormat += _T("Content-Type:application/octet-stream\r\n\r\n");
//	strData.Format(strFormat, strBoundary, strFileName);  
//	return strData;  
//}

//协议体
CString MakePreFileData1(CString &strBoundary, CString strName, CString strMsgContent)
{
	CString strFormat = _T("");
	CString strData = _T("");
	strFormat += _T("\r\n--%s\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"%s\"");
	strFormat += _T("\r\n");
	strFormat += _T("\r\n%s");


	strData.Format(strFormat, strBoundary, strName, strMsgContent);
	return strData;
}

//封装协议尾  
CString MakePostFileData(CString &strBoundary)
{
	CString strFormat;
	CString strData;
	//strFormat = _T("\r\n");
	//strFormat += _T("--%s");
	//strFormat += _T("\r\n");
	//strFormat += _T("Content-Disposition: form-data; name=\"submitted\"");
	//strFormat += _T("\r\n\r\n");
	//strFormat += _T("submit");
	strFormat += _T("\r\n");
	strFormat += _T("--%s--");
	strFormat += _T("\r\n");
	strData.Format(strFormat, strBoundary);
	return strData;
}

CString CHttpClient::doPostFile(CString strHref, vector<CString>vecName, vector<CString>vecContent)
{
	CString httpsource = "";
	CInternetSession session1;
	CHttpConnection* conn1 = NULL;
	CHttpFile* pFile = NULL;
	CString strServerName;
	CString strObject;
	INTERNET_PORT   nPort;
	DWORD dwServiceType;
	CString strRequestHeader = _T("");
	CString strHTTPBoundary = _T("");
	CString strPostFileData = _T("");
	CString strResponse = _T("");

	AfxParseURL((LPCTSTR)strHref, dwServiceType, strServerName, strObject, nPort);
	DWORD retcode;
	strHTTPBoundary = _T("-----------------------------7d86d16250370");
	strRequestHeader = MakeRequestHeaders(strHTTPBoundary);
	strPostFileData = MakePostFileData(strHTTPBoundary);
	/*	if (FALSE == fTrack.Open(strFilePath, CFile::modeRead | CFile::shareDenyWrite))
	{
	m_strLastErr.Format("打开文件[%s]失败", strFilePath);
	return "";
	}  */
	DWORD dwTotalRequestLength = strPostFileData.GetLength();
	if (vecName.size() != vecContent.size())
		return "";
	for (int i = 0; i < vecName.size(); i++)
	{
		dwTotalRequestLength += MakePreFileData1(strHTTPBoundary, vecName[i], vecContent[i]).GetLength();
	}
	try
	{
		conn1 = session1.GetHttpConnection(strServerName, nPort);
		pFile = conn1->OpenRequest(CHttpConnection::HTTP_VERB_POST, strObject);
		pFile->AddRequestHeaders(strRequestHeader);
		if (!pFile->SendRequestEx(dwTotalRequestLength, HSR_SYNC | HSR_INITIATE))
		{
			m_strLastErr.Format("SendRequestEx失败[%d]", GetLastError());
			return "";
		}
		//pFile->Write((LPSTR)(LPCSTR)strPreFileData, strPreFileData.GetLength());
		//DWORD dwReadLength = -1;  
		//int count = 1; 
		//while (0 != dwReadLength)  
		//{  
		//	dwReadLength = fTrack.Read(pBuffer, dwChunkLength);
		//	count++;
		//	if (0 != dwReadLength)
		//	{  
		//		pFile->Write(pBuffer, dwReadLength);
		//	}
		//}
		//fTrack.Close();

		for (int i = 0; i < vecName.size(); i++)
		{
			pFile->Write((LPSTR)(LPCSTR)MakePreFileData1(strHTTPBoundary, vecName[i], vecContent[i]), MakePreFileData1(strHTTPBoundary, vecName[i], vecContent[i]).GetLength());
		}
		pFile->Write((LPSTR)(LPCSTR)strPostFileData, strPostFileData.GetLength());
		pFile->EndRequest(HSR_SYNC);
		pFile->QueryInfoStatusCode(retcode);
		if (retcode == HTTP_STATUS_OK)
		{
			CString text;
			for (int i = 0; pFile->ReadString(text); i++)
			{
				httpsource = httpsource + text + "\r\n";
			}
			pFile->Close();
			delete pFile;
			delete conn1;
			session1.Close();
			return httpsource;
		}
		else
		{
			return "";
		}
	}
	catch (CInternetException* e)
	{
		return "";
	};
	return "";
}