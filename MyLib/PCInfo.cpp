#pragma once

#include "stdafx.h"
#include "PCInfo.h"

#include "atlbase.h"  
#include "winioctl.h"   
#include "iphlpapi.h"  
#pragma comment ( lib, "Iphlpapi.lib" ) 
CString CheckIP(void)//CheckIP���������ڻ�ȡ����IP��ַ
{
	WORD wVersionRequested;//WORD���ͱ��������ڴ��Winsock�汾��ֵ
	WSADATA wsaData;
	char name[255];//���ڴ��������
	PHOSTENT hostinfo;
	LPCSTR ip;
	wVersionRequested = MAKEWORD(2, 0);
	//����MAKEWORD�����������Winsock�汾�����ڼ���Winsock��
	if (WSAStartup(wVersionRequested, &wsaData) == 0)
	{
		//����Winsock�⣬���WSAStartup()�����ķ���ֵΪ0��˵�����سɹ�
		if (gethostname(name, sizeof(name)) == 0)
		{
			if ((hostinfo = gethostbyname(name)) != NULL)
			{
				//�������������ɹ��Ļ�������inet_ntoa()����ȡ��IP��ַ
				ip = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
		WSACleanup();
	}
	return ip;
}

/*

ֻ��ȡ�������ӵ�������Ϣ��������ȡ����������������������Ϣ��
Ҫ���ȡ������������Ϣ��
���if(strstr(pAdapter->Description,"PCI")>0 && pAdapter- >Type==MIB_IF_TYPE_ETHERNET)
�ĳ�if(strstr(pAdapter->Type==71)��
��Ҫ��ȡ������������Ϣ��
���if(strstr(pAdapter->Description,"PCI")>0 && pAdapter->Type==MIB_IF_TYPE_ETHERNET)�ĳ�
if(pAdapter->Type==MIB_IF_TYPE_ETHERNET)

*/
enum ADAPTERType
{
	LocalNetworkCard =1,
	WirelessCard,
	VirtualCard
};

CString GetMacAddress(UINT iType)
{	//PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
	PIP_ADAPTER_INFO pAdapterInfo = NULL;
	PIP_ADAPTER_INFO pAdapter = NULL;
	DWORD dwRetVal = 0;
	pAdapterInfo = new IP_ADAPTER_INFO;
	//�õ��ṹ���С,����GetAdaptersInfo����

	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	//����GetAdaptersInfo����,���pAdapterInfoָ�����;����ulOutBufLen��������һ��������Ҳ��һ�������

	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) != ERROR_SUCCESS)
	{
		//����������ص���ERROR_BUFFER_OVERFLOW,��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
		//��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������

		//�ͷ�ԭ�����ڴ�ռ�
		delete pAdapterInfo;		
		//���������ڴ�ռ������洢����������Ϣ
		pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
	}
	//�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
	CString strMacAdress, strTemp;
	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
	{
		pAdapter = pAdapterInfo;
		while (pAdapter)
		{
			UINT itype = pAdapter->Type;
			//6 ���������� 71 ����������
			if (iType == LocalNetworkCard /*&& strstr(pAdapter->Description, "PCI")>0 */&& pAdapter->Type == MIB_IF_TYPE_ETHERNET)
			{
				goto SHOW;
			}
			else if (iType == WirelessCard /*&& strstr(pAdapter->Description, "PCI")>0 */&& pAdapter->Type == 71)
			{
				goto SHOW;
 			}
//			else if (iType == VirtualCard && pAdapter->Type == MIB_IF_TYPE_ETHERNET)
// 			{
// 				goto SHOW;
// 			}
			pAdapter = pAdapter->Next;
			continue;
SHOW:			
// 			if (pAdapter->Type == MIB_IF_TYPE_ETHERNET)
// 			{
				CString ip(pAdapter->IpAddressList.IpAddress.String);
				for (UINT i = 0; i < pAdapter->AddressLength; i++)
				{
					strTemp.Format(_T("%02X"), pAdapter->Address[i]);
					strMacAdress += strTemp;
					if (i < pAdapter->AddressLength - 1)
						strMacAdress += _T("-");
				}
				break;
// 			}
//			pAdapter = pAdapter->Next;
		}
	}
	delete pAdapterInfo;
	return strMacAdress;
}



// ��ȡCPU���к�	
bool ObtainCPUID(char *pCpuId)
{
	INT32 deBuf[4];
	__cpuidex(deBuf, 01, 0);

	sprintf_s(pCpuId, 17, "%08X%08X", deBuf[3], deBuf[0]);

	if (strlen(pCpuId) != 16)
	{
		return false;
	}

	return true;
}

// ��ȡC�����к�
bool ObtainHDID(char *pHdId)
{
	DWORD VolumeSerialNumber = 0;
	GetVolumeInformation("c:\\", NULL, 12, &VolumeSerialNumber, NULL, NULL, NULL, 10);

	sprintf_s(pHdId, 13, "%012lu", VolumeSerialNumber);

	if (strlen(pHdId) != 12)
	{
		return false;
	}

	return true;
}


DWORD  Getsysteminfo(OUT LPVOID lpInfoBuffer)
{
	CString strCPUID = "";
	CString strMAC = "";
	CString strHDID = "";
	CString strOutBuffer = "";
	char szCpuId[17]{ 0 };

	if (!ObtainCPUID(szCpuId))
	{
		AfxMessageBox("CPU���кŻ�ȡʧ��!");
		return -1;
	}
	strCPUID.Format(szCpuId);
	// ��ȡMAC��
	char szMac[13]{ 0 };
// 	if (!ObtainMAC(szMac))
// 	{
// 		AfxMessageBox("MAC���ȡʧ��!");
// 		return -1;
// 	}
	strMAC.Format(szMac);
	// ��ȡӲ�����к�
	char szHdId[13]{ 0 };
	if (!ObtainHDID(szHdId))
	{
		AfxMessageBox("Ӳ�����кŻ�ȡʧ��!");
		return -1;
	}
	strHDID.Format(szHdId);
	strOutBuffer = strCPUID + "|" + strMAC + "|" + strHDID;
	memcpy(lpInfoBuffer, strOutBuffer.GetBuffer(0), strOutBuffer.GetLength());
	return 0;
}