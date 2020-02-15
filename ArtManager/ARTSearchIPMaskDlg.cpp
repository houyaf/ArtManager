// ARTSearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ART.h"
#include "ARTSearchIPMaskDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ARTDoc.h"


// CARTSearchIPMaskDlg 对话框

IMPLEMENT_DYNAMIC(CARTSearchIPMaskDlg, CARTSearchDlg)

CARTSearchIPMaskDlg::CARTSearchIPMaskDlg(CWnd* pParent /*=NULL*/)
	: CARTSearchDlg(CARTSearchIPMaskDlg::IDD, pParent)
	, m_iFoundedNum(0)
	, m_bComplete(TRUE)
	, m_iExit(0)
{

}

CARTSearchIPMaskDlg::~CARTSearchIPMaskDlg()
{
	if (m_pSearchTask!= NULL)
	{
		delete m_pSearchTask;
	}
	m_pSearchTask = NULL;
}

void CARTSearchIPMaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_RESULT_STATIC, m_Ctrl_Label_SearchResult);
	DDX_Control(pDX, IDC_BTN_SEARCH, m_Ctrl_Btn_Search);
	DDX_Control(pDX, IDC_SEARCHING_STATIC, m_Ctrl_Label_Searching);
}


BEGIN_MESSAGE_MAP(CARTSearchIPMaskDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CARTSearchIPMaskDlg::OnBnClickedBtnSearch)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CARTSearchIPMaskDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CARTSearchIPMaskDlg::OnBnClickedCancel)
	ON_MESSAGE(WM_COMPLETE , OnTaskComplete )
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CARTSearchIPMaskDlg 消息处理程序


void CARTSearchIPMaskDlg::OnBnClickedBtnSearch()
{
	m_Ctrl_Label_Searching.SetWindowText(_T(""));
	m_Ctrl_Label_SearchResult.SetWindowText(_T(""));
	if (m_bComplete)
	{

		//创建SearchTask, 先挂起
		m_pSearchTask = (CARTDevSearchTask*) AfxBeginThread(RUNTIME_CLASS(CARTDevSearchTask), 
															THREAD_PRIORITY_NORMAL,
															0,
															CREATE_SUSPENDED);
	
		m_pSearchTask->SetOwner(this);
		m_pSearchTask->Set_SearchType(DEVICE_SEARCH_BY_IPMASK);
		m_pSearchTask->ResumeThread();
		m_pSearchTask->PostThreadMessage(WM_SEARCH, NULL,NULL);
		m_Ctrl_Btn_Search.SetWindowText(_T("停止搜索")); 
		m_bComplete = FALSE;
	}
	else
	{
		m_Ctrl_Btn_Search.EnableWindow(FALSE);
		m_pSearchTask->m_bDone = TRUE;
	}
}

LRESULT CARTSearchIPMaskDlg::OnTaskComplete(WPARAM wp, LPARAM lp)
{
	CString szSearchResult ;
	m_Ctrl_Btn_Search.EnableWindow(TRUE);
	m_Ctrl_Btn_Search.SetWindowText(_T("重新搜索"));
	
	SetPorgressInfo(_T("搜索完毕！"));

	if (m_iFoundedNum >0)
	{
		szSearchResult.Format(_T("共发现%d台设备。"), m_iFoundedNum);
	}
	else
	{
		szSearchResult.Format(_T("没有发现设备。"));
	}
	m_Ctrl_Label_SearchResult.SetWindowText((LPCTSTR)szSearchResult);

	m_bComplete = TRUE;
    
	HANDLE hp = m_pSearchTask->m_hThread;

	if (WaitForSingleObject(hp, 1) != WAIT_OBJECT_0)
    {
        TerminateThread(hp,0);
		
    }
		
	CARTDoc     *pDoc = GetDocument();
    ASSERT(pDoc != NULL);

	CLogManager *pLogManager = pDoc->GetLogManager();
	CString      szLog;

	ASSERT(pLogManager!= NULL);
	
	szLog.Format("%s:%s","搜索计算机区域网设备:",(LPCTSTR)szSearchResult);
	pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);
	pDoc->UpdateAllViews(NULL);

	return 0;
}


BOOL CARTSearchIPMaskDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_Ctrl_Label_Searching.SetBkColor(RGB(0xff,0xff,0xff));

	m_Ctrl_Label_Searching.SetWindowText(_T(""));

	return TRUE;  

}

void CARTSearchIPMaskDlg::SetPorgressInfo(LPCTSTR szInfo)
{
	CString szHistoryInfo;
	
	m_Ctrl_Label_Searching.GetWindowText(szHistoryInfo);
	if (!szHistoryInfo.IsEmpty())
	{
		szHistoryInfo.Append(_T("完成！"));
	}
	szHistoryInfo.Append(_T("\r\n"));
	szHistoryInfo.Append(_T(szInfo));

	m_Ctrl_Label_Searching.SetWindowText(szHistoryInfo);
}

void CARTSearchIPMaskDlg::AddFoundDevice(CDevice *pDevice)
{
	CString szScanResult;

	ASSERT(pDevice);

	m_iFoundedNum++;

	szScanResult.Format(_T("已发现%d台设备"), m_iFoundedNum);
	m_Ctrl_Label_SearchResult.SetWindowText((LPCTSTR)szScanResult);
}

void CARTSearchIPMaskDlg::OnClose()
{
    if (!m_bComplete)
	{
	    HANDLE hp = m_pSearchTask->m_hThread;

		if (WaitForSingleObject(hp, 1) != WAIT_OBJECT_0)
        {
            TerminateThread(hp,0);
        }
	}
	
	CARTDoc *pDoc = GetDocument();

	pDoc->UpdateAllViews(NULL);

	CDialog::OnClose();
}



void CARTSearchIPMaskDlg::OnBnClickedOk()
{
	
	CARTDoc     *pDoc        = GetDocument();
	ASSERT(pDoc != NULL);
	CLogManager *pLogManager = pDoc->GetLogManager();
	ASSERT(pLogManager!= NULL);
	CString      szLog;

	if (!m_bComplete)
	{
	    HANDLE hp = m_pSearchTask->m_hThread;

		if (WaitForSingleObject(hp, 1) != WAIT_OBJECT_0)
        {
            TerminateThread(hp,0);
			szLog.Format("终止区域网搜索，已搜索到%d台设备!",m_iFoundedNum);
			pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);
        }
	}
	
	pDoc->UpdateAllViews(NULL);
	CDialog::OnOK();
}


void CARTSearchIPMaskDlg::OnBnClickedCancel()
{
	if (!m_bComplete)
	{
	    HANDLE hp = m_pSearchTask->m_hThread;

		if (WaitForSingleObject(hp, 1) != WAIT_OBJECT_0)
        {
            TerminateThread(hp,0);
        }
	}

	CARTDoc * pDoc = GetDocument();
	
	pDoc->UpdateAllViews(NULL);
	CDialog::OnCancel();
}


void CARTSearchIPMaskDlg::OnDestroy()
{
	CARTSearchDlg::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

CDevManager *CARTSearchIPMaskDlg::GetDevManger()
{
	CFrameWnd *pFrm = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);

	ASSERT(pFrm);

    CView *pView = pFrm->GetActiveView();

	CARTDoc *pDoc = (CARTDoc *)(pView->GetDocument());

	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CARTDoc)));

	return pDoc->GetDeviceManager();
}


CARTDoc *CARTSearchIPMaskDlg::GetDocument()
{
	CFrameWnd *pFrm = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);

	ASSERT(pFrm);

    CView *pView = pFrm->GetActiveView();

	CARTDoc *pDoc = (CARTDoc *)(pView->GetDocument());

	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CARTDoc)));

	return pDoc;
}
