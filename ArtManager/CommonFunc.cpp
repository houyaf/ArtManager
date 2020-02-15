/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：CommonFunc.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: 公共函數定義
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#include "stdafx.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "IPHLPAPI.lib")

CString IP_DW2STR(DWORD dwIP)
{
	CString szIP =_T("");
	WORD dwByte1, dwByte2, dwByte3, dwByte4;

	if (dwIP == 0) return szIP;

	dwByte1 = (WORD)(dwIP&255);
	dwByte2 = (WORD)((dwIP>>8)&255);
	dwByte3 = (WORD)((dwIP>>16)&255);
	dwByte4 = (WORD)((dwIP>>24)&255);

	szIP.Format("%d.%d.%d.%d",dwByte4, dwByte3, dwByte2, dwByte1);

	return szIP;
}

//DWORD IP_STR2DW(LPCTSTR szIP)
//{
//	return (DWORD)inet_addr(szIP);
//}


DWORD   IP_STR2DW(LPCTSTR szIP)
{
	int len=_tcslen(szIP);
	if( len <7 || len>15 ) 
		return 0 ;

	DWORD  dwip = 0;
	char  *p ;
	BYTE   dd;
	char   field[4];
	int    i=0;
	int    j = 3;

	for (p =(char *)szIP; *p!= NULL ; p++)
	{
		if ((*p >='0')  && (*p <='9'))
		{
			field[i++] = * p;
		}

		if ((*(p+1) == '.') || (*(p+1) == 0 ))
		{
			field[i] = 0;
			i = 0;
			dd = (BYTE)atoi(field);
			dwip = dwip | ((DWORD) dd << (j--)*8);
		}
	}

	if (j!= -1)
		return 0;

	return dwip;
}


bool GetLocalIPandMask(DWORD *pdwIP1, DWORD *pdwIPMask1, 
					  DWORD *pdwIP2, DWORD *pdwIPMask2, 
					  DWORD *pdwIP3, DWORD *pdwIPMask3, 
					  DWORD *pdwIP4, DWORD *pdwIPMask4  )
{
	PIP_ADAPTER_INFO pAdapterInfo;
	PIP_ADAPTER_INFO pAdapter	= NULL;
	DWORD dwRetVal				= 0;
	UINT  iCount				= 0;
	DWORD dwTargetIP            ; 
	DWORD dwTargetMask          ;

	ULONG ulOutBufLen = sizeof (IP_ADAPTER_INFO);
	pAdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof (IP_ADAPTER_INFO));
	if (pAdapterInfo == NULL)
	{
		//Error allocating memory needed to call GetAdaptersinfo
		return false;
	}
	// Make an initial call to GetAdaptersInfo to get
	// the necessary size into the ulOutBufLen variable
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) 
	{
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO *) malloc(ulOutBufLen);
		if (pAdapterInfo == NULL) 
		{
			//Error allocating memory needed to call GetAdaptersinfo
			return false;
		}
	}

	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) 
	{
		pAdapter = pAdapterInfo;
		while (pAdapter)
		{
			dwTargetIP   = IP_STR2DW(pAdapter->IpAddressList.IpAddress.String);
			dwTargetMask = IP_STR2DW(pAdapter->IpAddressList.IpMask.String);

			if (dwTargetIP != 0)
			{
				iCount++ ;
				switch (iCount)
				{
					case 1:
						*pdwIP1       = dwTargetIP   ;
						*pdwIPMask1   = dwTargetMask ;
						break;

					case 2:
						*pdwIP2       = dwTargetIP   ;
						*pdwIPMask2   = dwTargetMask ;
						break;

					case  3:
						*pdwIP3       = dwTargetIP   ;
						*pdwIPMask3   = dwTargetMask ;
						break;

					case 4:
						*pdwIP4       = dwTargetIP  ;
						*pdwIPMask4   = dwTargetMask;
						break;

					default :
						break;
				}	
			}
			pAdapter = pAdapter->Next;
		}
	} 

	if (pAdapterInfo)
	{
		free(pAdapterInfo);
	}

	return true;
}