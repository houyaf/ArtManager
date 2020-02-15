/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTDoc.cpp
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: CARTDoc ���ʵ��,�ĵ������ڹ�����ʾ�����ݡ�
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
#include "ARTLog.h"
#include "MainFrm.h"
#include <propkey.h>




#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CARTDoc

IMPLEMENT_DYNCREATE(CARTDoc, CDocument)

BEGIN_MESSAGE_MAP(CARTDoc, CDocument)
	ON_COMMAND_RANGE(ID_CONFIG, ID_COMMAPING, &CARTDoc::OnFuncSelect)
END_MESSAGE_MAP()


// CARTDoc ����/����

CARTDoc::CARTDoc()
{
	// TODO: �ڴ����һ���Թ������
	m_ulFunctionMode = 0 ;
	m_pDevManager = new CDevManager();

	m_pLogManger  = new CLogManager();
}

CARTDoc::~CARTDoc()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_pDevManager->ClearDevices();
	delete m_pDevManager ;

	m_pLogManger->ClearLog();
	delete m_pLogManger;
}

BOOL CARTDoc::OnNewDocument()
{
	//if (!CDocument::OnNewDocument())
	//	return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}


void CARTDoc::OnFuncSelect(UINT nCommandID)
{
	ULONG ulPreMode;
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetMainWnd();
	CARTLog *pLogView = NULL;

	ulPreMode = m_ulFunctionMode ;

	switch (nCommandID)
	{
		case ID_CONFIG:
			m_ulFunctionMode = 0 ;
			break;

		case ID_MONITOR:
			m_ulFunctionMode = 1 ;
			break;


	}

	if (ulPreMode != m_ulFunctionMode)
	{
		pMainFrame->CreateFuncView(m_ulFunctionMode);
	    this->UpdateAllViews(NULL);

		ASSERT(m_LogView->IsKindOf(RUNTIME_CLASS(CARTLog)));

		pLogView = (CARTLog *)m_LogView;
		pLogView->ShowLogView(m_ulFunctionMode);
	}

	

	return ;
}

CDevManager *CARTDoc::GetDeviceManager()
{
	return m_pDevManager;
}

CLogManager *CARTDoc::GetLogManager()
{
	return m_pLogManger;
}

// CARTDoc ���л�

void CARTDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

// CARTDoc ���

#ifdef _DEBUG
void CARTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CARTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CARTDoc ����
