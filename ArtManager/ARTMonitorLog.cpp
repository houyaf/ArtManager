/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTMsgLog.cpp
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: CARTMonitorLog ʵ���ļ�
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/

#include "stdafx.h"
#include "ART.h"
#include "ARTDoc.h"
#include "ARTMonitorLog.h"


// CARTMonitorLog
IMPLEMENT_DYNCREATE(CARTMonitorLog, CListView)

CARTMonitorLog::CARTMonitorLog()
{

}

CARTMonitorLog::~CARTMonitorLog()
{

}

BEGIN_MESSAGE_MAP(CARTMonitorLog, CListView)
END_MESSAGE_MAP()


// CARTMonitorLog ���

#ifdef _DEBUG
void CARTMonitorLog::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CARTMonitorLog::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CARTMonitorLog ��Ϣ�������


void CARTMonitorLog::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl& listCtrl = GetListCtrl();

	CHeaderCtrl *pHeadCtrl = listCtrl.GetHeaderCtrl();
	int  iCount;

	if (pHeadCtrl != NULL)
	{
		iCount = pHeadCtrl->GetItemCount();
		
		for (int i=0; i< iCount; i++)
		{
			listCtrl.DeleteColumn(0);
		}

		listCtrl.DeleteAllItems();
	}
	
	listCtrl.InsertColumn(0, _T("����"),  LVCFMT_LEFT, 50);	
	listCtrl.InsertColumn(1, _T("ʱ��"),  LVCFMT_LEFT, 150);
	listCtrl.InsertColumn(2, _T("����"),  LVCFMT_LEFT, 788);

	listCtrl.SetExtendedStyle(listCtrl.GetExtendedStyle()
		 |LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);

	
}


BOOL CARTMonitorLog::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}


void CARTMonitorLog::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CListCtrl& listCtrl = GetListCtrl();

	listCtrl.DeleteAllItems();

	// TODO: �ڴ����ר�ô����/����û���
	CLogManager *pLogManager = ((CARTDoc *)GetDocument())->GetLogManager();
	CLogList    *pLogList = NULL;

	pLogList = pLogManager->Get_MonitorLogList();

	POSITION pos;
	CLog    *pLog = NULL;
	int i = 1;
	CString strNo;
	CString strLogTime;
	CString strLogInfo;


	pos = pLogList->GetHeadPosition();
	while(pos != NULL)
	{
		pLog = pLogList->GetNext(pos);

		strNo.Format("%d", i);
		int nItem = listCtrl.InsertItem(i, (LPCTSTR)strNo);

		strLogTime = pLog->Get_LogTime().Format(_T("%Y-%m-%d %H:%M:%S"));
		listCtrl.SetItemText(nItem, 1, (LPCTSTR)strLogTime);

		strLogInfo = pLog->Get_LogInfo();
		listCtrl.SetItemText(nItem, 2, (LPCTSTR)strLogInfo);

		i++;
	}
}
