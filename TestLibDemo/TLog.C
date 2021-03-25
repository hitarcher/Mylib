/********************************************************************************
* File Name     :  TLog.C
* Created on    :  05/23/2009 
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
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h> 
#include <sys/stat.h>
#include <arpa/inet.h>

#include "TLog.h"

#define RUNLOG {strcpy(g_szFile,__FILE__);g_iLine=__LINE__;}g_pLog->writeRUNLog
#define SysLOG {strcpy(g_szFile,__FILE__);g_iLine=__LINE__;}g_pLog->writeSysLog
#define DebugLOG {strcpy(g_szFile,__FILE__);g_iLine=__LINE__;}g_pLog->writeDebugLog

enum TBool
{
    False = 0,
    True = 1
};

enum TLogType
{
    Error = 1,
    Warn,
    Prompt,
    None
};

struct TLoglevel
{
    int iLogLevel;
};

const int CommonStrLength = 256; 
const int MaxCfgItemValueLenth = 1024;

TLoglevel *g_pLogLevel = NULL;
TLog *g_pLog = NULL;
char g_szFile[CommonStrLength+1];
int g_iLine;

/*************************************************
  Function:       trim
  Description:   去除字符串前后的空格
  Calls:          
  Called By:    
  Table Accessed: 
  Table Updated:  
  Input:        源字段串
  Output:       
  Return:  目标字段串 
  Others:       
*************************************************/

char *trim(char *str)
{
    char *pBeg = str;
    char *pEnd;
    if (pBeg)
    {
        pEnd = pBeg + strlen(str) - 1;
        while(*pBeg && isspace(*pBeg)) pBeg++;
        while(pEnd > pBeg && isspace(*pEnd)) *pEnd-- = '\0';
    }
    return pBeg;
}
/*************************************************
  Function:       ip2Int
  Description:   将IP地址转换为整数
  Calls:          
  Called By:    
  Table Accessed: 
  Table Updated:  
  Input:        
  Output:      
  Return:    
  Others:    
*************************************************/

int ip2Int(char *ipAddr)
{
    if (NULL == ipAddr)
    {
        return -1;
    }

    return inet_addr(ipAddr);
}

/*************************************************
  Function:       int2IP
  Description:   将整数转换为IP地址
  Calls:          
  Called By:    
  Table Accessed: 
  Table Updated:  
  Input:        
  Output:      
  Return:    
  Others:    
*************************************************/

char* int2IP(int ip)
{
    struct in_addr addr;
    return inet_ntoa((struct in_addr&)ip);
}

TLog::TLog()
{
    memset(m_szSysLogFile, 0, sizeof(m_szSysLogFile));
    memset(m_szRUNLogFile, 0, sizeof(m_szRUNLogFile));
    memset(m_szDebugLogFile, 0, sizeof(m_szDebugLogFile));
    memset(m_szLogCont, 0, sizeof(m_szLogCont));
}

TLog::~TLog()
{

}

/*************************************************
  Function:       init
  Description:   
  Calls:          
  Called By:    
  Table Accessed: 
  Table Updated:  
  Input:        文件句柄
  Output:       
  Return:  
  Others:       
*************************************************/
TBool TLog::init(const char* sysLog, const char* RUNLog, const char* DebugLog)
{    
    if ((NULL == sysLog) || (0 == strlen(sysLog)))
    {
        fprintf(stderr, "sysLog is NULL./n");
        return False;
    }
    else if ((NULL == RUNLog) || (0 == strlen(RUNLog)))
    {
        fprintf(stderr, "RUNLog is NULL./n");
        return False;
    }
    else if ((NULL == DebugLog) || (0 == strlen(DebugLog)))
    {
        fprintf(stderr, "sysLog is NULL./n");
        return False;
    }    

    strcpy(m_szSysLogFile, sysLog);
    strcpy(m_szRUNLogFile, RUNLog);
    strcpy(m_szDebugLogFile, DebugLog);

    return True;
}

/*************************************************
  Function:       backupFile
  Description:  备份文件
  Calls:          
  Called By:    
  Table Accessed: 
  Table Updated:  
  Input:        文件名
  Output:       
  Return:    TBool
  Others:    
*************************************************/

void TLog::backupLogFile(char *szFileName)
{
    char szBakLogFile[CommonStrLength+1] = "";;
    struct stat FileStat;
    
    if ( 0 > stat(szFileName, &FileStat))
    {
        return;
    }
    else
    {
        if (10000000 <= FileStat.st_size)
        {
            sprintf(szBakLogFile, "%s.bak", szFileName);
            rename(szFileName, szBakLogFile);
        }
    }  

    return;

}

/*************************************************
  Function:       writeSysLog
  Description:   记录程序的系统日志
  Calls:          
  Called By:     
  Table Accessed: 
  Table Updated:  
  Input:         
  Output:      
  Return:  void      
  Others:       
*************************************************/

void TLog::writeSysLog(TLogType logType, char *fmt, ... )
{
    va_list args;
    va_start (args, fmt); 

    memset(m_szLogCont, 0, sizeof(m_szLogCont));
    vsprintf(m_szLogCont, fmt, args);
    va_end (args);
    
    trim(m_szLogCont);
    writeLog(logType, m_szSysLogFile);

    return;

}

/*************************************************
  Function:       writeRUNLog
  Description:   记录程序的系统日志
  Calls:          
  Called By:     
  Table Accessed: 
  Table Updated:  
  Input:         
  Output:      
  Return:  void      
  Others:       
*************************************************/

void TLog::writeRUNLog(TLogType logType, char *fmt, ... )
{
    if ((NULL == g_pLogLevel) || (0 == g_pLogLevel->iLogLevel))
    {
        return;
    }

    va_list args;
    va_start (args, fmt);
    memset(m_szLogCont, 0, sizeof(m_szLogCont));
    sprintf(m_szLogCont, fmt, args);
    va_end (args);
    
    trim(m_szLogCont);
    writeLog(logType, m_szRUNLogFile);

    return;

}


/*************************************************
  Function:       writeDebugLog
  Description:   记录程序的系统日志
  Calls:          
  Called By:     
  Table Accessed: 
  Table Updated:  
  Input:         
  Output:      
  Return:  void      
  Others:       
*************************************************/

void TLog::writeDebugLog(TLogType logType, char *fmt, ... )
{
    if ((NULL == g_pLogLevel) || (2 != g_pLogLevel->iLogLevel))
    {
        return;
    }

    va_list args;
    va_start (args, fmt);
    memset(m_szLogCont, 0, sizeof(m_szLogCont));
    vsprintf(m_szLogCont, fmt, args);
    va_end (args);
    
    trim(m_szLogCont);
    writeLog(logType, m_szDebugLogFile);

    return;
}

/*************************************************
  Function:       writeLog
  Description:   记录程序执行的日志
  Calls:          
  Called By:     
  Table Accessed: 
  Table Updated:  
  Input:         
  Output:      
  Return:  void      
  Others:       
*************************************************/

void TLog::writeLog(TLogType logType, char *logFile)
{
    
    static int s_iLastDate;
    char szLogFile[CommonStrLength+1] = "";  
    snprintf(szLogFile,  sizeof(szLogFile), "%s", logFile);
  
    FILE *fp = (FILE *)0;

    fp = fopen (szLogFile, "a");
    if ((FILE *)0 == fp)
    {
        fclose (fp);
        return;
    }
        
    time_t now = time ((time_t *)0);
    struct tm *tm = localtime (&now);    
    if (s_iLastDate != tm->tm_mday)
    {
        fprintf(fp,"\n\n####################[%d-%02d-%02d]######################\n",
            tm->tm_year + 1900, tm->tm_mon+1, tm->tm_mday);
    }
    s_iLastDate = tm->tm_mday;

    //add logtype
    char szLogType[256];
    switch (logType)
    {
        case Prompt:
            strcpy(szLogType, "Prompt:");
             break;
        case Warn:
            strcpy(szLogType, "Warning:");
            break;
        case Error:
            strcpy(szLogType, "Error:");
            break;
        case None:
            strcpy(szLogType, "");
            break;            
        default:
            strcpy(szLogType, "");
    }
        
    if (Error == logType)
    {
        fprintf (fp, "[%02d:%02d:%02d][%s] %s \"%s:%d\"\n",
          tm->tm_hour, tm->tm_min, tm->tm_sec, szLogType,
          m_szLogCont, g_szFile, g_iLine);       
    }
    else   
    {
        fprintf (fp, "[%02d:%02d:%02d][%s] %s",
          tm->tm_hour, tm->tm_min, tm->tm_sec, szLogType, m_szLogCont);    
    }
    

    //fflush(fp); 
    fclose (fp);

    //backup logfile
    backupLogFile(szLogFile);

    return;  
}

