//**********************************************************************/
//* ���ߣ�Jacc.Kim
//* ���ڣ�2013-03-11
//* ������Log��־����
//* ��ע��
//* �޸ģ�2013-03-19
//* �޸ģ�
//**********************************************************************/
#if (defined(_WIN32) || defined(WIN32)) && (_MSC_VER > 1000)
#	pragma once
#endif

#ifndef __LogConfig_H__2013_03_11__
#define __LogConfig_H__2013_03_11__

#define KK_PLATFORM_UNKNOWN			0x00	//δ֪ƽ̨
#define KK_PLATFORM_WIN32			0x01	//WIN32ƽ̨

#if defined(_WIN32) || defined(WIN32)
#	define KK_TARGET_PLATFORM	KK_PLATFORM_WIN32
#else
#	define KK_TARGET_PLATFORM	KK_PLATFORM_UNKNOWN
#endif

//- �����һЩ��־����(����WINƽ̨��ʹ��)
#if KK_TARGET_PLATFORM == KK_PLATFORM_WIN32

#	define KK_USE_LOG_SWITCH		//��־�ܿ���

#	ifdef KK_USE_LOG_SWITCH
#		define KK_TRACE_LOG_SWITCH	//׷����־����
#		define KK_NORMAL_LOG_SWITCH	//��ͨ��־����
#		define KK_ERROR_LOG_SWITCH	//������־����
#		define KK_WARN_LOG_SWITCH	//������־����
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