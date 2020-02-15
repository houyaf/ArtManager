/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTConfigView.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: CARTConfigView 类的实现
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CARTConfigView 构造/析构

CARTConfigView::CARTConfigView()
{
	// TODO: 在此处添加构造代码

}

CARTConfigView::~CARTConfigView()
{
}

BOOL CARTConfigView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

void CARTConfigView::OnInitialUpdate()
{

	GetDocument()->m_RightView = this;

	CListView::OnInitialUpdate();
	
}

// CARTConfigView 诊断
#ifdef _DEBUG
void CARTConfigView::AssertValid() const
{
	CListView::AssertValid();
}

void CARTConfigView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CARTDoc* CARTConfigView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CARTDoc)));
	return (CARTDoc*)m_pDocument;
}
#endif //_DEBUG



void CARTConfigView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	// TODO: 调用 GetListCtrl() 直接访问 ListView 的列表控件，
	//  从而可以用项填充 ListView。
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
	listCtrl.InsertColumn(1, _T("设备类型")	,  LVCFMT_LEFT		, 100);
	listCtrl.InsertColumn(3, _T("IP地址")   ,  LVCFMT_LEFT		, 150);
	listCtrl.InsertColumn(4, _T("设备名称") ,  LVCFMT_LEFT		, 150);
	listCtrl.InsertColumn(5, _T("MAC地址")  ,  LVCFMT_LEFT		, 150);
	listCtrl.InsertColumn(6, _T("设备状态") ,  LVCFMT_CENTER	, 80);


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
			strDevStatus.Format("正常");
		}
		else
		{
			strDevStatus.Format("掉线");
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
