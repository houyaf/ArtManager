/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTMsgLog.cpp
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: CARTMsgLog ʵ���ļ�
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/

#include "stdafx.h"
#include "ART.h"
#include "ARTDoc.h"
#include "ARTMsgLog.h"


// CARTMsgLog

IMPLEMENT_DYNCREATE(CARTMsgLog, CListView)

CARTMsgLog::CARTMsgLog()
{

}

CARTMsgLog::~CARTMsgLog()
{
}

BEGIN_MESSAGE_MAP(CARTMsgLog, CListView)
END_MESSAGE_MAP()


// CARTMsgLog ���

#ifdef _DEBUG
void CARTMsgLog::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CARTMsgLog::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CARTMsgLog ��Ϣ�������


void CARTMsgLog::OnInitialUpdate()
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

	listCtrl.SetExtendedStyle(listCtrl.GetExtendedStyle()|LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);

}


BOOL CARTMsgLog::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}


void CARTMsgLog::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���
	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.DeleteAllItems();

	CLogManager *pLogManager = ((CARTDoc *)GetDocument())->GetLogManager();
	CLogList    *pLogList = NULL;

	pLogList = pLogManager->Get_MsgLogList();


	POSITION pos;
	CLog  *pLog  = NULL;
	int        i = 1;
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
