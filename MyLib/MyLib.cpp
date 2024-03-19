#include "stdafx.h"
#include "MyLib.h"

#include "MyMD5.h"
//�޸�����ͷ�ļ�
#include <windows.h> 
#include <mmdeviceapi.h> 
#include <endpointvolume.h>
#include <audioclient.h>

#include "Base64.h"
//����ͷ�ļ�
#include "MakePNG.h"
CString g_configPath = "config//config.ini";
//��þ���·��
CString getFullPath(CString strTempPath)
{
	CString strEngineeringPath;
	TCHAR szPath[MAX_PATH] = { 0 };
	if (GetModuleFileName(NULL, szPath, MAX_PATH))
	{
		TCHAR *pChr = _tcsrchr(szPath, _T('\\'));
		pChr++;
		*pChr = _T('\0');
		//(_tcsrchr(szPath, _T('\\')))[1] = 0;//�����������һ�����
	}
	strEngineeringPath.Format(_T("%s"), szPath);

	return strEngineeringPath + strTempPath;
}

//getFullpath
CString GetAppPathW()
{
	wchar_t szExePath[MAX_PATH] = { 0 };
	GetModuleFileNameW(NULL, szExePath, MAX_PATH);
	wchar_t *pstr = wcsrchr(szExePath, '\\');
	memset(pstr + 1, 0, 2);
	CString strAppPath(szExePath);
	return strAppPath;
}

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/// �ж��ļ��Ƿ����
BOOL CheckFileExist(CString strFilePath)
{
	FILE *pFile;
	fopen_s(&pFile, strFilePath, "rb");

	if (NULL == pFile)
	{
		return FALSE;
	}

	fclose(pFile);

	return TRUE;
}

//ɾ�ļ��к�����
bool RemoveDir(const char* szFileDir)
{
	std::string strDir = szFileDir;
	if (strDir.at(strDir.length() - 1) != '\\')
		strDir += '\\';
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile((strDir + "*.*").c_str(), &wfd);
	if (hFind == INVALID_HANDLE_VALUE)
		return false;
	do
	{
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (_stricmp(wfd.cFileName, ".") != 0 &&
				_stricmp(wfd.cFileName, "..") != 0)
				RemoveDir((strDir + wfd.cFileName).c_str());
		}
		else
		{
			DeleteFile((strDir + wfd.cFileName).c_str());
		}
	} while (FindNextFile(hFind, &wfd));
	FindClose(hFind);
	RemoveDirectory(szFileDir);
	return true;
}

//Ǩ���ļ������Ϊ��ȫ·������ȫ·�����Լ���·���µ�·�ļ����ͣ���jpg,mp4,*�������·���к���ͬ���ļ����򲻻��ƶ���
void RemoveFileToOtherPath(const char* pathOld, const char* pathNew, const char * type)
{
	CFileFind finder;
	char szOldTextPath[MAX_PATH] = "";
	sprintf(szOldTextPath, "%s\\*.%s", pathOld, type);
	char szNewTextPath[MAX_PATH] = "";

	BOOL bWorking = finder.FindFile(szOldTextPath);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		CString strFileName = finder.GetFileName();
		if (finder.IsDirectory())continue;
		sprintf(szNewTextPath, "%s\\%s", pathNew, strFileName.GetBuffer(0));
		MoveFile(finder.GetFilePath(), szNewTextPath);
	}
}

//��ý��������ڼ�������0-6����һ=0������=6
int GetWeekDay()
{
	/*
	time_t��һ���洢ʱ����Ϣ��long int
	time(&rawtime) ��ϵͳʱ�����rawtime���time_t��
	struct tm *timeinfo ��tm��һ����ʱ����Ϣ�Ľṹ�� timeinfo��ָ��һ������ṹ���ָ��
	timeinfo=localtime(&rawtime) ��֮ǰtime()�õ�����Ϣת��Ϊstruct tm����
	*/
	struct tm *ptr;
	time_t lt;
	lt = time(NULL);
	ptr = localtime(&lt);
	//mlgb,ϵͳ����0Ϊ���գ�ƽ̨���˲� ����0Ϊ��һ����ô���ظ���.
	int iSysTime = ptr->tm_wday;
	int iPFTime = iSysTime - 1;
	if (iPFTime < 0) iPFTime = 6;

	return  iPFTime;
}

//�޸�ʱ�䣬��YYYYMMDDHHMMSS ���YYYY-MM-DD HH:MM:SS
CString changeTime(CString strTime)
{
	CString strpart1 = strTime.Left(8);
	CString strpart2 = strTime.Right(strTime.GetLength() - 8);

	CString str1 = "";
	str1.Format("%s-%s-%s ", strpart1.Left(4), strpart1.Mid(4, 2), strpart1.Right(2));

	CString str2 = "";
	str2.Format("%s:%s:%s", strpart2.Left(2), strpart2.Mid(2, 2), strpart2.Right(2));

	return str1 + str2;
}

//�޸�����������������ֵ
bool SetVolumeLevel(int level)
{
	HRESULT hr;
	IMMDeviceEnumerator* pDeviceEnumerator = 0;
	IMMDevice* pDevice = 0;
	IAudioEndpointVolume* pAudioEndpointVolume = 0;
	IAudioClient* pAudioClient = 0;

	try {
		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pDeviceEnumerator);
		if (FAILED(hr)) throw "CoCreateInstance";
		hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
		if (FAILED(hr)) throw "GetDefaultAudioEndpoint";
		hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pAudioEndpointVolume);
		if (FAILED(hr)) throw "pDevice->Active";
		hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&pAudioClient);
		if (FAILED(hr)) throw "pDevice->Active";

		if (level == -2) {
			hr = pAudioEndpointVolume->SetMute(FALSE, NULL);
			if (FAILED(hr)) throw "SetMute";
		}
		else if (level == -1) {
			hr = pAudioEndpointVolume->SetMute(TRUE, NULL);
			if (FAILED(hr)) throw "SetMute";
		}
		else {
			if (level < 0 || level>100) {
				hr = E_INVALIDARG;
				throw "Invalid Arg";
			}

			float fVolume;
			fVolume = level / 100.0f;
			hr = pAudioEndpointVolume->SetMasterVolumeLevelScalar(fVolume, &GUID_NULL);
			if (FAILED(hr)) throw "SetMasterVolumeLevelScalar";

			pAudioClient->Release();
			pAudioEndpointVolume->Release();
			pDevice->Release();
			pDeviceEnumerator->Release();
			return true;
		}
	}
	catch (...) {
		if (pAudioClient) pAudioClient->Release();
		if (pAudioEndpointVolume) pAudioEndpointVolume->Release();
		if (pDevice) pDevice->Release();
		if (pDeviceEnumerator) pDeviceEnumerator->Release();
		throw;
	}
	return false;
}

//�ж����Ƿ���json����
bool IsJsonData(std::string strData)
{
	if (strData[0] != '{')
		return false;

	int num = 1;
	for (unsigned int i = 1; i < strData.length(); ++i)
	{
		if (strData[i] == '{')
		{
			++num;
		}
		else if (strData[i] == '}')
		{
			--num;
		}

		if (num == 0)
		{
			return true;
		}
	}

	return false;
}

//תgbk��utf8
void ConvertGbkToUtf8(CString &strConvert)
{
	//�ú���ӳ��һ�����ֽڵ�һ�����ַ���unicode�����ַ�����
	/*int MultiByteToWideChar(
����UINT CodePage,
����DWORD dwFlags,
����LPCSTR lpMultiByteStr,
����int cchMultiByte,
����LPWSTR lpWideCharStr,
����int cchWideChar);*/

  //ע�⣺����n��len��ֵ��С��ͬ,n�ǰ��ַ�����ģ�len�ǰ��ֽڼ���ģ�һ������ռ�����ֽ�
	//  CString str = _T("D://У����Ŀ//QQ.bmp");
	int n = strConvert.GetLength();     // n = 14(str��), len = 18(str��)

	//����MultiByteToWideChar()����������cchWideChar����Ϊ0�����Ի�ȡת������Ľ��ջ�������С����
	//Ϊ���ֽ��ַ���������ռ䣬�����СΪ���ֽڼ���Ķ��ֽ��ַ���С
	int len = MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strConvert, -1, NULL, 0);
	// ��ȡ���뻺��Ĵ�С����ΪcchMultiByte��ֵ��
	//			����������Ϊ�˽�ʡ�ռ䣬Ҳ���Ը�cchMultiByteȡֵ-1���ַ�����Ҫ�Կ��ַ���β������������

	// �����㹻���ڴ�飬���ڴ��ת�����Unicode�ַ��������ڴ��Ĵ�С��ǰ���cchWideChar()�����ķ���ֵ��������
	//			��Ҳ�����ñ�ķ��������÷�������ʡ�ڴ棩
	wchar_t * wszUtf8 = new wchar_t[len];
	memset(wszUtf8, 0, len);
	//�ٴε���MultiByteToWideChar()��������ν�����ĵ�ַ��ΪlpWideCharStr,���������ݣ�
	//�����ݵ�һ�ε���MultiByteToWideChar()����ʱ�ķ���ֵ��ΪcchWideChar������ֵ��
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strConvert, -1, wszUtf8, len);
	/************************************************************************************************************************/

	//�ӿ��ֽڣ�unicode��תΪխ�ֽ��ַ���(utf-8)
	/*int WideCharToMultiByte(
����UINT CodePage,
����DWORD dwFlags,
����LPCWSTR lpWideCharStr,
����int cchWideChar,
����LPSTR lpMultiByteStr,
����int cchMultiByte,
����LPCSTR lpDefaultChar,
����LPBOOL pfUsedDefaultChar);*/
	len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = new char[len + 1];
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, szUtf8, len, NULL, NULL);
	strConvert = szUtf8;
	delete[] szUtf8;
	delete[] wszUtf8;
}

//תutf8��gbk
void  ConvertUtf8ToGbk(CString& strUtf8)
{
	int   len = MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, NULL, 0);
	unsigned   short   *   wszGBK = new   unsigned   short[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, (LPWSTR)wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	char   *szGBK = new   char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);
	strUtf8 = szGBK;
	delete[]   szGBK;
	delete[]   wszGBK;
}

// ��Unicode�ַ���ת��ΪAnsicode�ַ���
void ConvertUnicodeToAnsi(wchar_t* source, char* dest)
{
	int len = 0;
	len = WideCharToMultiByte(CP_ACP, 0, source, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, source, -1, dest, len, NULL, NULL);
}

// ��Ansicode�ַ���ת��ΪUnicode�ַ���
void ConvertAnsiToUnicode(char* source, wchar_t* dest)
{
	int len = 0;
	len = MultiByteToWideChar(CP_ACP, 0, source, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, source, -1, dest, len);
}

//����ͼƬ·��������base64����	
CString Base64EncodePic(CString strPath)
{
	HANDLE hFile;
	hFile = CreateFile(strPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD dFileSize = GetFileSize(hFile, NULL);
	char * pBuffer = new char[dFileSize + 1];

	if (pBuffer == NULL)
		return false;

	memset(pBuffer, 0, dFileSize);

	DWORD dReadSize(0);
	if (!ReadFile(hFile, pBuffer, dFileSize, &dReadSize, NULL))
	{
		delete[]pBuffer;
		CloseHandle(hFile);
		return false;
	}
	string strData = base64_encode((const unsigned char*)pBuffer, dReadSize);
	CString strReturn = strData.c_str();
	delete[]pBuffer;
	CloseHandle(hFile);
	return strReturn;
}

//����һ���ļ�Ŀ¼path��Ȼ���ҵ��������У���������Ŀ¼����ļ���
 void  getFloderFiles(string path, vector<string>& files)
 {
 	//�ļ����  
 	long   hFile = 0;
 	//�ļ���Ϣ  
 	struct _finddata_t fileinfo;
 	string p;
 	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
 	{
 		do
 		{
 			//�����Ŀ¼,����֮  
 			//�������,�����б�  
 			if ((fileinfo.attrib &  _A_SUBDIR))
 			{
 				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFloderFiles(p.assign(path).append("\\").append(fileinfo.name), files);
 			}
 			else
 			{
 				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
 			}
 		} while (_findnext(hFile, &fileinfo) == 0);
 		_findclose(hFile);
 	}
 }
 
 //��������
 void OnClose()
 {
	 // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	 // 	if (g_bIsRunAgain)
	 // 	{
	 //�õ���ǰ�����·����
	 CString strPath;
	 GetModuleFileName(NULL, strPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH + 1);

	 STARTUPINFO StartInfo;
	 PROCESS_INFORMATION procStruct;
	 memset(&StartInfo, 0, sizeof(STARTUPINFO));
	 StartInfo.cb = sizeof(STARTUPINFO);

	 if (CreateProcess((LPCTSTR)strPath, NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &StartInfo, &procStruct))
	 {
		 CloseHandle(procStruct.hProcess);
		 CloseHandle(procStruct.hThread);
	 }
	 //	}

	 //	CDialogEx::OnClose();
 }

 int UrlEncodeUtf8(LPCSTR pszUrl, LPSTR pszEncode, int nEncodeLen)
 {
	 int nRes = 0;
	 //�������
	 wchar_t* pWString = NULL;
	 char* pString = NULL;
	 char* pResult = NULL;

	 do
	 {
		 if (pszUrl == NULL)
			 break;

		 //�Ƚ��ַ����ɶ��ֽ�ת����UTF-8����  
		 int nLength = MultiByteToWideChar(CP_ACP, 0, pszUrl, -1, NULL, 0);

		 //����Unicode�ռ�  
		 pWString = new wchar_t[nLength + 1];
		 if (pWString == NULL)
			 break;

		 memset(pWString, 0, (nLength + 1) * sizeof(wchar_t));
		 //��ת����Unicode
		 MultiByteToWideChar(CP_ACP, 0, pszUrl, -1, pWString, nLength);

		 //����UTF-8�ռ�
		 nLength = WideCharToMultiByte(CP_UTF8, 0, pWString, -1, NULL, 0, NULL, NULL);
		 pString = new char[nLength + 1];
		 if (pString == NULL)
			 break;

		 memset(pString, 0, nLength + 1);
		 //Unicodeת��UTF-8
		 nLength = WideCharToMultiByte(CP_UTF8, 0, pWString, -1, pString, nLength, NULL, NULL);

		 pResult = new char[nLength * 3];
		 if (pResult == NULL)
			 break;

		 memset(pResult, 0, nLength * 3);
		 char* pTmp = pResult;
		 static char hex[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

		 for (int i = 0; i < nLength; i++)
		 {
			 unsigned char c = pString[i];
			 if (c == 0)
			 {
				 break;
			 }

			 if (c > 0x20 && c < 0x7f)// ���ֻ���ĸ
			 {
				 *pTmp++ = c;
			 }
			 else if (c == 0x20)// �����ո�  
			 {
				 *pTmp++ = '%';
				 *pTmp++ = hex[c / 16];
				 *pTmp++ = hex[c % 16];
			 }
			 else// ���б���
			 {
				 *pTmp++ = '%';
				 *pTmp++ = hex[c / 16];
				 *pTmp++ = hex[c % 16];
			 }
		 }
		 nLength = strlen(pResult);
		 nRes = nLength;
		 if (pszEncode == NULL || nEncodeLen < nLength)
			 break;

		 memcpy(pszEncode, pResult, nLength);
	 } while (0);

	 if (pWString != NULL)
		 delete[]pWString;

	 if (pString != NULL)
		 delete[]pString;

	 if (pResult != NULL)
		 delete[]pResult;

	 return nRes;
 }

//ʮ������ת�ַ���
 static void hex_to_str(char *ptr, unsigned char *buf, int len)
 {
	 for (int i = 0; i < len; i++)
	 {
		 sprintf(ptr, "%02x", buf[i]);
		 ptr += 2;
	 }
 }

//�ַ���ת��Ϊʮ������
 static int str_to_hex(char *string, unsigned char *cbuf, int len)
 {
	 BYTE high, low;
	 int idx, ii = 0;
	 for (idx = 0; idx < len; idx += 2)
	 {
		 high = string[idx];
		 low = string[idx + 1];

		 if (high >= '0' && high <= '9')
			 high = high - '0';
		 else if (high >= 'A' && high <= 'F')
			 high = high - 'A' + 10;
		 else if (high >= 'a' && high <= 'f')
			 high = high - 'a' + 10;
		 else
			 return -1;

		 if (low >= '0' && low <= '9')
			 low = low - '0';
		 else if (low >= 'A' && low <= 'F')
			 low = low - 'A' + 10;
		 else if (low >= 'a' && low <= 'f')
			 low = low - 'a' + 10;
		 else
			 return -1;

		 cbuf[ii++] = high << 4 | low;
	 }
	 return 0;
 }

// �ָ��ַ���
 vector<CString> SplitString(CString &strContent, const string &seperator)
 {
	 vector<CString> result;
	 typedef string::size_type string_size;
	 string_size i = 0;
	 string s = strContent;

	 while (i != s.size()) {
		 //�ҵ��ַ������׸������ڷָ�������ĸ��
		 int flag = 0;
		 while (i != s.size() && flag == 0) {
			 flag = 1;
			 for (string_size x = 0; x < seperator.size(); ++x)
				 if (s[i] == seperator[x]) {
					 ++i;
					 flag = 0;
					 break;
				 }
		 }

		 //�ҵ���һ���ָ������������ָ���֮����ַ���ȡ����
		 flag = 0;
		 string_size j = i;
		 while (j != s.size() && flag == 0) {
			 for (string_size x = 0; x < seperator.size(); ++x)
				 if (s[j] == seperator[x]) {
					 flag = 1;
					 break;
				 }
			 if (flag == 0)
				 ++j;
		 }
		 if (i != j) {
			 result.push_back(s.substr(i, j - i).c_str());
			 i = j;
		 }
	 }
	 return result;
 }

 //��ȡ�ļ�
 BOOL ReadFileContent(CString &strContent, CString pFileName)
 {
	 CFile file;
	 CFileStatus status;
	 if (FALSE == CheckFileExist(pFileName))
	 {
		 return FALSE;
	 }
	 //1 ��
	 if (file.Open(pFileName, CFile::modeReadWrite) == FALSE &&
		 file.Open(pFileName, CFile::modeCreate | CFile::modeReadWrite) == FALSE)
	 {
		 return FALSE;
	 }
	 file.GetStatus(status);
	 //2 �п�
	 if (status.m_size == 0)
	 {
		 return FALSE;
	 }
	 else
	 {
		 char* pTemplate = (char*)calloc((int)status.m_size + 1, sizeof(char));
		 file.Read(pTemplate, (int)status.m_size);
		 CString strJson = pTemplate;
		 ConvertUtf8ToGbk(strJson);
		 strContent = strJson;
		 //json jrsp = json::parse(strJson.GetBuffer(0));
		 free(pTemplate);
		 pTemplate = NULL;
	 }
	 file.Close();

	 return TRUE;
 }

 //��ȡ�ļ�����
 CString ReadFileContent(const char* pFile)
 {
	 CStdioFile file;
	 CString szLine = "";
	 CString strText = "";
	 if (!file.Open(pFile, CFile::modeRead))
	 {
		 return "";
	 }
	 //���ж�ȡ�ַ���
	 while (file.ReadString(szLine))
	 {
		 strText += szLine;
	 }
	 file.Close();
	 return strText;
 }

 //�����ļ�
 BOOL WriteFileCotent(CString strContent, CString pFileName)
 {
	 CFile filenew(pFileName, CFile::modeCreate | CFile::modeWrite);
	 CString strUtf = strContent;
	 ConvertGbkToUtf8(strUtf);
	 filenew.Write(strUtf.GetBuffer(0), strUtf.GetLength());
	 filenew.Close();
	 return TRUE;
 }

 //��ȡʱ��
 CString GetCurTime(int nType)
 {
 	CString strCurTime = "";
 	time_t tmCur;
 	time(&tmCur);
 	struct tm*pCurTime;
 	pCurTime = localtime(&tmCur);
 	char szDate[30];
 
 	//	CString strCurTime = TEXT_NULL;
 	//time_t tmCur;
 	//time(&tmCur);
 	//struct tm* pCurTime;
 	//pCurTime = localtime(&tmCur);
 
 	switch (nType)
 	{
 	case 0:
 		sprintf(szDate, "%d-%02d-%02d %02d:%02d:%02d", pCurTime->tm_year + 1900, pCurTime->tm_mon + 1, pCurTime->tm_mday,
 			pCurTime->tm_hour, pCurTime->tm_min, pCurTime->tm_sec);
 		break;
 	case 1:
 		sprintf(szDate, "%d%02d%02d", pCurTime->tm_year + 1900, pCurTime->tm_mon + 1, pCurTime->tm_mday);
 		break;
 	case 2:
 		sprintf(szDate, "%02d%02d%02d", pCurTime->tm_hour, pCurTime->tm_min, pCurTime->tm_sec);
 		break;
 	case 3:
 		sprintf(szDate, "%d%02d%02d%02d%02d%02d", pCurTime->tm_year + 1900, pCurTime->tm_mon + 1, pCurTime->tm_mday,
 			pCurTime->tm_hour, pCurTime->tm_min, pCurTime->tm_sec);
 		break;
 	case 4:
 		sprintf(szDate, "%02d%02d", pCurTime->tm_mon + 1, pCurTime->tm_mday);
 		break;
 	case 5:
 		sprintf(szDate, "%d-%02d-%02d", pCurTime->tm_year + 1900, pCurTime->tm_mon + 1, pCurTime->tm_mday);
 		break;
 	case 6:
 		sprintf(szDate, "%02d:%02d:%02d", pCurTime->tm_hour, pCurTime->tm_min, pCurTime->tm_sec);
 		break;
 	case 7:
 		sprintf(szDate, "%02d%02d%02d%02d%02d%02d", pCurTime->tm_year - 100, pCurTime->tm_mon + 1, pCurTime->tm_mday,
 			pCurTime->tm_hour, pCurTime->tm_min, pCurTime->tm_sec);
 		break;
 	case 8:
 		sprintf(szDate, "%d%02d", pCurTime->tm_year + 1900, pCurTime->tm_mon + 1);
 		break;
 	case 9:
 		sprintf(szDate, "%02d%02d%02d%02d%02d", pCurTime->tm_mon + 1, pCurTime->tm_mday,
 			pCurTime->tm_hour, pCurTime->tm_min, pCurTime->tm_sec);
 		break;
 	case 10:
 		sprintf(szDate, "%02d:%02d", pCurTime->tm_hour, pCurTime->tm_min);
 		break;
 	}
 	strCurTime = szDate;
 	return strCurTime;
 
 }

 void ModifyConfigpath(CString strPath)
 {
	 g_configPath = strPath;
 }

 void WriteContentToCfg(CString strIndex, CString strAppName, LPCSTR strModifyMsg)
 {
	 CString strCfgPath = getFullPath(g_configPath);
	 WritePrivateProfileString(strAppName, strIndex, strModifyMsg, strCfgPath);
 }

 CString GetContentFromCfg(CString strIndex, CString strAppName)
 {
	 CString strTemp;
	 CString strCfgPath = getFullPath(g_configPath);
	 GetPrivateProfileString(strAppName, strIndex, "", strTemp.GetBuffer(1024), 1024, strCfgPath);
	 strTemp.ReleaseBuffer();
	 return strTemp;
 }

 UINT GetIntgFromCfg(CString strAppName, CString strKeyName)
 {
	 CString strCfgPath = getFullPath(g_configPath);
	 int iTemp = GetPrivateProfileInt(strAppName, strKeyName, 0, strCfgPath);
	 return iTemp;
 }

 int GetTimeDifference(CString strTime, BOOL iSReturnSec)
 {
	 CString s1 = GetCurTime(MY_DATE_LONG);
	 CString strTime1 = s1.Right(8);
	 int  iHour = atoi(strTime1.Left(2));
	 int iMin = atoi(strTime1.Mid(3, 2));
	 int iSec = atoi(strTime1.Mid(6, 2));

	 CString s2 = strTime;
	 CString strTime2 = s2.Right(8);
	 int iHour2 = atoi(strTime2.Left(2));
	 int iMin2 = atoi(strTime2.Mid(3, 2));
	 int iSec2 = atoi(strTime2.Mid(6, 2));

	 int  iAllSec = (iHour - iHour2) * 3600 + (iMin - iMin2) * 60 + (iSec - iSec2);
	 int time = iAllSec;
	 if (FALSE == iSReturnSec)
	 {
		 time = iAllSec / 60;
	 }
	 return time;
 }

 //ѭ���滻
 string&   replace_all(string&   str, const   string&   old_value, const   string&   new_value)
 {
	 while (true) {
		 string::size_type   pos(0);
		 if ((pos = str.find(old_value)) != string::npos)
			 str.replace(pos, old_value.length(), new_value);
		 else   break;
	 }
	 return   str;
 }

 //һ�����滻
 string&   replace_all_distinct(string&   str, const   string&   old_value, const   string&   new_value)
 {
	 for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
		 if ((pos = str.find(old_value, pos)) != string::npos)
			 str.replace(pos, old_value.length(), new_value);
		 else   break;
	 }
	 return   str;
 }

 //��ѹ
 DWORD UnZIPFile(CString strTargetFile,CString strResourceFullPath)
 {
	 DWORD  nResult = _unzip(strTargetFile, strResourceFullPath);
	 return nResult;
 }

  //��Ļ��ͼ,����ͼƬ��·��
  CString ScreenShot(void)
  {
 	 CWnd *pDesktop = CWnd::FromHandle(GetDesktopWindow());
 	 CDC *pDC = pDesktop->GetDC();
 	 CRect rect;
 
 	 //��ȡ���ڵĴ�С  
 	 pDesktop->GetClientRect(&rect);
 
 	 //���浽���ļ���
 	 CString strFileName(GetAppPathW());
 	 strFileName += _T("ScreenShot\\");
 	 CreateDirectory((LPCTSTR)strFileName, NULL);
 	 CTime t = CTime::GetCurrentTime();
 	 CString tt = t.Format("%Y%m%d_%H%M%S");
 	 strFileName += tt;
 	 strFileName += _T(".png");

 	 //����ΪPNG
 	 CMakePNG MakePNG;
 	 MakePNG.MakePNG(pDC->m_hDC, rect, strFileName);
	 ::ReleaseDC(GetDesktopWindow(), pDC->m_hDC);
 	 return strFileName;
  }


// �����ļ�������Ϊ���ļ���,����MFC��ͷ�ļ�
 //BOOL HTTP_Download(CString strURL, CString strFilePath)
 //{
 //	BOOL bRes = FALSE;
 //#define PATH_LEN 1024
 //	//����http����
 //	TCHAR szUserName[MAX_PATH] = { 0 };
 //	TCHAR szPassword[MAX_PATH] = { 0 };
 //	_tcscpy(szUserName, "");
 //	_tcscpy(szPassword, "");
 //
 //	const TCHAR szHeaders[] = _T("Accept: */*\r\nUser-Agent:  Mozilla/4.0 (compatible; MSIE 5.00; Windows 98)\r\n");    //Э��
 //
 //	CInternetSession    aInternetSession;        //һ���Ự
 //	CHttpConnection*    pHttpConnection = NULL;    //����
 //	CHttpFile*          pHttpFile = NULL;
 //	DWORD               dwFileStatus;
 //	INTERNET_PORT       nPort;
 //	DWORD               dwServiceType;
 //	DWORD               dwDownloadSize = 0;
 //	CString             strServer;
 //	CString             strObject;
 //
 //	const int nBufferSize = 4096;
 //	TCHAR szURL[nBufferSize] = { 0 };
 //	UrlEncodeUtf8(strURL, szURL, nBufferSize);
 //	strURL = szURL;
 //
 //	//�ֽ�URL
 //	if (AfxParseURL(strURL, dwServiceType, strServer, strObject, nPort))
 //	{
 //		//�������������HTTP����
 //		if (dwServiceType != AFX_INET_SERVICE_HTTP && dwServiceType != AFX_INET_SERVICE_HTTPS)
 //		{
 //			//���سɹ�
 //			return bRes;
 //		}
 //	}
 //
 //	try
 //	{
 //		pHttpConnection = aInternetSession.GetHttpConnection(strServer, nPort);
 //		do
 //		{
 //			//���ʧ�����߳��˳�
 //			if (pHttpConnection == NULL)
 //				break;
 //
 //			//ȡ��HttpFile����
 //			pHttpFile = pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET,
 //				strObject,
 //				NULL,
 //				1,
 //				NULL,
 //				NULL,
 //				INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE);
 //
 //			if (pHttpFile == NULL)
 //				break;
 //
 //			pHttpFile->SetOption(INTERNET_OPTION_PROXY_USERNAME, szUserName, _tcslen(szUserName) + 1);
 //			pHttpFile->SetOption(INTERNET_OPTION_PROXY_PASSWORD, szPassword, _tcslen(szPassword) + 1);
 //
 //			if (!pHttpFile->AddRequestHeaders(szHeaders))//��������ͷ
 //				break;
 //
 //			if (!pHttpFile->SendRequest())//�����ļ�����
 //				break;
 //
 //			if (!pHttpFile->QueryInfoStatusCode(dwFileStatus))//��ѯ�ļ�״̬
 //				break;
 //
 //			if ((dwFileStatus / 100) * 100 != HTTP_STATUS_OK)//����ļ�״̬����
 //				break;
 //
 //			CFile aFile;
 //			if (!aFile.Open(strFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
 //				break;
 //
 //			DWORD dwFileLen;
 //			DWORD dwWordSize = sizeof(dwFileLen);
 //			pHttpFile->QueryInfo(HTTP_QUERY_FLAG_NUMBER | HTTP_QUERY_CONTENT_LENGTH, &dwFileLen, &dwWordSize, NULL);
 //
 //			do
 //			{
 //				BYTE szBuffer[PATH_LEN] = { 0 };
 //				DWORD dwLen = pHttpFile->Read(szBuffer, PATH_LEN);//��������
 //				if (dwLen == 0)
 //					break;
 //
 //				aFile.Write(szBuffer, dwLen);
 //				dwDownloadSize += dwLen;
 //			} while (1);
 //
 //			aFile.Close();
 //			DWORD dw = 0;
 //			if (InternetQueryDataAvailable((HINTERNET)(*pHttpFile), &dw, 0, 0) && (dw == 0))
 //				bRes = TRUE;//���óɹ���־
 //
 //		} while (0);
 //
 //		if (pHttpFile != NULL)
 //			delete pHttpFile;
 //
 //		if (pHttpConnection != NULL)
 //			delete pHttpConnection;
 //
 //		//�ر�http����
 //		aInternetSession.Close();
 //	}
 //	//�쳣����
 //	catch (CInternetException* e)
 //	{
 //		TCHAR   szCause[MAX_PATH] = { 0 };
 //		//ȡ�ô�����Ϣ
 //		e->GetErrorMessage(szCause, MAX_PATH);
 //
 //		TRACE("internet exception:%s\n", szCause);//������Ϣд����־
 //
 //		e->Delete();//ɾ���쳣����
 //
 //		if (pHttpFile != NULL)//ɾ��http�ļ�����
 //			delete pHttpFile;
 //
 //		if (pHttpConnection != NULL)//ɾ��http���Ӷ���
 //			delete pHttpConnection;
 //
 //		aInternetSession.Close();//�ر�http����
 //	}
 //	catch (...)
 //	{
 //		if (pHttpFile != NULL)//ɾ��http�ļ�����
 //			delete pHttpFile;
 //
 //		if (pHttpConnection != NULL)//ɾ��http���Ӷ���
 //			delete pHttpConnection;
 //
 //		aInternetSession.Close();//�ر�http����
 //	}
 //
 //	return bRes;
 //}

//ת�����12λ�����֣�Ϊ�����
void NumToCH(CString &str)
{
	// str = "123456789111";
	 vector<CString>vecUnit;//��λ����ʮ��ǧ��
	// vector<CString>vecNum;//
	 vector<CString>VecSection;//1234,5678

	 vecUnit.push_back("ʮ");//0
	 vecUnit.push_back("��");//1
	 vecUnit.push_back("ǧ");//2
	 vecUnit.push_back("��");//3
	 vecUnit.push_back("��");//4
	 //1 ��֣�12|3456|78910
	int len = str.GetLength();//4
	double j = len;
	int iSection = (INT)ceil(j / 4);//ȡ��2���֣�Ȼ��ֳ������������߶�����������ѭ��
	if (str.GetLength() - 1 > 4)
	{
	
		CString strTemp = "";
		int posLeft = 0;
		int posRight = 0;
		for (int i = 0; i < iSection; i++)
		{ 
			//CString Mid( int nFirst, int nCount ) const;	����ߵ� nFirst+1 ���ַ���ʼ,��ȡ����  nCount ���ַ�
			if (i == 0)
			{
				posRight = len - 4 * (iSection - 1);
			}
			else posRight = 4;
			strTemp = str.Mid(posLeft, posRight);
			if (i == 0)
			{
				posLeft = posRight;
			}else posLeft += 4;
			VecSection.push_back(strTemp);
		}		
	}
	//2 ������
	CString strCombin;
	for (unsigned int j = 0; j < VecSection.size(); j++)
	{
		int len2 = VecSection[j].GetLength();//12|3456|78910

		for (int i = 0; i < len2-1; i++)
		{
			switch (i)
			{
			case 0:
				VecSection[j].Insert(3 * i + 1, vecUnit[len2 - 2]);
				break;
			case 1:
				VecSection[j].Insert(3 * i + 1, vecUnit[len2 - 3]);
				break;
			case 2:
				VecSection[j].Insert(3 * i + 1, vecUnit[len2 - 4]);
				break;
			default:
				break;
			}
		}
		if(VecSection.size() == 3 &&j==0)
			VecSection[j] += vecUnit[4];//���� �е���
		if (VecSection.size() == 3 && j == 1)
			VecSection[j] += vecUnit[3];//���� �е���
		if (VecSection.size() == 2 && j == 0)
			VecSection[j] += vecUnit[3];//��
		strCombin += VecSection[j];
	}
	str = strCombin;
	//2.	1(yao������Ϊһ��yi��
	int pos = str.Find("1");
	str.Replace("1", "һ");//ȫ���滻

	//3 ��һʮ2����,ȥ��һ
	if (len == 2 && !str.Find("һʮ"))
	{
		str.Replace("һ", "");
	}

}

//MD5����,ȡ�ӵ�8λ��ʼ��16λ����
CString MD5Encrypt_16(CString strTem)
{
	int i;
	char* encrypt = strTem.GetBuffer(strTem.GetLength());//CStirng תchar*
	unsigned char decrypt[16];

	MD5_CTX1 md5;
	MD5Init(&md5);
	MD5Update(&md5, (unsigned char *)encrypt, (int)strlen((char*)encrypt));//ֻ�Ǹ��м䲽��
	MD5Final(&md5, decrypt);//32λ

	char ss[20] = {};
	//printf("����ǰ��%s\n���ܺ�16λ��", encrypt);
	int j = 0;
	char p[200] = {};
	char  buffer[200];

	for (i = 4; i < 12; i++) {
		printf("%02x", decrypt[i]);
		sprintf(buffer, "%x", decrypt[i]); // C4996
		p[j++] = buffer[0];//16����ת�ַ���
		p[j++] = buffer[1];
	}//p������ӣ�decrypt������

	// 	DWORD dwd = HEXS((char*)decrypt);
	//printf("\n����ǰ��%s\n���ܺ�32λ��", encrypt);
// 	for (int i = 0; i < 16; i++) {
// 		printf("%02x", decrypt[i]);
// 	}
	// ��ʽ������ӡ�������ݵ�buffer
	CString strResult = "";
	strResult =decrypt;
	return strResult;
}

void findch(CString &strTemp)
{
	char *pChar = strTemp.GetBuffer();
	for (int m = 0; m < strTemp.GetLength(); m++)
	{
		if (pChar[m] >= 65 && pChar[m] <= 90)
		{
			strTemp += pChar[m];
		}
	}
}

std::string stows(std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char* _Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);
	wcstombs(_Dest, _Source, _Dsize);
	std::string result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}
std::wstring s2ws(const std::string& s)
{
	setlocale(LC_ALL, "chs");
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t* _Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest, _Source, _Dsize);
	std::wstring result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, "C");
	return result;
}


//�����ַ���
char* UpsideDown(char* a)
{
	char* p = a;
	char* q = a + strlen(a) - 1;
	for (; p < q; p++, q--)
	{
		char tmp = *p;
		*p = *q;
		*q = tmp;
	}
	printf("%s", a);
	return p;
}

#ifdef _UNICODE

void RemoveAllFiles(wstring wstrDir)
{
	if (wstrDir.empty())
	{
		return;
	}
	HANDLE hFind;
	WIN32_FIND_DATA findData;
	wstring wstrTempDir = wstrDir + (L"\\*");;
	hFind = FindFirstFile(wstrTempDir.c_str(), &findData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}
	do
	{
		// ����"."��".."�������
		if (wcscmp(findData.cFileName, L".") == 0 || wcscmp(findData.cFileName, L"..") == 0)
		{
			continue;
		}
		wstring wstrFileName;
		wstrFileName.assign(wstrDir);
		wstrFileName.append(L"\\");
		wstrFileName.append(findData.cFileName);
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)// �Ƿ���Ŀ¼
		{
			RemoveAllFiles(wstrFileName.c_str());
		}
		else
		{
			DeleteFile(wstrFileName.c_str());
		}
	} while (FindNextFile(hFind, &findData));
	FindClose(hFind);
	RemoveDirectory(wstrDir.c_str());
}



#endif


//1. ����ĳ��Ŀ¼�µ������ļ�
void listFiles1(const char* dir)
{
	using namespace std;
	HANDLE hFind;
	WIN32_FIND_DATA findData;
	LARGE_INTEGER size;
	hFind = FindFirstFile(dir, &findData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		cout << "Failed to find first file!\n";
		return;
	}
	do
	{
		// ����"."��".."������� 
		if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
			continue;
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)    // �Ƿ���Ŀ¼ 
		{
			cout << findData.cFileName << "\t<dir>\n";
		}
		else
		{
			size.LowPart = findData.nFileSizeLow;
			size.HighPart = findData.nFileSizeHigh;
			cout << findData.cFileName << "\t" << size.QuadPart << " bytes\n";
		}
	} while (FindNextFile(hFind, &findData));
	cout << "Done!\n";
}

//2 ����ĳ��Ŀ¼��������ļ�
void listFiles2(const char* dir)
{
	using namespace std;

	HANDLE hFind;
	WIN32_FIND_DATA findData;
	LARGE_INTEGER size;
	char dirNew[100];

	// ��Ŀ¼��ͨ���������������һ���ļ� 
	strcpy(dirNew, dir);
	strcat(dirNew, "\\*.*");

	hFind = FindFirstFile(dirNew, &findData);
	do
	{
		// �Ƿ����ļ��У��������Ʋ�Ϊ"."��".." 
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY != 0
			&& strcmp(findData.cFileName, ".") != 0
			&& strcmp(findData.cFileName, "..") != 0
			)
		{
			// ��dirNew����Ϊ��������Ŀ¼����������һ������ 
			strcpy(dirNew, dir);
			strcat(dirNew, "\\");
			strcat(dirNew, findData.cFileName);
			listFiles1(dirNew);
		}
		else
		{
			size.LowPart = findData.nFileSizeLow;
			size.HighPart = findData.nFileSizeHigh;
			cout << findData.cFileName << "\t" << size.QuadPart << " bytes\n";
		}
	} while (FindNextFile(hFind, &findData));

	FindClose(hFind);
}

string DectoHex(int num)
{
	if (num == 0)
		return "0";

	string res = "";
	string hex[16] = { "0", "1", "2", "3", "4", "5", "6", "7",
					  "8", "9", "a", "b", "c", "d", "e", "f" };

	unsigned int num2 = num;//����������ȫ��ת�����޷�������
	while (num2)
	{
		res = hex[num2 % 16] + res;//ȡ�༴�����λ
		num2 /= 16;
	}
	return "0x" + res;
}
int hexToDec(string hex) {
	int len = hex.size();
	int base = 1;
	int dec = 0;

	for (int i = len - 1; i >= 0; i--) {
		if (hex[i] >= '0' && hex[i] <= '9') {
			dec += (hex[i] - '0') * base;
			base *= 16;
		}
		else if (hex[i] >= 'A' && hex[i] <= 'F') {
			dec += (hex[i] - 'A' + 10) * base;
			base *= 16;
		}
	}

	return dec;
}

//exepath Ϊ����·��������·����
std::string GetSoftVersion(const char* exepath)
{
	std::string strVersionInfo;
	if (!exepath)
		return strVersionInfo;
	if (_access(exepath, 0) != 0)
		return strVersionInfo;

	HMODULE hDll = NULL;
	char szDbgHelpPath[MAX_PATH];

	sprintf_s(szDbgHelpPath, sizeof(szDbgHelpPath), "version.dll");
	hDll = ::LoadLibraryA(szDbgHelpPath);
	if (hDll == NULL)
	{
		return strVersionInfo;
	}

	typedef DWORD(WINAPI* func_GetFileVersionInfoSizeA)(LPCSTR, LPDWORD);
	func_GetFileVersionInfoSizeA p_GetFileVersionInfoSizeA =
		(func_GetFileVersionInfoSizeA)::GetProcAddress(hDll, "GetFileVersionInfoSizeA");


	typedef DWORD(WINAPI* func_GetFileVersionInfoA)(LPCSTR, DWORD, DWORD, LPVOID);
	func_GetFileVersionInfoA p_GetFileVersionInfoA =
		(func_GetFileVersionInfoA)::GetProcAddress(hDll, "GetFileVersionInfoA");


	typedef DWORD(WINAPI* func_VerQueryValueA)(LPCVOID, LPCSTR, LPVOID*, PUINT);
	func_VerQueryValueA p_VerQueryValueA =
		(func_VerQueryValueA)::GetProcAddress(hDll, "VerQueryValueA");


	if (p_GetFileVersionInfoSizeA == NULL
		|| p_GetFileVersionInfoA == NULL
		|| p_VerQueryValueA == NULL)
	{
		if (hDll)
		{
			FreeLibrary(hDll);
			hDll = NULL;
		}
		return strVersionInfo;
	}

	UINT infoSize = p_GetFileVersionInfoSizeA(exepath, 0);
	if (infoSize != 0) {
		strVersionInfo.resize(infoSize, 0);
		char* pBuf = NULL;
		pBuf = new char[infoSize];
		VS_FIXEDFILEINFO* pVsInfo;
		if (p_GetFileVersionInfoA(exepath, 0, infoSize, pBuf)) {
			if (p_VerQueryValueA(pBuf, "\\", (void**)&pVsInfo, &infoSize))
			{
				sprintf_s(pBuf, infoSize, "%d.%d.%d.%d",
					HIWORD(pVsInfo->dwFileVersionMS),
					LOWORD(pVsInfo->dwFileVersionMS),
					HIWORD(pVsInfo->dwFileVersionLS),
					LOWORD(pVsInfo->dwFileVersionLS));

				strVersionInfo = pBuf;
			}
		}
		delete[] pBuf;
	}

	if (hDll)
	{
		FreeLibrary(hDll);
	}
	return strVersionInfo;
}