/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTLog.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: CARTLog 类的实现,用于在SDI显示下方的LOG View。
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#include "stdafx.h"
#include "ART.h"
#include "ARTMsgLog.h"
#include "ARTMonitorLog.h"
#include "ARTLog.h"
#include "ARTDoc.h"


// CARTLog

IMPLEMENT_DYNCREATE(CARTLog, CTabView)

CARTLog::CARTLog()
{

}

CARTLog::~CARTLog()
{
}

BEGIN_MESSAGE_MAP(CARTLog, CTabView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CARTLog 诊断

#ifdef _DEBUG
void CARTLog::AssertValid() const
{
	CTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CARTLog::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CARTLog 消息处理程序


int CARTLog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	this->AddView(RUNTIME_CLASS(CARTMsgLog), _T("操作日志"), 3000);
    this->AddView(RUNTIME_CLASS(CARTMonitorLog), _T("监控日志"), 3000);
	
	return 0;
}


void CARTLog::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	
	// TODO: 在此添加专用代码和/或调用基类
	//CView *pView = 
	//CARTMsgLog *pView = (CARTMsgLog* )this->GetActiveView();
	//pView->OnInitialUpdate();

	
}


void CARTLog::OnInitialUpdate()
{
	CTabView::OnInitialUpdate();

	GetDocument()->m_LogView = this;

	// TODO: 在此添加专用代码和/或调用基类
}


CARTDoc* CARTLog::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CARTDoc)));
	return (CARTDoc*)m_pDocument;
}

void CARTLog::ShowLogView(int iLogType)
{
	this->SetActiveView(iLogType);
	
	return ;
}