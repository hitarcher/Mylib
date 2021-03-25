//**********************************************************************/
//* 作者：Jacc.Kim
//* 日期：2013-03-19
//* 描述：user log information config
//* 备注：
//**********************************************************************/
#if (defined(_WIN32) || defined(WIN32)) && (_MSC_VER > 1000)
#	pragma once
#endif

#ifndef __LogUserConfig_H__2013_03_19__
#define __LogUserConfig_H__2013_03_19__

#include "LogConfig.h"

#define KKTraceBegin(logText, logFileName)			KKLogTrace(std::string("----[ ") + logText + std::string(" ]----"), logFileName)
#define KKLog(logText, logFileName)					KKLogInfo(logText, logFileName)
#define KKError(logText, logFileName)				KKLogError(std::string("xxx ") + logText, logFileName)
#define KKWarn(logText, logFileName)				KKLogWarn(std::string("!!! ") + logText, logFileName)
#define KKTraceEnd(logText, logFileName)			KKLogTrace(std::string("----[ ") + logText + std::string(" ]----\r\n"), logFileName)

//////////////////////////////////////////////////////////////////////////
//- user log config can be defined like below code.

//- MyTableView control log define.
#define MyTableViewCtrlLFN							"MyTableViewLog"
#define MYTVTraceBegin(logText)						KKTraceBegin(logText, MyTableViewCtrlLFN)
#define MYTVLog(logText)							KKLog(logText, MyTableViewCtrlLFN)
#define MYTVError(logText)							KKError(logText, MyTableViewCtrlLFN)
#define MYTVWarn(logText)							KKWarn(logText, MyTableViewCtrlLFN)
#define MYTVTraceEnd(logText)						KKTraceEnd(logText, MyTableViewCtrlLFN)

#define MYTVTraceBeginEx(logText, ...)				KKTraceBegin(KKLogTextConvertFormat(logText, ##__VA_ARGS__), MyTableViewCtrlLFN)
#define MYTVLogEx(logText, ...)						KKLog(KKLogTextConvertFormat(logText, ##__VA_ARGS__), MyTableViewCtrlLFN)
#define MYTVErrorEx(logText, ...)					KKError(KKLogTextConvertFormat(logText, ##__VA_ARGS__), MyTableViewCtrlLFN)
#define MYTVWarnEx(logText, ...)					KKWarn(KKLogTextConvertFormat(logText, ##__VA_ARGS__), MyTableViewCtrlLFN)
#define MYTVTraceEndEx(logText, ...)				KKTraceEnd(KKLogTextConvertFormat(logText, ##__VA_ARGS__), MyTableViewCtrlLFN)

#endif//__LogUserConfig_H__2013_03_19__