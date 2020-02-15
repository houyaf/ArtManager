// ARTView.cpp : 实现文件
//

#include "stdafx.h"
#include "ART.h"
#include "ARTView.h"


// CARTView

IMPLEMENT_DYNCREATE(CARTView, CView)

CARTView::CARTView()
{

}

CARTView::~CARTView()
{
}

BEGIN_MESSAGE_MAP(CARTView, CView)
END_MESSAGE_MAP()


// CARTView 绘图

void CARTView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CARTView 诊断

#ifdef _DEBUG
void CARTView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CARTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CARTView 消息处理程序
