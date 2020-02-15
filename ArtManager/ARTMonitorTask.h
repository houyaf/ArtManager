/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：CARTUIThread.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: ART UI Task基类声明
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/
#pragma once
#include "artuithread.h"
class CARTMonitorTask :	public CARTUIThread
{
	DECLARE_DYNCREATE(CARTMonitorTask)

public:
	CARTMonitorTask(void);
	~CARTMonitorTask(void);
	virtual BOOL InitInstance();

public:
	afx_msg void OnMonitor(WPARAM wParam,LPARAM lParam);

public:
	// Generated message map functions
	//{{AFX_MSG(CCounterThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

