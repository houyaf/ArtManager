/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����CARTUIThread.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: ART UI Task��������
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

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

