// ARTPortMonitor.cpp : 实现文件
//

#include "stdafx.h"
#include "ART.h"
#include "ARTDoc.h"
#include "ARTPortMonitor.h"


// CARTPortMonitor

IMPLEMENT_DYNCREATE(CARTPortMonitor, CListView)

CARTPortMonitor::CARTPortMonitor()
{

}

CARTPortMonitor::~CARTPortMonitor()
{
}

BEGIN_MESSAGE_MAP(CARTPortMonitor, CListView)
END_MESSAGE_MAP()


BOOL CARTPortMonitor::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

void CARTPortMonitor::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.InsertColumn(0, _T("No.")		    ,  LVCFMT_LEFT, 50);	
	listCtrl.InsertColumn(1, _T("设备类型")   	,  LVCFMT_LEFT, 150);
	listCtrl.InsertColumn(2, _T("MAC地址")      ,  LVCFMT_LEFT, 150);
	listCtrl.InsertColumn(3, _T("IP地址")       ,  LVCFMT_LEFT, 150);
	listCtrl.InsertColumn(4, _T("串口号")       ,  LVCFMT_LEFT, 50);
	listCtrl.InsertColumn(5, _T("串口工作模式") ,  LVCFMT_LEFT, 120);
	listCtrl.InsertColumn(6, _T("串口状态") ,  LVCFMT_LEFT, 80);

	listCtrl.SetExtendedStyle(listCtrl.GetExtendedStyle()
		 |LVS_EX_FULLROWSELECT);

	CString strNo;
	CString strDevType;
	CString strSysnip;
	CString strMac;
	CString strCOMPPortNo;
	CString strCOMPPortMode;
	CString strStatus;
	for (int i=0; i<20; i++)
	{
		strNo.Format("%d", i+1);
		int nItem = listCtrl.InsertItem(i, strNo.GetBuffer(0));

		strDevType.Format("SC508%d", i);
		listCtrl.SetItemText(nItem, 1, strDevType.GetBuffer(0));

		strMac.Format("00-80-27-20-78-%d",i+10);
		listCtrl.SetItemText(nItem, 2, strMac.GetBuffer(0));

		strSysnip.Format("192.168.1.%d",i+1);
		listCtrl.SetItemText(nItem, 3, strSysnip.GetBuffer(0));

		strCOMPPortNo.Format("%d", i%8);
		listCtrl.SetItemText(nItem, 4, strCOMPPortNo.GetBuffer(0));

		strCOMPPortMode.Format("TCP Server Mode");
		listCtrl.SetItemText(nItem, 5, strCOMPPortMode.GetBuffer(0));

		strStatus.Format("正常", i+1);
		listCtrl.SetItemText(nItem, 6, strStatus.GetBuffer(0));
	}

}
// CARTPortMonitor 诊断

#ifdef _DEBUG
void CARTPortMonitor::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CARTPortMonitor::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CARTPortMonitor 消息处理程序


void CARTPortMonitor::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
}

CARTDoc* CARTPortMonitor::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CARTDoc)));
	return (CARTDoc*)m_pDocument;
}