#pragma once

#ifndef _MYLIB_H_  
#define _MYLIB_H_  

#include "stdafx.h"
#include <iostream>
#include <io.h>
#include<vector>

#include "tinyzipinterface.h"
#pragma comment( lib, "tinyzip.lib" )

#define KILOBYTE 1024
using namespace std;

#include "PCInfo.h"
CString CheckIP(void);
CString GetMacAddress(UINT iType);

// 获取CPU序列号	
bool ObtainCPUID(char *pCpuId);

// 获取C盘序列号
bool ObtainHDID(char *pHdId);

/************************************************************************\
* 获得程序根目录下的文件的绝对路径										*
* 入参：文件夹的绝对路径，如D:\\1\\	1.exe								*
* 返回值： 文件的绝对路径												*
\************************************************************************/
CString  getFullPath(CString strTempPath);

/************************************************************************\
* 获得程序根目录的绝对路径												*
* 入参：文件夹的绝对路径，如D:\\1\\										*
* 返回值： 根目录的绝对路径												*
\************************************************************************/
CString GetAppPathW();

/************************************************************************\
* 判断文件是否存在														*
* 入参：输入文件的绝对路径												*
* 返回值： True 存在，False 不存在										*
\************************************************************************/
BOOL CheckFileExist(CString strFilePath);

/************************************************************************\
* 删除包括该文件夹和内部所有的文件										*
* 入参：文件夹的绝对路径，如D:\\1\\										*
* 返回值： True 成功， False 失败										*
\************************************************************************/
bool RemoveDir(const char* szFileDir);

//删除所有文件(Unicode环境下）
void RemoveAllFiles(wstring wstrDir);

// 拷贝文件
BOOL copyFile(LPCTSTR lpExistingFileName,LPCTSTR lpNewFileName, BOOL bFailIfExists)
{
	return CopyFile(lpExistingFileName, lpNewFileName, bFailIfExists);
}

/************************************************************************\
* 迁移文件，如果新路径中含有同名文件，则不会移动						*
* 入参：旧全路径，新全路径，以及旧路径下的要转移的文件类型，如 *,jpg,mp4*
* 返回值： 无															*
\************************************************************************/
void RemoveFileToOtherPath(const char* pathOld, const char* pathNew, const char * type);

/************************************************************************\
* 获得今天是星期几														*
* 入参：无																*
* 返回值： 返回0-6，周一=0，周日=6										*
\************************************************************************/
int GetWeekDay();

/************************************************************************\
* 修改系统的音量														*
* 入参：音量的值，范围0-100	；输入-2 恢复静音；输入-1，静音				*
* 返回值： True 成功， False 失败										*
\************************************************************************/
bool SetVolumeLevel(int level);

/************************************************************************\
* 判断是否是json报文，是否符合规范										*
* 入参：json报文														*
* 返回值： True是， False 否											*
\************************************************************************/
bool IsJsonData(std::string strData);

/************************************************************************\
* 将文件从GBK转成UTF-8格式，平台大多需要utf8							*
* 入参：传的数据														*
* 返回值： 无															*
\************************************************************************/
void ConvertGbkToUtf8(CString &strConvert);

/************************************************************************\
* 将文件从UTF-8转成GBK格式，c程序里用GBK，utf8显示乱码					*
* 入参：传的数据utf8数据，												*
* 返回值： 无															*
\************************************************************************/
void  ConvertUtf8ToGbk(CString& strUtf8);

/************************************************************************\
* 将Unicode字符串转换为Ansicode字符串									*
* 入参：source 为宽字节，dest 为多字节									*
* 返回值： 无															*
\************************************************************************/
void ConvertUnicodeToAnsi(wchar_t* source, char* dest);

/************************************************************************\
* 将Ansicode字符串转换为Unicode字符串									*
* 入参：source 为多字节，dest 为宽字节									*
* 返回值： 无															*
\************************************************************************/
void ConvertAnsiToUnicode(wchar_t* source, char* dest);

/************************************************************************\
* 传入图片路径，进行base64加密											*
* 入参：传入图片路径													*
* 返回值： base64加密位数据												*
\************************************************************************/
CString Base64EncodePic(CString strPath);

/************************************************************************\
* 重启电脑																*
* 入参：	无															*
* 返回值： 无															*
\************************************************************************/
void OnClose();

/************************************************************************\
* 给定一个文件目录path，然后找到其中所有（包括其子目录里）的文件，将文件名放入files中,依赖io.h																*
* 入参：文件的绝对路径，和一个存放文件名的容器，						*
* 返回值： 无															*
\************************************************************************/
void getFloderFiles(string path, vector<string>& files);

/************************************************************************\
* 分割字符串															*
* 入参：需要分割的字符串，分隔符号，如“|”								*
* 返回值： 分割好的容器													*
\************************************************************************/
vector<CString> SplitString(CString &strContent, const string &seperator);

/************************************************************************\
* 读取文件																*
* 入参：读取的内容，读取文件名的绝对路径								*
* 返回值： 成功True 失败false											*
\************************************************************************/
BOOL ReadFileContent(CString &strContent, CString pFileName);
// 读取文件内容
CString ReadFileContent(const char* pFile);

/************************************************************************\
* 写入文件																*
* 入参：写入的内容，写入文件名的绝对路径								*
* 返回值： 成功True 失败false											*
\************************************************************************/
BOOL WriteFileCotent(CString strContent, CString pFileName);


typedef enum 
{	
	MY_DATE_LONG,		//0	2020-09-11 08:55:44
	MY_DAY_NORMAL,		//1	20200911		YYYYMMDD
	MY_TIME_NORMAL,		//2	085628			HHMMSS
	MY_DATE_NORMAL,		//3	20200911085638	YYYYMMDDHHMMSS
	MY_DAY_SHORT,		//4	0911			MMDD
	MY_DAY_LONG,		//5	2020-09-11
	MY_TIME_LONG,		//6	08:57:03
	MY_TIME_SHORT,		//7	200911085711	YYMMHHMMSS
	MY_DATE_LONG2,		//8	202009			YYYYMM
	MY_DATE_LONG3		//9	0911085726		MMHHMMSS
}MY_TIME_TYPE;

CString  GetCurTime(int nType);

//修改时间，将YYYYMMDDHHMMSS 变成YYYY-MM-DD HH:MM:SS
CString changeTime(CString strTime);

/************************************************************************\
* 修改g_configPath的值，默认为“config\\config.ini”					*
* 入参：g_configPath的新路劲											*
* 返回值： 无															*
\************************************************************************/
void ModifyConfigpath(CString strPath);

/************************************************************************\
* 往g_configPath，路径中写数据											*
* 入参：[index]  键名=键值												*
* 返回值： 成功True 失败false											*
\************************************************************************/
void WriteContentToCfg(CString strIndex, CString strAppName, LPCSTR strModifyMsg);

/************************************************************************\
* 读取g_configPath 数据													*
* 入参：[index]  键名=键值												*
* 返回值： 键值															*
\************************************************************************/
CString GetContentFromCfg(CString strIndex, CString strAppName);

/************************************************************************\
* 读取g_configPath 数据,int类型数据										*
* 入参：[index]  键名=键值												*
* 返回值： 键值															*
\************************************************************************/
UINT GetIntgFromCfg(CString strAppName, CString strKeyName);

/****************************************************************************
函数名称: hex_to_str
函数功能: 十六进制转字符串
输入参数: ptr 字符串数组 ，buf 十六进制数组 len 十六进制字符串的长度。
输出参数: 无
*****************************************************************************/
static void hex_to_str(char *ptr, unsigned char *buf, int len);

/****************************************************************************
函数名称: str_to_hex
函数功能: 字符串转换为十六进制
输入参数: string 字符串数组 ， cbuf 十六进制数组 ， len 字符串的长度。
输出参数: 无
*****************************************************************************/
static int str_to_hex(char *string, unsigned char *cbuf, int len);

/****************************************************************************
函数名称: UrlEncodeUtf8
函数功能: 将字符串以URL编码，用于编码处理
输入参数: pszUrl 字符串 nEncodeLen 
输出参数: pszEncode 保存转换好的字符串
*****************************************************************************/
int UrlEncodeUtf8(LPCSTR pszUrl, LPSTR pszEncode, int nEncodeLen);

/****************************************************************************
函数名称: GetTimeDifference
函数功能: 获得输入时间与当前时间的时间差，返回有秒和分钟两种形式
输入参数: 输入时间，格式为%d-%d-%d %d:%d:%d  
输出参数: 默认输出为分钟，iSReturnSec改为True后输出为秒
*****************************************************************************/
int GetTimeDifference(CString strTime, BOOL iSReturnSec = FALSE);

/****************************************************************************
函数名称: replace_all
函数功能: 将素有的old_value都换成new_value,区别于下面的，如果12212-》22211,即替换后，里面还是有12的话，也继续替换，直到没有为止
输入参数: str=“12212”，old_value=“12”，new_value="21"
输出参数: 替换后的str，str本身也可以拿来直接使用
*****************************************************************************/
string&   replace_all(string&   str, const   string&   old_value, const   string&   new_value);

/****************************************************************************
函数名称: replace_all_distinct
函数功能: 将素有的old_value都换成new_value,区别于下面的，如果12212-》21221,等同于自带的replace，只轮询一次
输入参数: str=“12212”，old_value=“12”，new_value="21"
输出参数:  替换后的str，str本身也可以拿来直接使用
*****************************************************************************/
string&   replace_all_distinct(string&   str, const   string&   old_value, const   string&   new_value);

/****************************************************************************
函数名称: 解压函数
函数功能: 解压压缩文件，
输入参数: 压缩文件的路径，解压后的路径
输出参数:  非0就失败，1就成功
*****************************************************************************/
DWORD UnZIPFile(CString strTargetFile, CString strResourceFullPath);

/****************************************************************************
函数名称: 排除掉容器里重复的元素，和为""的值,类模版函数，可以适用于
函数功能: 解压压缩文件，
输入参数: 压缩文件的路径，解压后的路径
输出参数:  非0就失败，1就成功
*****************************************************************************/
template<typename T>
//排除掉容器里重复的元素，和为""的值
void deduplication(T& c)
{
	//①首先将vector排序
	sort(c.begin(), c.end());
	//②然后使用unique算法,unique返回值是重复元素的开始位置。
	T::iterator new_end = unique(c.begin(), c.end());//"删除"相邻的重复元素
													 //③最后删除后面的那段重复部分
	c.erase(new_end, c.end());//删除(真正的删除)重复的元素

	for (unsigned int i = 0; i < c.size(); i++)
	{
		if (c[i] == "")
		{
			c.erase(c.begin() + i);
			break;
		}
	}
}

/****************************************************************************
函数名称: 截屏
函数功能: 获得当前页面的画面，保存到ScreenShot 文件夹内
输入参数:
输出参数:  图片的绝对路径
*****************************************************************************/
CString ScreenShot(void);

//转换最多12位的数字，为中文念法;（可能有bug）
void NumToCH(CString &str);

//MD5加密,取从第8位开始的16位数字
CString MD5Encrypt_16(CString strTem);

void findch(CString &strTemp);


std::string stows(std::wstring& ws);
std::wstring s2ws(const std::string& s);

//倒置字符串
char* UpsideDown(char* a);

int hexToDec(string hex);
string DectoHex(int num);

//1. 遍历某个目录下的所有文件
void listFiles1(const char* dir);
//2 遍历某个目录里的所有文件
void listFiles2(const char* dir);

//exepath 为程序路径（绝对路径）
std::string GetSoftVersion(const char* exepath)
#endif