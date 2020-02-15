/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTCOMMapping.cpp
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: CARTCOMMappingʵ���ļ� 
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/

#include "stdafx.h"
#include "ART.h"
#include "ARTDoc.h"
#include "ARTCOMMapping.h"


// CARTCOMMapping

IMPLEMENT_DYNCREATE(CARTCOMMapping, CListView)

CARTCOMMapping::CARTCOMMapping()
{

}

CARTCOMMapping::~CARTCOMMapping()
{
}

BEGIN_MESSAGE_MAP(CARTCOMMapping, CListView)
END_MESSAGE_MAP()

BOOL CARTCOMMapping::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

void CARTCOMMapping::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	
	// TODO: ���� GetListCtrl() ֱ�ӷ��� ListView ���б�ؼ���
	//  �Ӷ������������ ListView��
	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.InsertColumn(0, _T("No.")		,  LVCFMT_LEFT, 50);	
	listCtrl.InsertColumn(1, _T("�豸����")	,  LVCFMT_LEFT, 150);
	listCtrl.InsertColumn(2, _T("MAC��ַ")  ,  LVCFMT_LEFT, 150);
	listCtrl.InsertColumn(3, _T("IP��ַ")   ,  LVCFMT_LEFT, 150);
	listCtrl.InsertColumn(4, _T("���⴮��") ,  LVCFMT_LEFT, 200);


	listCtrl.SetExtendedStyle(listCtrl.GetExtendedStyle()
		 |LVS_EX_FULLROWSELECT);

	CString strNo;
	CString strDevType;
	CString strSysname;
	CString strSysnip;
	CString strMac;

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

		strSysname.Format("COM%d", i+1);
		listCtrl.SetItemText(nItem, 4, strSysname.GetBuffer(0));
	}
		
}





// CARTCOMMapping ���

#ifdef _DEBUG
void CARTCOMMapping::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CARTCOMMapping::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// CARTCOMMapping ��Ϣ�������


void CARTCOMMapping::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���
}

CARTDoc* CARTCOMMapping::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CARTDoc)));
	return (CARTDoc*)m_pDocument;
}