
/********************************************************************************
* File Name     :  TLog.h
* Created on    :  05/25/2009 
* Version       :  1.0
* Revised on    :  
*
* Author        :  rivergood
*
* Copyright (c) 2009
* All rights reserved.
* 
* Description   :         
* 
********************************************************************************/
#ifndef _TLOG
#define _TLOG

#include "basetype.h"

class TLog
{
  public:
    TLog();
    ~TLog();
    TBool init(const char* sysLog, const char* RUNLog, const char* DebugLog);
    void writeSysLog(TLogType logType, char *fmt, ... );
    void writeRUNLog(TLogType logType, char *fmt, ... );
    void writeDebugLog(TLogType logType, char *fmt, ... );
  private:
    void writeLog(TLogType logType, char *logFile);
    void backupLogFile(char *szFileName);    
  private:
    char m_szSysLogFile[CommonStrLength+1];
    char m_szRUNLogFile[CommonStrLength+1];
    char m_szDebugLogFile[CommonStrLength+1];
    char m_szLogCont[MaxFileLineLength+1];
};

#endif

