#pragma once
#ifndef _PCINFO_H_
#define _PCINFO_H_

CString CheckIP(void);//CheckIP���������ڻ�ȡ����IP��ַ
CString GetMacAddress(UINT iType=1);

// ��ȡCPU���к�	
bool ObtainCPUID(char *pCpuId);

// ��ȡC�����к�
bool ObtainHDID(char *pHdId);
#endif // PCINFO
