/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTCOMMapping.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: CARTCOMMapping实现文件 
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

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
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS;
	return CListView::PreCreateWindow(cs);
}

void CARTCOMMapping::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	
	// TODO: 调用 GetListCtrl() 直接访问 ListView 的列表控件，
	//  从而可以用项填充 ListView。
	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.InsertColumn(0, _T("No.")		,  LVCFMT_LEFT, 50);	
	listCtrl.InsertColumn(1, _T("设备类型")	,  LVCFMT_LEFT, 150);
	listCtrl.InsertColumn(2, _T("MAC地址")  ,  LVCFMT_LEFT, 150);
	listCtrl.InsertColumn(3, _T("IP地址")   ,  LVCFMT_LEFT, 150);
	listCtrl.InsertColumn(4, _T("虚拟串口") ,  LVCFMT_LEFT, 200);


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





// CARTCOMMapping 诊断

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


// CARTCOMMapping 消息处理程序


void CARTCOMMapping::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
}

CARTDoc* CARTCOMMapping::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CARTDoc)));
	return (CARTDoc*)m_pDocument;
}