// ARTPortMonitor.cpp : ʵ���ļ�
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

void CARTPortMonitor::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.InsertColumn(0, _T("No.")		    ,  LVCFMT_LEFT, 50);	
	listCtrl.InsertColumn(1, _T("�豸����")   	,  LVCFMT_LEFT, 150);
	listCtrl.InsertColumn(2, _T("MAC��ַ")      ,  LVCFMT_LEFT, 150);
	listCtrl.InsertColumn(3, _T("IP��ַ")       ,  LVCFMT_LEFT, 150);
	listCtrl.InsertColumn(4, _T("���ں�")       ,  LVCFMT_LEFT, 50);
	listCtrl.InsertColumn(5, _T("���ڹ���ģʽ") ,  LVCFMT_LEFT, 120);
	listCtrl.InsertColumn(6, _T("����״̬") ,  LVCFMT_LEFT, 80);

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

		strStatus.Format("����", i+1);
		listCtrl.SetItemText(nItem, 6, strStatus.GetBuffer(0));
	}

}
// CARTPortMonitor ���

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


// CARTPortMonitor ��Ϣ�������


void CARTPortMonitor::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���
}

CARTDoc* CARTPortMonitor::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CARTDoc)));
	return (CARTDoc*)m_pDocument;
}