#pragma once
#ifndef _INTERFACE_TINY_ZIP_H__
#define _INTERFACE_TINY_ZIP_H__

#ifdef RN_API_EXPORTS
#define RN_API __declspec(dllexport) WINAPI  
#else
#define RN_API __declspec(dllimport) WINAPI 
#endif

#ifdef __cplusplus
extern "C" {
#endif 

	typedef DWORD RN_RESULT;
	typedef DWORD RN_STATUS;

// 	enum LOGLEVEL
// 	{
// 		LOGLEVEL_NULL = 0,
// 		LOGLEVEL_ERR = 1,
// 		LOGLEVEL_ENTER = 2,
// 		LOGLEVEL_DETAIL = 3
// 	};

	/************************************************************************/
	/*                             ERR    MESSAGE                           */
	/************************************************************************/
#define RN_ERR_PARAM		1000	/// ��������
#define RN_ERR_OPEN			1001	/// ��ѹ���ļ�ʧ��
#define RN_ERR_FILEINFO		1002	/// ��ȡѹ���ļ�����
#define RN_ERR_CREATFILE	1003	/// �����ļ�ʧ��
#define RN_ERR_OPENFILE		1004	/// ��ѹ���ļ��е��ļ�ʧ��

#define RN_ERR_NOSUPPORT	9999	/// ���ܲ�֧��

	/* example */
	//==================================================
	// ��������_expFunction
	// ���  ��null
	// ����  ��null
	// ����ֵ��RN_RESULT 
	//==================================================
	//EXTERN_C RN_RESULT RN_API _expFunction(void);

	//==================================================
	// ��������_version
	// ���  ��detail			> ture:��ϸ��Ϣ
	//							> false:����ʾ�汾��
	// ����  ��null
	// ����ֵ��version 
	//==================================================
	LPCTSTR RN_API _version(bool bdetail);

	//==================================================
	// ��������_zip
	// ���  ��null
	// ����  ��null
	// ����ֵ��RN_RESULT 
	//==================================================
	RN_RESULT RN_API _zip(const char* _in_pFolderPath, int nType);

	//==================================================
	// ��������_unzip
	// ���  ��_in_pFilePath       > ����ѹ�ļ�ȫ·��
	//         _in_pOutputFilePath > ��ѹ���ļ�·�������Ϊ�գ���ѹ����ǰ·��
	//         _in_Passwd          > ����ѹ�ļ����룻���Ϊ�գ���������
	// ����  ��null
	// ����ֵ��RN_RESULT           > �ɹ�������ʧ��
	//==================================================
	RN_RESULT RN_API _unzip(const char* _in_pFilePath, const char* _in_pOutputFilePath = NULL,const char* _in_Passwd = NULL);






#ifdef __cplusplus
}
#endif 
#endif