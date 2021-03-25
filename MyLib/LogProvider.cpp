#include "stdafx.h"

#include "LogProvider.h"

#if defined(_WIN32) || defined(WIN32)

#include <Shlwapi.h>
#include <direct.h>
#pragma comment(lib, "Shlwapi.lib")

//////////////////////////////////////////////////////////////////////////
//- KKLogObject
KKLogObject::KKLogObject(const std::string &logFileName /* = */ )
	: mLogFileName(logFileName)
{
	if (!::PathFileExistsA("log"))
		_mkdir("log");
	std::string logRlvFileName("log\\");
	logRlvFileName += mLogFileName + ".log";
	mFOut.open(logRlvFileName.c_str(), std::ios::app);
}

KKLogObject::~KKLogObject()
{
	mFOut.flush();
	mFOut.close();
}

const std::string & KKLogObject::GetLogFileName() const
{
	return mLogFileName;
}

void KKLogObject::LogTrace(const std::string &strLogText)
{
	static std::string logText("");
	logText = std::string("[ ") + GetCurrentTimeString() + " ] Trace > " + strLogText;
	OutputLogText(mFOut, logText);
}

void KKLogObject::LogInfo(const std::string &strLogText)
{
	static std::string logText("");
	logText = std::string("[ ") + GetCurrentTimeString() + " ] Info  > " + strLogText;
	OutputLogText(mFOut, logText);
}

void KKLogObject::LogError(const std::string &strLogText)
{
	static std::string logText("");
	logText = std::string("[ ") + GetCurrentTimeString() + " ] Error > " + strLogText;
	OutputLogText(mFOut, logText);
}

void KKLogObject::LogWarn(const std::string &strLogText)
{
	static std::string logText("");
	logText = std::string("[ ") + GetCurrentTimeString() + " ] Warn  > " + strLogText;
	OutputLogText(mFOut, logText);
}

std::string KKLogObject::GetCurrentTimeString()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	char pszFileName[50] = "\0";
	sprintf_s(pszFileName, 50, "%d-%02d-%02d %02d:%02d:%02d %03d", 
		st.wYear,
		st.wMonth,
		st.wDay,
		st.wHour,
		st.wMinute,
		st.wSecond,
		st.wMilliseconds); 
	return std::string(pszFileName);
}

void KKLogObject::OutputLogText(std::ofstream &fout, const std::string &logText)
{
	fout << logText.c_str() << "\r\n";
	fout.flush();
#if defined(_DEBUG) || defined(DEBUG)
	printf("%s\r\n", logText.c_str());
	::OutputDebugStringA((LPCSTR)(std::string(logText + "\r\n")).c_str());
#else
	::OutputDebugStringA((LPCSTR)logText.c_str());
#endif
}

//////////////////////////////////////////////////////////////////////////
//- KKLogObjectPool
KKLogObjectPool::KKLogObjectPool()
{
	
}

KKLogObjectPool::~KKLogObjectPool()
{
	this->ClearLogObjects();
}

KKLogObjectPool & KKLogObjectPool::GetLogObjectPool()
{
	static KKLogObjectPool logObjPool;
	return logObjPool;
}

KKLogObject * KKLogObjectPool::GetLogObject(const std::string &objId)
{
	LogObjectPoolIter iter = mLogObjectPool.find(objId);
	if (mLogObjectPool.end() != iter)
		return iter->second;
	KKLogObject *lpLogObj = new KKLogObject(objId);
	mLogObjectPool[objId] = lpLogObj;
	return lpLogObj;
}

bool KKLogObjectPool::IsLogObjectExisted(const std::string &objId)
{
	LogObjectPoolIter iter = mLogObjectPool.find(objId);
	return mLogObjectPool.end() != iter;
}

void KKLogObjectPool::ClearLogObjects()
{
	KKLogObject *lpLogObj(NULL);
	for (LogObjectPoolIter iter = mLogObjectPool.begin(); iter != mLogObjectPool.end(); ++iter)
	{
		lpLogObj = iter->second;
		delete lpLogObj;
	}
	mLogObjectPool.clear();
}

//////////////////////////////////////////////////////////////////////////
//- KKLogProvider
void KKLogProvider::LogTrace(const std::string &logText, const std::string &filename /* = KKCommonLogFileName */)
{
	KKLogObject *lpLogTraceObj(NULL);
	if (filename.empty())
		lpLogTraceObj = KKLogObjectPool::GetLogObjectPool().GetLogObject(KKCommonLogFileName);
	else
		lpLogTraceObj = KKLogObjectPool::GetLogObjectPool().GetLogObject(filename);
	lpLogTraceObj->LogTrace(logText);
}

void KKLogProvider::LogInfo(const std::string &logText, const std::string &filename /* = KKCommonLogFileName */)
{
	KKLogObject *lpLogInfoObj(NULL);
	if (filename.empty())
		lpLogInfoObj = KKLogObjectPool::GetLogObjectPool().GetLogObject(KKCommonLogFileName);
	else
		lpLogInfoObj = KKLogObjectPool::GetLogObjectPool().GetLogObject(filename);
	lpLogInfoObj->LogInfo(logText);
}

void KKLogProvider::LogError(const std::string &logText, const std::string &filename /* = KKCommonLogFileName */)
{
	KKLogObject *lpLogErrorObj(NULL);
	if (filename.empty())
		lpLogErrorObj = KKLogObjectPool::GetLogObjectPool().GetLogObject(KKCommonLogFileName);
	else
		lpLogErrorObj = KKLogObjectPool::GetLogObjectPool().GetLogObject(filename);
	lpLogErrorObj->LogError(logText);
}

void KKLogProvider::LogWarn(const std::string &logText, const std::string &filename /* = KKCommonLogFileName */)
{
	KKLogObject *lpLogWarnObj(NULL);
	if (filename.empty())
		lpLogWarnObj = KKLogObjectPool::GetLogObjectPool().GetLogObject(KKCommonLogFileName);
	else
		lpLogWarnObj = KKLogObjectPool::GetLogObjectPool().GetLogObject(filename);
	lpLogWarnObj->LogWarn(logText);
}

#ifndef KKMaxLogLength
#	define KKMaxLogLength         (16 * 1024 + 1)
#endif
char g_szLogTextBuff[KKMaxLogLength] = "\0";

#endif