/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����CommonFunc.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: ����������
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/

#pragma once

extern DWORD   IP_STR2DW(LPCTSTR szIP);
extern CString IP_DW2STR(DWORD dwIP);

extern bool GetLocalIPandMask(	DWORD *pdwIP1, DWORD *pdwIPMask1, 
								DWORD *pdwIP2, DWORD *pdwIPMask2, 
								DWORD *pdwIP3, DWORD *pdwIPMask3, 
								DWORD *pdwIP4, DWORD *pdwIPMask4  );
