/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTMsgLog.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: CARTMonitorLog 实现文件
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

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


// CARTMonitorLog 诊断

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


// CARTMonitorLog 消息处理程序


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
	
	listCtrl.InsertColumn(0, _T("索引"),  LVCFMT_LEFT, 50);	
	listCtrl.InsertColumn(1, _T("时间"),  LVCFMT_LEFT, 150);
	listCtrl.InsertColumn(2, _T("描述"),  LVCFMT_LEFT, 788);

	listCtrl.SetExtendedStyle(listCtrl.GetExtendedStyle()
		 |LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);

	
}


BOOL CARTMonitorLog::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}


void CARTMonitorLog::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CListCtrl& listCtrl = GetListCtrl();

	listCtrl.DeleteAllItems();

	// TODO: 在此添加专用代码和/或调用基类
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
