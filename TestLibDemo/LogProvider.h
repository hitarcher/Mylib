//**********************************************************************/
//* 作者：Jacc.Kim
//* 日期：2013-03-11
//* 描述：一个通用类型的Log日志报告
//* 备注：只希望在WIN平台下使用
//**********************************************************************/
#if (defined(_WIN32) || defined(WIN32)) && (_MSC_VER > 1000)
#	pragma once
#endif

#ifndef __LogProvider_H__2013_03_11__
#define __LogProvider_H__2013_03_11__

#if defined(_WIN32) || defined(WIN32)

#include <string>
#include <fstream>
#include <map>
using namespace std;

#define KKCommonLogFileName			"CommonLog"

//////////////////////////////////////////////////////////////////////////
//- KKLogObject
class KKLogObject
{
public:
	KKLogObject(const std::string &logFileName = KKCommonLogFileName);
	virtual ~KKLogObject();

public:
	virtual const std::string & GetLogFileName(void) const;

	virtual void LogTrace(const std::string &strLogText);
	virtual void LogInfo(const std::string &strLogText);
	virtual void LogError(const std::string &strLogText);
	virtual void LogWarn(const std::string &strLogText);

protected:
	static std::string GetCurrentTimeString(void);
	static void OutputLogText(std::ofstream &fout, const std::string &logText);

protected:
	std::ofstream	mFOut;
	std::string		mLogFileName;
};

//////////////////////////////////////////////////////////////////////////
//- LogFlyweight
class KKLogObjectPool
{
public:
	typedef std::map<std::string, KKLogObject*>	LogObjectPool;
	typedef LogObjectPool::iterator				LogObjectPoolIter;

private:
	KKLogObjectPool();
public:
	virtual ~KKLogObjectPool();
	static KKLogObjectPool & GetLogObjectPool(void);

public:
	//- objId is log filename(only).
	KKLogObject * GetLogObject(const std::string &objId);
	bool IsLogObjectExisted(const std::string &objId);

private:
	void ClearLogObjects(void);

protected:
	LogObjectPool	mLogObjectPool;
};

//////////////////////////////////////////////////////////////////////////
//- KKLogProvider 
class KKLogProvider
{
public:
	static void LogTrace(const std::string &logText, const std::string &filename = KKCommonLogFileName);
	static void LogInfo(const std::string &logText, const std::string &filename = KKCommonLogFileName);
	static void LogError(const std::string &logText, const std::string &filename = KKCommonLogFileName);
	static void LogWarn(const std::string &logText, const std::string &filename = KKCommonLogFileName);

	static const char * LogConvertFormatStr(const char *lpcszFormat, ...);
};

#endif

#endif//__LogProvider_H__2013_03_11__