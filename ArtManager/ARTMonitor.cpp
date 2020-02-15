/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTMonitor.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: CARTMonitor 实现文件
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#include "stdafx.h"
#include "ART.h"
#include "ARTDoc.h"
#include "ARTMonitor.h"
#include "ARTDlgMonitor.h"
#include "ARTMonitorTask.h"

#define TIME_MONITOR   1

// CARTMonitor

IMPLEMENT_DYNCREATE(CARTMonitor, CListView)

CARTMonitor::CARTMonitor()
:m_pMonitorTask(NULL)
,m_bRunning(FALSE)
{

}

CARTMonitor::~CARTMonitor()
{
}

BEGIN_MESSAGE_MAP(CARTMonitor, CListView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CARTMonitor::OnNMDblclk)
	////ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_COMPLETE , OnTaskComplete )
END_MESSAGE_MAP()

BOOL CARTMonitor::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

void CARTMonitor::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	GetDocument()->m_RightView = this;

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


	listCtrl.InsertColumn(0 , _T("No.")			,  LVCFMT_CENTER	, 30);	
	listCtrl.InsertColumn(1 , _T("设备类型")	,  LVCFMT_CENTER	, 70);
	listCtrl.InsertColumn(2 , _T("IP地址")		,  LVCFMT_CENTER	, 100);
	listCtrl.InsertColumn(3 , _T("串口号")		,  LVCFMT_CENTER	, 50);
	listCtrl.InsertColumn(4 , _T("别名")		,  LVCFMT_CENTER	, 120);

	listCtrl.InsertColumn(5 , _T("发送报文数目"),  LVCFMT_CENTER	, 80);
	listCtrl.InsertColumn(6 , _T("发送报文大小"),  LVCFMT_CENTER	, 80);
	listCtrl.InsertColumn(7 , _T("接收报文数目"),  LVCFMT_CENTER	, 80);
	listCtrl.InsertColumn(8 , _T("接收报文大小"),  LVCFMT_CENTER	, 80);
	listCtrl.InsertColumn(9 , _T("端口状态")	,  LVCFMT_CENTER	, 80);

	listCtrl.SetExtendedStyle(listCtrl.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	CDevManager *pDevManager = GetDocument()->GetDeviceManager();
	CDeviceList *pDevList = NULL;

	pDevList = pDevManager->Get_DevList();


	POSITION pos;
	CDevice  *pDevice = NULL;
	int iRow = 1;
	CString strNo;
	CString strPortNo;
	CString strDevMode;
	CString strMac;
	CString strDevIp;
	CString strDevName;
	CString strPortStatus;
	int     iPortNum;

	CString szSendNum;
	CString szSendSize;
	CString szRecNum;
	CString szRecSize;

	unsigned long ulSendNum;
	unsigned long ulSendSize;
	unsigned long ulRecNum;
	unsigned long ulRecSize;

	CPortList *pPortList = NULL;
	CPort     *pPort = NULL;
	POSITION   portPos;

	pos = pDevList->GetHeadPosition();
	while(pos != NULL)
	{
		pDevice = pDevList->GetNext(pos);

		iPortNum = pDevice->Get_PortNum();
		pPortList = pDevice->Get_PortList();

		////////////////////////////////////////////////////////////
		portPos   = pPortList->GetHeadPosition();
		while(portPos != NULL)
		{
			pPort = pPortList->GetNext(portPos);

			ulSendNum  = 0;
	        ulSendSize = 0;
	        ulRecNum   = 0;
	        ulRecSize  = 0;

            /***********************************************************************************************************/
			//串口参数列表框填值
			/***********************************************************************************************************/
			if (pPort != NULL)
			{

				strNo.Format("%d", iRow);
				int nItem = listCtrl.InsertItem(iRow, (LPCTSTR)strNo);

				strDevMode = pDevice->Get_DevMode();
				listCtrl.SetItemText(nItem, 1, (LPCTSTR)strDevMode);

				strDevIp  = IP_DW2STR(pDevice->Get_DevIP());
				listCtrl.SetItemText(nItem, 2, (LPCTSTR)strDevIp);

				//3串口
				strPortNo.Format("%d", pPort->Get_Index());
				listCtrl.SetItemText(nItem, 3,(LPCTSTR)strPortNo);
	    
				//4串口别名
				listCtrl.SetItemText(nItem, 4,(LPCTSTR)pPort->Get_PortName());

				//5 , _T("发送报文数目")
				ulSendNum += pPort->m_pChannelStatic1->Get_SendNum();
				ulSendNum += pPort->m_pChannelStatic2->Get_SendNum();
				ulSendNum += pPort->m_pChannelStatic3->Get_SendNum();
				ulSendNum += pPort->m_pChannelStatic4->Get_SendNum();
				ulSendNum += pPort->m_pChannelStatic5->Get_SendNum();
				ulSendNum += pPort->m_pChannelStatic6->Get_SendNum();

				szSendNum.Format("%d", ulSendNum);
				listCtrl.SetItemText(nItem, 5, (LPCTSTR)szSendNum);

				//6 , _T("发送报文大小")
				ulSendSize += pPort->m_pChannelStatic1->Get_SendSize();
				ulSendSize += pPort->m_pChannelStatic2->Get_SendSize();
				ulSendSize += pPort->m_pChannelStatic3->Get_SendSize();
				ulSendSize += pPort->m_pChannelStatic4->Get_SendSize();
				ulSendSize += pPort->m_pChannelStatic5->Get_SendSize();
				ulSendSize += pPort->m_pChannelStatic6->Get_SendSize();

				szSendSize.Format("%d", ulSendSize);
				listCtrl.SetItemText(nItem, 6, (LPCTSTR)szSendSize);
				

				//7 , _T("接收报文数目")
				ulRecNum += pPort->m_pChannelStatic1->Get_RecNum();
				ulRecNum += pPort->m_pChannelStatic2->Get_RecNum();
				ulRecNum += pPort->m_pChannelStatic3->Get_RecNum();
				ulRecNum += pPort->m_pChannelStatic4->Get_RecNum();
				ulRecNum += pPort->m_pChannelStatic5->Get_RecNum();
				ulRecNum += pPort->m_pChannelStatic6->Get_RecNum();

				szRecNum.Format("%d", ulRecNum);
				listCtrl.SetItemText(nItem, 7, (LPCTSTR)szRecNum);
				
				//8 , _T("接收报文大小")
	            ulRecSize += pPort->m_pChannelStatic1->Get_RecSize();
				ulRecSize += pPort->m_pChannelStatic2->Get_RecSize();
				ulRecSize += pPort->m_pChannelStatic3->Get_RecSize();
				ulRecSize += pPort->m_pChannelStatic4->Get_RecSize();
				ulRecSize += pPort->m_pChannelStatic5->Get_RecSize();
				ulRecSize += pPort->m_pChannelStatic6->Get_RecSize();

				szRecSize.Format("%d", ulRecSize);
				listCtrl.SetItemText(nItem, 8, (LPCTSTR)szRecSize);

				//9, _T("状态")	
				//串口状态
				int iPortSwitch = pPort->Get_PortSwitch();
				if (iPortSwitch == SERIALSERV_SWITCH_OFF)
				{
					strPortStatus.Format("关闭");
				}
				else
				{
					strPortStatus.Format("打开");
				}

				//if ( pPort->Get_PortStatus() == 1) 
				//{
				//	strPortStatus.Format("正常");
				//}
				//else
				//{
				//	strPortStatus.Format("关闭");
				//}
				listCtrl.SetItemText(nItem, 9, (LPCTSTR)strPortStatus);
			}
			iRow++;
		}
			
	}

	//SetTimer(TIME_MONITOR, TIME_INTERVAL_MONITOR, NULL);

}


// CARTMonitor 诊断

#ifdef _DEBUG
void CARTMonitor::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CARTMonitor::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CARTMonitor 消息处理程序


void CARTMonitor::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
}

CARTDoc* CARTMonitor::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CARTDoc)));
	return (CARTDoc*)m_pDocument;
}

void CARTMonitor::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint        point;
	int           iItem;
	CListCtrl& ListCtrl = GetListCtrl();
	LVHITTESTINFO lvo;
	CString       szDevIP;
	CString       szPort;
	DWORD         dwIP;
	int           iPort;
	
	GetCursorPos(&point);
	ScreenToClient(&point);

	lvo.pt = point;
	lvo.flags = LVHT_ABOVE ;

	iItem = ListCtrl.SubItemHitTest(&lvo);

	if (iItem != -1)
	{   
		szDevIP = ListCtrl.GetItemText(iItem, 2);
		if (szDevIP.IsEmpty())
		{
			return ;
		}

		dwIP = IP_STR2DW((LPCTSTR)szDevIP);

		ASSERT(dwIP !=0 );

		szPort = ListCtrl.GetItemText(iItem, 3);

		iPort = atoi((LPSTR)(LPCTSTR)szPort);

		CARTDlgMonitor DlgMonitor(this, dwIP, iPort);

		if (DlgMonitor.DoModal() == IDOK)
		{

		}
	}
}

LRESULT CARTMonitor::OnTaskComplete(WPARAM wp, LPARAM lp)
{
	m_bRunning = FALSE;
	CARTDoc *pDoc = GetDocument();

	pDoc->UpdateAllViews(NULL);
	return 0;
}


void CARTMonitor::OnTimer(UINT_PTR nIDEvent)
{
	if (!m_bRunning) 
	{
			//创建SearchTask, 先挂起
		m_pMonitorTask = (CARTMonitorTask*) AfxBeginThread(RUNTIME_CLASS(CARTMonitorTask), 
															THREAD_PRIORITY_NORMAL,
															0,
															CREATE_SUSPENDED);
	
		m_pMonitorTask->SetOwner(this);
		m_pMonitorTask->ResumeThread();
		m_pMonitorTask->PostThreadMessage(WM_MONITOR, NULL,NULL);
		m_bRunning = TRUE;

	}
	
	CListView::OnTimer(nIDEvent);
}


void CARTMonitor::OnDestroy()
{
	CListView::OnDestroy();

	KillTimer(TIME_MONITOR);
}

