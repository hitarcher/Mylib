//**********************************************************************/
//* 作者：Jacc.Kim
//* 日期：2013-03-11
//* 描述：Log日志配置
//* 备注：
//* 修改：2013-03-19
//* 修改：
//**********************************************************************/
#if (defined(_WIN32) || defined(WIN32)) && (_MSC_VER > 1000)
#	pragma once
#endif

#ifndef __LogConfig_H__2013_03_11__
#define __LogConfig_H__2013_03_11__

#define KK_PLATFORM_UNKNOWN			0x00	//未知平台
#define KK_PLATFORM_WIN32			0x01	//WIN32平台

#if defined(_WIN32) || defined(WIN32)
#	define KK_TARGET_PLATFORM	KK_PLATFORM_WIN32
#else
#	define KK_TARGET_PLATFORM	KK_PLATFORM_UNKNOWN
#endif

//- 定义的一些日志开关(仅在WIN平台下使用)
#if KK_TARGET_PLATFORM == KK_PLATFORM_WIN32

#	define KK_USE_LOG_SWITCH		//日志总开关

#	ifdef KK_USE_LOG_SWITCH
#		define KK_TRACE_LOG_SWITCH	//追踪日志开关
#		define KK_NORMAL_LOG_SWITCH	//普通日志开关
#		define KK_ERROR_LOG_SWITCH	//错误日志开关
#		define KK_WARN_LOG_SWITCH	//警告日志开关
#	endif

#endif

#	if defined(KK_USE_LOG_SWITCH)
#		include "LogProvider.h"
#	endif

#	if defined(KK_TRACE_LOG_SWITCH)
#		define KKLogTrace(logText, logFileName)					KKLogProvider::LogTrace(logText, logFileName)
#	else
#		define KKLogTrace(logText, logFileName)
#	endif
#	if defined(KK_NORMAL_LOG_SWITCH)
#		define KKLogInfo(logText, logFileName)					KKLogProvider::LogInfo(logText, logFileName)
#	else
#		define KKLogInfo(logText, logFileName)
#	endif
#	if defined(KK_ERROR_LOG_SWITCH)
#		define KKLogError(logText, logFileName)					KKLogProvider::LogError(logText, logFileName)
#	else
#		define KKLogError(logText, logFileName)
#	endif
#	if defined(KK_WARN_LOG_SWITCH)
#		define KKLogWarn(logText, logFileName)					KKLogProvider::LogWarn(logText, logFileName)
#	else
#		define KKLogWarn(logText, logFileName)
#	endif

#ifndef KKMaxLogLength
#	define KKMaxLogLength         (16 * 1024 + 1)
#endif
extern char g_szLogTextBuff[KKMaxLogLength];

const char * KKLogTextConvertFormat(const char *lpcszFormat, ...);

#endif//__LogConfig_H__2013_03_11__