#include "stdafx.h"
#include "MyLib.h"

#include "MyMD5.h"
//修改音量头文件
#include <windows.h> 
#include <mmdeviceapi.h> 
#include <endpointvolume.h>
#include <audioclient.h>

#include "Base64.h"
//截屏头文件
#include "MakePNG.h"
CString g_configPath = "config//config.ini";
//获得绝对路径
CString getFullPath(CString strTempPath)
{
	CString strEngineeringPath;
	TCHAR szPath[MAX_PATH] = { 0 };
	if (GetModuleFileName(NULL, szPath, MAX_PATH))
	{
		TCHAR *pChr = _tcsrchr(szPath, _T('\\'));
		pChr++;
		*pChr = _T('\0');
		//(_tcsrchr(szPath, _T('\\')))[1] = 0;//三句可以由这一句替代
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

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/// 判断文件是否存在
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

//删文件夹和内容
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

//迁移文件，入参为旧全路径，新全路径，以及旧路径下的路文件类型，如jpg,mp4,*（如果新路径中含有同名文件，则不会移动）
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

//获得今天是星期几，返回0-6，周一=0，周日=6
int GetWeekDay()
{
	/*
	time_t是一个存储时间信息的long int
	time(&rawtime) 将系统时间存入rawtime这个time_t中
	struct tm *timeinfo 里tm是一个存时间信息的结构体 timeinfo是指向一个这个结构体的指针
	timeinfo=localtime(&rawtime) 将之前time()得到的信息转存为struct tm内容
	*/
	struct tm *ptr;
	time_t lt;
	lt = time(NULL);
	ptr = localtime(&lt);
	//mlgb,系统返回0为周日，平台的人才 返回0为周一，怎么办呢改呗.
	int iSysTime = ptr->tm_wday;
	int iPFTime = iSysTime - 1;
	if (iPFTime < 0) iPFTime = 6;

	return  iPFTime;
}

//修改时间，将YYYYMMDDHHMMSS 变成YYYY-MM-DD HH:MM:SS
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

//修改音量，输入音量的值
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

//判断是是否是json报文
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

//转gbk成utf8
void ConvertGbkToUtf8(CString &strConvert)
{
	//该函数映射一个多字节到一个宽字符（unicode）的字符串。
	/*int MultiByteToWideChar(
　　UINT CodePage,
　　DWORD dwFlags,
　　LPCSTR lpMultiByteStr,
　　int cchMultiByte,
　　LPWSTR lpWideCharStr,
　　int cchWideChar);*/

  //注意：以下n和len的值大小不同,n是按字符计算的；len是按字节计算的，一个汉字占两个字节
	//  CString str = _T("D://校内项目//QQ.bmp");
	int n = strConvert.GetLength();     // n = 14(str的), len = 18(str的)

	//调用MultiByteToWideChar()函数，设置cchWideChar参数为0（用以获取转换所需的接收缓冲区大小）；
	//为宽字节字符数组申请空间，数组大小为按字节计算的多字节字符大小
	int len = MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strConvert, -1, NULL, 0);
	// 获取输入缓存的大小，作为cchMultiByte的值；
	//			（这样做是为了节省空间，也可以给cchMultiByte取值-1（字符串需要以空字符结尾，否则会出错））

	// 分配足够的内存块，用于存放转换后的Unicode字符串；该内存块的大小由前面对cchWideChar()函数的返回值来决定；
	//			（也可以用别的方法，但该方法更节省内存）
	wchar_t * wszUtf8 = new wchar_t[len];
	memset(wszUtf8, 0, len);
	//再次调用MultiByteToWideChar()函数，这次将缓存的地址作为lpWideCharStr,参数来传递，
	//并传递第一次调用MultiByteToWideChar()函数时的返回值作为cchWideChar参数的值；
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strConvert, -1, wszUtf8, len);
	/************************************************************************************************************************/

	//从宽字节（unicode）转为窄字节字符串(utf-8)
	/*int WideCharToMultiByte(
　　UINT CodePage,
　　DWORD dwFlags,
　　LPCWSTR lpWideCharStr,
　　int cchWideChar,
　　LPSTR lpMultiByteStr,
　　int cchMultiByte,
　　LPCSTR lpDefaultChar,
　　LPBOOL pfUsedDefaultChar);*/
	len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = new char[len + 1];
	memset(szUtf8, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, szUtf8, len, NULL, NULL);
	strConvert = szUtf8;
	delete[] szUtf8;
	delete[] wszUtf8;
}

//转utf8成gbk
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

// 将Unicode字符串转换为Ansicode字符串
void ConvertUnicodeToAnsi(wchar_t* source, char* dest)
{
	int len = 0;
	len = WideCharToMultiByte(CP_ACP, 0, source, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, source, -1, dest, len, NULL, NULL);
}

// 将Ansicode字符串转换为Unicode字符串
void ConvertAnsiToUnicode(char* source, wchar_t* dest)
{
	int len = 0;
	len = MultiByteToWideChar(CP_ACP, 0, source, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, source, -1, dest, len);
}

//传入图片路径，进行base64加密	
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

//给定一个文件目录path，然后找到其中所有（包括其子目录里）的文件名
 void  getFloderFiles(string path, vector<string>& files)
 {
 	//文件句柄  
 	long   hFile = 0;
 	//文件信息  
 	struct _finddata_t fileinfo;
 	string p;
 	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
 	{
 		do
 		{
 			//如果是目录,迭代之  
 			//如果不是,加入列表  
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
 
 //重启函数
 void OnClose()
 {
	 // TODO: 在此添加消息处理程序代码和/或调用默认值
	 // 	if (g_bIsRunAgain)
	 // 	{
	 //得到当前程序的路径；
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
	 //定义变量
	 wchar_t* pWString = NULL;
	 char* pString = NULL;
	 char* pResult = NULL;

	 do
	 {
		 if (pszUrl == NULL)
			 break;

		 //先将字符串由多字节转换成UTF-8编码  
		 int nLength = MultiByteToWideChar(CP_ACP, 0, pszUrl, -1, NULL, 0);

		 //分配Unicode空间  
		 pWString = new wchar_t[nLength + 1];
		 if (pWString == NULL)
			 break;

		 memset(pWString, 0, (nLength + 1) * sizeof(wchar_t));
		 //先转换成Unicode
		 MultiByteToWideChar(CP_ACP, 0, pszUrl, -1, pWString, nLength);

		 //分配UTF-8空间
		 nLength = WideCharToMultiByte(CP_UTF8, 0, pWString, -1, NULL, 0, NULL, NULL);
		 pString = new char[nLength + 1];
		 if (pString == NULL)
			 break;

		 memset(pString, 0, nLength + 1);
		 //Unicode转到UTF-8
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

			 if (c > 0x20 && c < 0x7f)// 数字或字母
			 {
				 *pTmp++ = c;
			 }
			 else if (c == 0x20)// 包含空格  
			 {
				 *pTmp++ = '%';
				 *pTmp++ = hex[c / 16];
				 *pTmp++ = hex[c % 16];
			 }
			 else// 进行编码
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

//十六进制转字符串
 static void hex_to_str(char *ptr, unsigned char *buf, int len)
 {
	 for (int i = 0; i < len; i++)
	 {
		 sprintf(ptr, "%02x", buf[i]);
		 ptr += 2;
	 }
 }

//字符串转换为十六进制
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

// 分割字符串
 vector<CString> SplitString(CString &strContent, const string &seperator)
 {
	 vector<CString> result;
	 typedef string::size_type string_size;
	 string_size i = 0;
	 string s = strContent;

	 while (i != s.size()) {
		 //找到字符串中首个不等于分隔符的字母；
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

		 //找到又一个分隔符，将两个分隔符之间的字符串取出；
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

 //读取文件
 BOOL ReadFileContent(CString &strContent, CString pFileName)
 {
	 CFile file;
	 CFileStatus status;
	 if (FALSE == CheckFileExist(pFileName))
	 {
		 return FALSE;
	 }
	 //1 打开
	 if (file.Open(pFileName, CFile::modeReadWrite) == FALSE &&
		 file.Open(pFileName, CFile::modeCreate | CFile::modeReadWrite) == FALSE)
	 {
		 return FALSE;
	 }
	 file.GetStatus(status);
	 //2 判空
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

 //读取文件内容
 CString ReadFileContent(const char* pFile)
 {
	 CStdioFile file;
	 CString szLine = "";
	 CString strText = "";
	 if (!file.Open(pFile, CFile::modeRead))
	 {
		 return "";
	 }
	 //逐行读取字符串
	 while (file.ReadString(szLine))
	 {
		 strText += szLine;
	 }
	 file.Close();
	 return strText;
 }

 //保存文件
 BOOL WriteFileCotent(CString strContent, CString pFileName)
 {
	 CFile filenew(pFileName, CFile::modeCreate | CFile::modeWrite);
	 CString strUtf = strContent;
	 ConvertGbkToUtf8(strUtf);
	 filenew.Write(strUtf.GetBuffer(0), strUtf.GetLength());
	 filenew.Close();
	 return TRUE;
 }

 //获取时间
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

 //循环替换
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

 //一次性替换
 string&   replace_all_distinct(string&   str, const   string&   old_value, const   string&   new_value)
 {
	 for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
		 if ((pos = str.find(old_value, pos)) != string::npos)
			 str.replace(pos, old_value.length(), new_value);
		 else   break;
	 }
	 return   str;
 }

 //解压
 DWORD UnZIPFile(CString strTargetFile,CString strResourceFullPath)
 {
	 DWORD  nResult = _unzip(strTargetFile, strResourceFullPath);
	 return nResult;
 }

  //屏幕截图,返回图片的路径
  CString ScreenShot(void)
  {
 	 CWnd *pDesktop = CWnd::FromHandle(GetDesktopWindow());
 	 CDC *pDC = pDesktop->GetDC();
 	 CRect rect;
 
 	 //获取窗口的大小  
 	 pDesktop->GetClientRect(&rect);
 
 	 //保存到的文件名
 	 CString strFileName(GetAppPathW());
 	 strFileName += _T("ScreenShot\\");
 	 CreateDirectory((LPCTSTR)strFileName, NULL);
 	 CTime t = CTime::GetCurrentTime();
 	 CString tt = t.Format("%Y%m%d_%H%M%S");
 	 strFileName += tt;
 	 strFileName += _T(".png");

 	 //保存为PNG
 	 CMakePNG MakePNG;
 	 MakePNG.MakePNG(pDC->m_hDC, rect, strFileName);
	 ::ReleaseDC(GetDesktopWindow(), pDC->m_hDC);
 	 return strFileName;
  }


// 下载文件并保存为新文件名,依赖MFC等头文件
 //BOOL HTTP_Download(CString strURL, CString strFilePath)
 //{
 //	BOOL bRes = FALSE;
 //#define PATH_LEN 1024
 //	//建立http连接
 //	TCHAR szUserName[MAX_PATH] = { 0 };
 //	TCHAR szPassword[MAX_PATH] = { 0 };
 //	_tcscpy(szUserName, "");
 //	_tcscpy(szPassword, "");
 //
 //	const TCHAR szHeaders[] = _T("Accept: */*\r\nUser-Agent:  Mozilla/4.0 (compatible; MSIE 5.00; Windows 98)\r\n");    //协议
 //
 //	CInternetSession    aInternetSession;        //一个会话
 //	CHttpConnection*    pHttpConnection = NULL;    //链接
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
 //	//分解URL
 //	if (AfxParseURL(strURL, dwServiceType, strServer, strObject, nPort))
 //	{
 //		//如果服务类型是HTTP下载
 //		if (dwServiceType != AFX_INET_SERVICE_HTTP && dwServiceType != AFX_INET_SERVICE_HTTPS)
 //		{
 //			//返回成功
 //			return bRes;
 //		}
 //	}
 //
 //	try
 //	{
 //		pHttpConnection = aInternetSession.GetHttpConnection(strServer, nPort);
 //		do
 //		{
 //			//如果失败则线程退出
 //			if (pHttpConnection == NULL)
 //				break;
 //
 //			//取得HttpFile对象
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
 //			if (!pHttpFile->AddRequestHeaders(szHeaders))//增加请求头
 //				break;
 //
 //			if (!pHttpFile->SendRequest())//发送文件请求
 //				break;
 //
 //			if (!pHttpFile->QueryInfoStatusCode(dwFileStatus))//查询文件状态
 //				break;
 //
 //			if ((dwFileStatus / 100) * 100 != HTTP_STATUS_OK)//如果文件状态正常
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
 //				DWORD dwLen = pHttpFile->Read(szBuffer, PATH_LEN);//接收数据
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
 //				bRes = TRUE;//设置成功标志
 //
 //		} while (0);
 //
 //		if (pHttpFile != NULL)
 //			delete pHttpFile;
 //
 //		if (pHttpConnection != NULL)
 //			delete pHttpConnection;
 //
 //		//关闭http连接
 //		aInternetSession.Close();
 //	}
 //	//异常处理
 //	catch (CInternetException* e)
 //	{
 //		TCHAR   szCause[MAX_PATH] = { 0 };
 //		//取得错误信息
 //		e->GetErrorMessage(szCause, MAX_PATH);
 //
 //		TRACE("internet exception:%s\n", szCause);//错误信息写入日志
 //
 //		e->Delete();//删除异常对象
 //
 //		if (pHttpFile != NULL)//删除http文件对象
 //			delete pHttpFile;
 //
 //		if (pHttpConnection != NULL)//删除http连接对象
 //			delete pHttpConnection;
 //
 //		aInternetSession.Close();//关闭http连接
 //	}
 //	catch (...)
 //	{
 //		if (pHttpFile != NULL)//删除http文件对象
 //			delete pHttpFile;
 //
 //		if (pHttpConnection != NULL)//删除http连接对象
 //			delete pHttpConnection;
 //
 //		aInternetSession.Close();//关闭http连接
 //	}
 //
 //	return bRes;
 //}

//转换最多12位的数字，为中文念法
void NumToCH(CString &str)
{
	// str = "123456789111";
	 vector<CString>vecUnit;//单位，个十百千万
	// vector<CString>vecNum;//
	 vector<CString>VecSection;//1234,5678

	 vecUnit.push_back("十");//0
	 vecUnit.push_back("百");//1
	 vecUnit.push_back("千");//2
	 vecUnit.push_back("万");//3
	 vecUnit.push_back("亿");//4
	 //1 拆分，12|3456|78910
	int len = str.GetLength();//4
	double j = len;
	int iSection = (INT)ceil(j / 4);//取得2部分，然后分成两个容器或者多个，下面进行循环
	if (str.GetLength() - 1 > 4)
	{
	
		CString strTemp = "";
		int posLeft = 0;
		int posRight = 0;
		for (int i = 0; i < iSection; i++)
		{ 
			//CString Mid( int nFirst, int nCount ) const;	从左边第 nFirst+1 个字符开始,获取后面  nCount 个字符
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
	//2 加中文
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
			VecSection[j] += vecUnit[4];//亿万 中的亿
		if (VecSection.size() == 3 && j == 1)
			VecSection[j] += vecUnit[3];//亿万 中的万
		if (VecSection.size() == 2 && j == 0)
			VecSection[j] += vecUnit[3];//万
		strCombin += VecSection[j];
	}
	str = strCombin;
	//2.	1(yao）发声为一（yi）
	int pos = str.Find("1");
	str.Replace("1", "一");//全部替换

	//3 有一十2这种,去掉一
	if (len == 2 && !str.Find("一十"))
	{
		str.Replace("一", "");
	}

}

//MD5加密,取从第8位开始的16位数字
CString MD5Encrypt_16(CString strTem)
{
	int i;
	char* encrypt = strTem.GetBuffer(strTem.GetLength());//CStirng 转char*
	unsigned char decrypt[16];

	MD5_CTX1 md5;
	MD5Init(&md5);
	MD5Update(&md5, (unsigned char *)encrypt, (int)strlen((char*)encrypt));//只是个中间步骤
	MD5Final(&md5, decrypt);//32位

	char ss[20] = {};
	//printf("加密前：%s\n加密后16位：", encrypt);
	int j = 0;
	char p[200] = {};
	char  buffer[200];

	for (i = 4; i < 12; i++) {
		printf("%02x", decrypt[i]);
		sprintf(buffer, "%x", decrypt[i]); // C4996
		p[j++] = buffer[0];//16进制转字符串
		p[j++] = buffer[1];
	}//p数组可视，decrypt不可视

	// 	DWORD dwd = HEXS((char*)decrypt);
	//printf("\n加密前：%s\n加密后32位：", encrypt);
// 	for (int i = 0; i < 16; i++) {
// 		printf("%02x", decrypt[i]);
// 	}
	// 格式化并打印各种数据到buffer
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


//倒置字符串
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
		// 忽略"."和".."两个结果
		if (wcscmp(findData.cFileName, L".") == 0 || wcscmp(findData.cFileName, L"..") == 0)
		{
			continue;
		}
		wstring wstrFileName;
		wstrFileName.assign(wstrDir);
		wstrFileName.append(L"\\");
		wstrFileName.append(findData.cFileName);
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)// 是否是目录
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


//1. 遍历某个目录下的所有文件
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
		// 忽略"."和".."两个结果 
		if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
			continue;
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)    // 是否是目录 
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

//2 遍历某个目录里的所有文件
void listFiles2(const char* dir)
{
	using namespace std;

	HANDLE hFind;
	WIN32_FIND_DATA findData;
	LARGE_INTEGER size;
	char dirNew[100];

	// 向目录加通配符，用于搜索第一个文件 
	strcpy(dirNew, dir);
	strcat(dirNew, "\\*.*");

	hFind = FindFirstFile(dirNew, &findData);
	do
	{
		// 是否是文件夹，并且名称不为"."或".." 
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY != 0
			&& strcmp(findData.cFileName, ".") != 0
			&& strcmp(findData.cFileName, "..") != 0
			)
		{
			// 将dirNew设置为搜索到的目录，并进行下一轮搜索 
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

	unsigned int num2 = num;//无论正负，全部转换成无符号整型
	while (num2)
	{
		res = hex[num2 % 16] + res;//取余即是最低位
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

//exepath 为程序路径（绝对路径）
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