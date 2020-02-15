/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：CommonFunc.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: 公共函數聲明
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#pragma once

extern DWORD   IP_STR2DW(LPCTSTR szIP);
extern CString IP_DW2STR(DWORD dwIP);

extern bool GetLocalIPandMask(	DWORD *pdwIP1, DWORD *pdwIPMask1, 
								DWORD *pdwIP2, DWORD *pdwIPMask2, 
								DWORD *pdwIP3, DWORD *pdwIPMask3, 
								DWORD *pdwIP4, DWORD *pdwIPMask4  );
