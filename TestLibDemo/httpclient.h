#pragma once
/************************Http: Get¡¢PostµÄ·â×°Àà***************/

#include   "wininet.h"    
#include   "afxinet.h"  
#include <iostream>
using namespace std;
#include <vector>

class CHttpClient
{
public:
	CHttpClient();
	~CHttpClient();

	CString CHttpClient::doPostFile(CString strHref, vector<CString>vecName, vector<CString>vecContent);
private:
	CString m_strLastErr;
	CString GetLastErr() { return m_strLastErr; }

};
