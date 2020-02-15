/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTLog.cpp
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: CARTLog ���ʵ��,������SDI��ʾ�·���LOG View��
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

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


// CARTLog ���

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


// CARTLog ��Ϣ�������


int CARTLog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	this->AddView(RUNTIME_CLASS(CARTMsgLog), _T("������־"), 3000);
    this->AddView(RUNTIME_CLASS(CARTMonitorLog), _T("�����־"), 3000);
	
	return 0;
}


void CARTLog::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	
	// TODO: �ڴ����ר�ô����/����û���
	//CView *pView = 
	//CARTMsgLog *pView = (CARTMsgLog* )this->GetActiveView();
	//pView->OnInitialUpdate();

	
}


void CARTLog::OnInitialUpdate()
{
	CTabView::OnInitialUpdate();

	GetDocument()->m_LogView = this;

	// TODO: �ڴ����ר�ô����/����û���
}


CARTDoc* CARTLog::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CARTDoc)));
	return (CARTDoc*)m_pDocument;
}

void CARTLog::ShowLogView(int iLogType)
{
	this->SetActiveView(iLogType);
	
	return ;
}