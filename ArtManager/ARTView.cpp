// ARTView.cpp : ʵ���ļ�
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


// CARTView ��ͼ

void CARTView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CARTView ���

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


// CARTView ��Ϣ�������
