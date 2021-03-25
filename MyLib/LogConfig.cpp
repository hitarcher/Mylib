#include "stdafx.h"
#include "LogConfig.h"

#ifdef KK_USE_LOG_SWITCH
#	include <Windows.h>
#endif

const char * KKLogTextConvertFormat(const char *lpcszFormat, ...)
{
#ifdef KK_USE_LOG_SWITCH
	memset(g_szLogTextBuff, 0, KKMaxLogLength);
	va_list ap;
	va_start(ap, lpcszFormat);
	vsnprintf_s(g_szLogTextBuff, KKMaxLogLength, KKMaxLogLength, lpcszFormat, ap);
	va_end(ap);
	return g_szLogTextBuff;
#else
	return "";
#endif
}