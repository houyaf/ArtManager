/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTConfigView.cpp
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: CARTConfigView ���ʵ��
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ART.h"
#endif

#include "ARTDoc.h"
#include "ARTConfigView.h"
#include "ARTConfigDlg.h"
#include "ARTBasicPage.h"
#include "ARTPortPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CARTConfigView

IMPLEMENT_DYNCREATE(CARTConfigView, CListView)

BEGIN_MESSAGE_MAP(CARTConfigView, CListView)
	
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CARTConfigView::OnNMDblclk)
END_MESSAGE_MAP()

// CARTConfigView ����/����

CARTConfigView::CARTConfigView()
{
	// TODO: �ڴ˴���ӹ������

}

CARTConfigView::~CARTConfigView()
{
}

BOOL CARTConfigView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

void CARTConfigView::OnInitialUpdate()
{

	GetDocument()->m_RightView = this;

	CListView::OnInitialUpdate();
	
}

// CARTConfigView ���
#ifdef _DEBUG
void CARTConfigView::AssertValid() const
{
	CListView::AssertValid();
}

void CARTConfigView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CARTDoc* CARTConfigView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CARTDoc)));
	return (CARTDoc*)m_pDocument;
}
#endif //_DEBUG



void CARTConfigView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: �ڴ����ר�ô����/����û���
	// TODO: ���� GetListCtrl() ֱ�ӷ��� ListView ���б�ؼ���
	//  �Ӷ������������ ListView��
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


	listCtrl.InsertColumn(0, _T("No.")		,  LVCFMT_LEFT		, 50);	
	listCtrl.InsertColumn(1, _T("�豸����")	,  LVCFMT_LEFT		, 100);
	listCtrl.InsertColumn(3, _T("IP��ַ")   ,  LVCFMT_LEFT		, 150);
	listCtrl.InsertColumn(4, _T("�豸����") ,  LVCFMT_LEFT		, 150);
	listCtrl.InsertColumn(5, _T("MAC��ַ")  ,  LVCFMT_LEFT		, 150);
	listCtrl.InsertColumn(6, _T("�豸״̬") ,  LVCFMT_CENTER	, 80);


	listCtrl.SetExtendedStyle(listCtrl.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	
	CDevManager *pDevManager = GetDocument()->GetDeviceManager();
	CDeviceList *pDevList = NULL;

	pDevList = pDevManager->Get_DevList();


	POSITION pos;
	CDevice  *pDevice = NULL;
	int i = 1;
	CString strNo;
	CString strDevMode;
	CString strMac;
	CString strDevIp;
	CString strDevName;
	CString strDevStatus;

	pos = pDevList->GetHeadPosition();
	while(pos != NULL)
	{
		pDevice = pDevList->GetNext(pos);

		strNo.Format("%d", i);
		int nItem = listCtrl.InsertItem(i, (LPCTSTR)strNo);

		strDevMode = pDevice->Get_DevMode();
		listCtrl.SetItemText(nItem, 1, (LPCTSTR)strDevMode);

		strDevIp  = IP_DW2STR(pDevice->Get_DevIP());
		listCtrl.SetItemText(nItem, 2, (LPCTSTR)strDevIp);

		strDevName = pDevice->Get_DevName();
		listCtrl.SetItemText(nItem, 3, (LPCTSTR)strDevName);

		strMac    = pDevice->Get_DevMAC();
		listCtrl.SetItemText(nItem, 4, (LPCTSTR)strMac);

		if ( pDevice->Get_DevStatus() == 1) 
		{
			strDevStatus.Format("����");
		}
		else
		{
			strDevStatus.Format("����");
		}
		listCtrl.SetItemText(nItem, 5, (LPCTSTR)strDevStatus);

		i++;
	
	}
	
}

void CARTConfigView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint        point;
	int           iItem;
	CListCtrl& ListCtrl = GetListCtrl();
	LVHITTESTINFO lvo;
	CString       szDevIP;
	DWORD         dwIP;
	
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

		CARTConfigDlg ConfigDlg(this, dwIP);

		if (ConfigDlg.DoModal() == IDOK)
		{
			OnInitialUpdate();
		}
	}
	
	*pResult = 0;
}
