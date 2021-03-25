#pragma once

#include "stdafx.h"
#include "PCInfo.h"

#include "atlbase.h"  
#include "winioctl.h"   
#include "iphlpapi.h"  
#pragma comment ( lib, "Iphlpapi.lib" ) 
CString CheckIP(void)//CheckIP函数，用于获取本机IP地址
{
	WORD wVersionRequested;//WORD类型变量，用于存放Winsock版本的值
	WSADATA wsaData;
	char name[255];//用于存放主机名
	PHOSTENT hostinfo;
	LPCSTR ip;
	wVersionRequested = MAKEWORD(2, 0);
	//调用MAKEWORD（）函数获得Winsock版本，用于加载Winsock库
	if (WSAStartup(wVersionRequested, &wsaData) == 0)
	{
		//加载Winsock库，如果WSAStartup()函数的返回值为0，说明加载成功
		if (gethostname(name, sizeof(name)) == 0)
		{
			if ((hostinfo = gethostbyname(name)) != NULL)
			{
				//如果获得主机名成功的话，调用inet_ntoa()函数取得IP地址
				ip = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
		WSACleanup();
	}
	return ip;
}

/*

只获取本地连接的网卡信息，并不获取无线网卡和虚拟网卡的信息，
要想获取无线网卡的信息，
需把if(strstr(pAdapter->Description,"PCI")>0 && pAdapter- >Type==MIB_IF_TYPE_ETHERNET)
改成if(strstr(pAdapter->Type==71)，
若要获取虚拟网卡的信息，
需把if(strstr(pAdapter->Description,"PCI")>0 && pAdapter->Type==MIB_IF_TYPE_ETHERNET)改成
if(pAdapter->Type==MIB_IF_TYPE_ETHERNET)

*/
enum ADAPTERType
{
	LocalNetworkCard =1,
	WirelessCard,
	VirtualCard
};

CString GetMacAddress(UINT iType)
{	//PIP_ADAPTER_INFO结构体指针存储本机网卡信息
	PIP_ADAPTER_INFO pAdapterInfo = NULL;
	PIP_ADAPTER_INFO pAdapter = NULL;
	DWORD dwRetVal = 0;
	pAdapterInfo = new IP_ADAPTER_INFO;
	//得到结构体大小,用于GetAdaptersInfo参数

	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
	//调用GetAdaptersInfo函数,填充pAdapterInfo指针变量;其中ulOutBufLen参数既是一个输入量也是一个输出量

	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) != ERROR_SUCCESS)
	{
		//如果函数返回的是ERROR_BUFFER_OVERFLOW,则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
		//这也是说明为什么stSize既是一个输入量也是一个输出量

		//释放原来的内存空间
		delete pAdapterInfo;		
		//重新申请内存空间用来存储所有网卡信息
		pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
	}
	//再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
	CString strMacAdress, strTemp;
	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR)
	{
		pAdapter = pAdapterInfo;
		while (pAdapter)
		{
			UINT itype = pAdapter->Type;
			//6 是有线网卡 71 是无线网卡
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



// 获取CPU序列号	
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

// 获取C盘序列号
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
		AfxMessageBox("CPU序列号获取失败!");
		return -1;
	}
	strCPUID.Format(szCpuId);
	// 获取MAC码
	char szMac[13]{ 0 };
// 	if (!ObtainMAC(szMac))
// 	{
// 		AfxMessageBox("MAC码获取失败!");
// 		return -1;
// 	}
	strMAC.Format(szMac);
	// 获取硬盘序列号
	char szHdId[13]{ 0 };
	if (!ObtainHDID(szHdId))
	{
		AfxMessageBox("硬盘序列号获取失败!");
		return -1;
	}
	strHDID.Format(szHdId);
	strOutBuffer = strCPUID + "|" + strMAC + "|" + strHDID;
	memcpy(lpInfoBuffer, strOutBuffer.GetBuffer(0), strOutBuffer.GetLength());
	return 0;
}