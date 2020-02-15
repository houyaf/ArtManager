
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "ART.h"
#include "ARTDoc.h"
#include "MainFrm.h"
#include "ARTTaskView.h"
#include "ARTConfigView.h"
#include "ARTLog.h"
#include "ARTMonitor.h"
#include "ARTPortMonitor.h"
#include "ARTCOMMapping.h"
#include "ARTCOMConsole.h"
#include "ARTMonitorTask.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_SECOND    1
#define TIMER_MONITOR   2

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI_RANGE(ID_CONFIG, ID_COMMAPING, &CMainFrame::OnUpdateFuncSelect)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TIME, OnUpdateStatusTime)
	
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_COMMAND(ID_CONSOLE, &CMainFrame::OnConsole)
	ON_MESSAGE(WM_COMPLETE , OnTaskComplete )

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_TIME,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,

};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
:m_pMonitorTask(NULL)
,m_bRunning(FALSE)
{
	// TODO: 在此添加成员初始化代码
	m_bSplitterCreated = FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CImageList imglist;
	CBitmap bmp ;

	imglist.Create(32,32,ILC_COLOR32|ILC_MASK , 5, 2);

	bmp.LoadBitmap(IDB_EXIT);
	imglist.Add(&bmp, RGB(255,255,255));
	bmp.DeleteObject();

	bmp.LoadBitmap(IDB_CONFIG);
	imglist.Add(&bmp, RGB(255,255,255));
	bmp.DeleteObject();

	bmp.LoadBitmap(IDB_MONITOR);
	imglist.Add(&bmp, RGB(255,255,255));
	bmp.DeleteObject();

	bmp.LoadBitmap(IDB_PORTMONITOR);
	imglist.Add(&bmp, RGB(255,255,255));
	bmp.DeleteObject();

	bmp.LoadBitmap(IDB_PORTMAPP);
	imglist.Add(&bmp, RGB(255,255,255));
	bmp.DeleteObject();

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT|TBSTYLE_TRANSPARENT|TBSTYLE_LIST) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	m_wndToolBar.GetToolBarCtrl().SetImageList(&imglist);
	imglist.Detach();

	m_wndToolBar.SetButtonText(0, _T("退出软件"));
	m_wndToolBar.SetButtonText(2, _T("设备配置"));
	m_wndToolBar.SetButtonText(4, _T("设备监控"));
	//m_wndToolBar.SetButtonText(6, _T("监控端口"));
	//m_wndToolBar.SetButtonText(8, _T("串口映射"));

	
	//m_wndToolBar.SetButtonInfo(0, ID_APP_EXIT, TBBS_BUTTON, 0);
	
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("未能创建对话栏\n");
		return -1;		// 未能创建
	}

	if (!m_wndReBar.Create(this) || !m_wndReBar.AddBar(&m_wndToolBar) || !m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("未能创建 Rebar\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneInfo(1,ID_INDICATOR_TIME , SBPS_NORMAL , 120);

	// TODO: 如果不需要工具提示，则将此移除
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	SetTimer(TIMER_SECOND, 1000, NULL);
	return 0;
}


/*****************************************************************************
 函 数 名  : OnCreateClient
 功能描述  : CMainFrame 消息处理程序, ON_CREATECLIENT消息处理
 输入参数  : ……
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
******************************************************************************/
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs,
	CCreateContext* pContext)
{
	CRect rect;
	CARTDoc *pDoc           = (CARTDoc *) GetActiveDocument();

	GetClientRect(&rect);

	// 创建拆分窗口
	if (!m_wndSplitter.CreateStatic(this,2,1))
		return FALSE;

	m_wndSplitter.SetRowInfo(0, rect.Height()-200 ,  0);
	m_wndSplitter.SetRowInfo(1, 200               ,  0);

	if (!m_wndFuncSplitter.CreateStatic(&m_wndSplitter,1 ,2, WS_CHILD|WS_VISIBLE, m_wndSplitter.IdFromRowCol(0,0)))
		return FALSE;

	if (!m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CARTLog), CSize(rect.Width() , 200), pContext) )
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	if (!m_wndFuncSplitter.CreateView(0, 0, RUNTIME_CLASS(CARTTaskView)  , CSize(200              , rect.Height()-200), pContext)||
		!m_wndFuncSplitter.CreateView(0, 1, RUNTIME_CLASS(CARTConfigView), CSize(rect.Width()-200 , rect.Height()-200), pContext))
	{
		m_wndFuncSplitter.DestroyWindow();
		return FALSE;
	}

	m_bSplitterCreated = TRUE;

	//m_nCurView = pDoc->m_ulFunctionMode;
	//CreateFuncView(m_nCurView);

	//创建SearchTask, 先挂起
	m_pMonitorTask = (CARTMonitorTask*) AfxBeginThread(RUNTIME_CLASS(CARTMonitorTask), 
														THREAD_PRIORITY_NORMAL,
														0,
														CREATE_SUSPENDED);
	
	m_pMonitorTask->SetOwner(this);

	SetTimer(TIMER_MONITOR, TIME_INTERVAL_MONITOR, NULL);


	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.cx = 1024;
	cs.cy = 720;

	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style &= ~FWS_ADDTOTITLE;
	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


/*****************************************************************************
 函 数 名  : OnUpdateFuncSelect
 功能描述  : CMainFrame 消息处理程序, ON_UPDATE_COMMAND_UI_RANGE消息处理
 输入参数  : ……
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
******************************************************************************/
void CMainFrame::OnUpdateFuncSelect(CCmdUI* pCmdUI)
{
	BOOL bChecked = FALSE;
	CARTDoc *pDoc           = (CARTDoc *) GetActiveDocument();

	if (!pCmdUI)
		return;

	if (!pDoc)
		return ;

	CWnd* pWnd = m_wndFuncSplitter.GetPane(0, 1);
	if (pWnd == NULL)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{

		switch (pCmdUI->m_nID)
		{
			case ID_CONFIG:
				m_nCurView = pDoc->m_ulFunctionMode ;
				bChecked = (m_nCurView == 0);
				break;

			case ID_MONITOR:
				bChecked = (m_nCurView == 1);
				m_nCurView = pDoc->m_ulFunctionMode ;
				break;

			case ID_PORTMONITOR:
				bChecked = (m_nCurView == 2);
				m_nCurView = pDoc->m_ulFunctionMode ;
				break;

			case ID_COMMAPING:
				bChecked = (m_nCurView == 3);
				m_nCurView = pDoc->m_ulFunctionMode ;
				break;

			default:
				bChecked = FALSE;
				break;
		}
		pCmdUI->SetRadio(bChecked);

	}
	
	return ;
}

/*****************************************************************************
 函 数 名  : CreateFuncView
 功能描述  : 创建splitwnd中的功能区view.
 输入参数  : iFuncMode 功能模式 
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
******************************************************************************/
void CMainFrame::CreateFuncView (int iFuncMode)
{
	CRect rect;
	CSize viewSize;
	CView *pWnd ;
	CCreateContext cc ;
	
	GetClientRect(&rect);
	

	if (m_nCurView == iFuncMode )
		return ;

	m_nCurView = iFuncMode ;

	pWnd = (CView *)m_wndFuncSplitter.GetPane(0,1);
	if (pWnd != NULL)
	{
	    m_wndFuncSplitter.DeleteView(0,1);
	}

	//CWnd* pPane00 = m_wndFuncSplitter.GetPane(0, 0);


	cc.m_pCurrentDoc    = this->GetActiveDocument();

	switch (m_nCurView)
	{
			case 0:

				viewSize.cx = rect.Width()- 200 ;
				viewSize.cy = rect.Height()-200 ;
				cc.m_pNewViewClass  = RUNTIME_CLASS(CARTConfigView);
				m_wndFuncSplitter.CreateView(0, 1, RUNTIME_CLASS(CARTConfigView) , viewSize, &cc);
				break;

			case 1:
				//pPane00->ShowWindow(SW_SHOWNA);

				viewSize.cx = rect.Width() ;
				viewSize.cy = rect.Height() ;
				cc.m_pNewViewClass  = RUNTIME_CLASS(CARTMonitor);
				m_wndFuncSplitter.CreateView(0, 1, RUNTIME_CLASS(CARTMonitor)    , viewSize, &cc);
				break;

			case 2:
				cc.m_pNewViewClass  = RUNTIME_CLASS(CARTPortMonitor);
				m_wndFuncSplitter.CreateView(0, 1, RUNTIME_CLASS(CARTPortMonitor) , viewSize, &cc);
				break;

			case 3:
				cc.m_pNewViewClass  = RUNTIME_CLASS(CARTCOMMapping);
				m_wndFuncSplitter.CreateView(0, 1, RUNTIME_CLASS(CARTCOMMapping)  , viewSize, &cc);
				break;

	}
	pWnd = (CView *)m_wndFuncSplitter.GetPane(0,1);
	pWnd->OnInitialUpdate();

	m_wndFuncSplitter.RecalcLayout();

	return ;
}

/*****************************************************************************
 函 数 名  : OnSize
 功能描述  : CMainFrame 消息处理程序, WM_SIZE消息处理
 输入参数  : ……
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
******************************************************************************/
void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CRect rect;
	int   iWidth, iHeight;

	CFrameWnd::OnSize(nType, cx, cy);

	GetClientRect(&rect);
	iHeight = rect.Height();
	iWidth  = rect.Width();


	if ( GetSafeHwnd() != NULL && ::IsWindow( m_wndSplitter.m_hWnd ) )
    {
		if (m_bSplitterCreated)
		{
			if (iHeight > 200 )
			{
		    
				m_wndSplitter.SetRowInfo(0, iHeight-200, 0);
				m_wndSplitter.RecalcLayout();
			}
			if (iWidth > 200 )
			{
				m_wndFuncSplitter.SetColumnInfo(0, 200, 0);
				m_wndFuncSplitter.RecalcLayout();
			}
		}
    }
}

void CMainFrame::OnUpdateStatusTime(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


CDocument* CMainFrame::GetActiveDocument()
{
	// TODO: 在此添加专用代码和/或调用基类
	return CFrameWnd::GetActiveDocument();
}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString szTime ;
	CTime  tTime = CTime::GetCurrentTime();
	

	switch (nIDEvent)
	{
		case TIMER_SECOND:
			
			szTime = tTime.Format(_T("%Y-%m-%d %H:%M:%S"));
			m_wndStatusBar.SetPaneText(1, szTime);
			
			break;

		case TIMER_MONITOR: 

			if (!m_bRunning) 
			{
					
				m_pMonitorTask->ResumeThread();
				m_pMonitorTask->PostThreadMessage(WM_MONITOR, NULL,NULL);
				m_bRunning = TRUE;

			}

			break;
		default:
			break;
	}

	CFrameWnd::OnTimer(nIDEvent);
}


void CMainFrame::OnDestroy()
{
	CFrameWnd::OnDestroy();

	KillTimer(TIMER_SECOND);
	KillTimer(TIMER_MONITOR);
}


void CMainFrame::OnConsole()
{
	// TODO: 在此添加命令处理程序代码
	CARTCOMConsole ConsoleDlg;

	if (ConsoleDlg.DoModal() == IDOK)
	{

	}
}

LRESULT CMainFrame::OnTaskComplete(WPARAM wp, LPARAM lp)
{
	m_bRunning = FALSE;
	CARTDoc *pDoc = (CARTDoc *)GetActiveDocument();

	pDoc->UpdateAllViews(NULL);
	return 0;
}