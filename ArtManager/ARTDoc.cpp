/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTDoc.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: CARTDoc 类的实现,文档类用于管理显示的数据。
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


// CARTDoc 构造/析构

CARTDoc::CARTDoc()
{
	// TODO: 在此添加一次性构造代码
	m_ulFunctionMode = 0 ;
	m_pDevManager = new CDevManager();

	m_pLogManger  = new CLogManager();
}

CARTDoc::~CARTDoc()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pDevManager->ClearDevices();
	delete m_pDevManager ;

	m_pLogManger->ClearLog();
	delete m_pLogManger;
}

BOOL CARTDoc::OnNewDocument()
{
	//if (!CDocument::OnNewDocument())
	//	return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

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

// CARTDoc 序列化

void CARTDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

// CARTDoc 诊断

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


// CARTDoc 命令
