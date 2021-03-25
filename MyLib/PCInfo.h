#pragma once
#ifndef _PCINFO_H_
#define _PCINFO_H_

CString CheckIP(void);//CheckIP函数，用于获取本机IP地址
CString GetMacAddress(UINT iType=1);

// 获取CPU序列号	
bool ObtainCPUID(char *pCpuId);

// 获取C盘序列号
bool ObtainHDID(char *pHdId);
#endif // PCINFO
