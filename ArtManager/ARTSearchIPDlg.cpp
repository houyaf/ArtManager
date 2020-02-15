// ARTSearchIPDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ART.h"
#include "ARTSearchIPDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ARTDoc.h"


IMPLEMENT_DYNAMIC(CARTSearchIPDlg, CARTSearchDlg)

CARTSearchIPDlg::CARTSearchIPDlg(CWnd* pParent /*=NULL*/)
	: CARTSearchDlg(CARTSearchIPDlg::IDD, pParent)
	, m_iFoundedNum(0)
	, m_dwSearchIP(0xC0A80104)
	, m_bComplete(TRUE)
	, m_iExit(0)
{

}

CARTSearchIPDlg::~CARTSearchIPDlg()
{
	if (m_pSearchTask!= NULL)
	{
		delete m_pSearchTask;
	}
	m_pSearchTask = NULL;
}

void CARTSearchIPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEVICE, m_Ctrl_List_Device);
	DDX_Control(pDX, IDC_STATIC_SEARCH_RESULT, m_Ctrl_Label_SearchResult);
	DDX_Control(pDX, IDC_BTN_SEARCH, m_Ctrl_Btn_Search);
	DDX_IPAddress(pDX, IDC_IPADDRESS_IP_SEARCH, m_dwSearchIP);
	DDX_Control(pDX, IDC_SEARCHING_STATIC, m_Ctrl_Label_Searching);
}


BEGIN_MESSAGE_MAP(CARTSearchIPDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CARTSearchIPDlg::OnBnClickedBtnSearch)
	ON_MESSAGE(WM_COMPLETE , OnTaskComplete )
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CARTSearchIPDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CARTSearchIPDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CARTSearchIPDlg 消息处理程序


void CARTSearchIPDlg::OnBnClickedBtnSearch()
{
	UpdateData(TRUE);
	
	if (m_dwSearchIP == 0)
	{
		MessageBox(_T("IP地址不能为0！"),_T("提示信息"), MB_OK);
		return ;
	}

	if (m_bComplete)
	{
		//创建SearchTask, 先挂起
		m_pSearchTask = (CARTDevSearchTask*) AfxBeginThread(RUNTIME_CLASS(CARTDevSearchTask), 
															THREAD_PRIORITY_NORMAL,
															0,
															CREATE_SUSPENDED);
	
		m_pSearchTask->SetOwner(this);
	    m_pSearchTask->Set_SearchType(DEVICE_SEARCH_BY_IP);
		m_pSearchTask->Set_SearchIP(m_dwSearchIP);
		m_pSearchTask->ResumeThread();
		m_pSearchTask->PostThreadMessage(WM_SEARCH, NULL,NULL);
		m_Ctrl_Btn_Search.SetWindowText(_T("停止搜索")); 
		m_bComplete = FALSE;
	}
	else
	{
		m_pSearchTask->m_bDone = TRUE;
		m_Ctrl_Btn_Search.EnableWindow(FALSE);
	}

}

LRESULT CARTSearchIPDlg::OnTaskComplete(WPARAM wp, LPARAM lp)
{
	CString szSearchResult;

	m_Ctrl_Btn_Search.EnableWindow(TRUE);
	m_Ctrl_Btn_Search.SetWindowText(_T("重新搜索"));
	m_Ctrl_Label_Searching.SetWindowText(_T(""));

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

	m_pSearchTask = NULL;

    CARTDoc     *pDoc = GetDocument();
	CLogManager *pLogManager = pDoc->GetLogManager();
	CString      szLog;

	ASSERT(pDoc!= NULL);
	ASSERT(pLogManager!= NULL);
	
	szLog.Format("根据IP搜索设备:%s",(LPCTSTR)szSearchResult);
	pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);
	
	pDoc->UpdateAllViews(NULL);

	return 0;
}

BOOL CARTSearchIPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Ctrl_Label_Searching.SetBkColor(RGB(0xff,0xff,0xff));

	int  iCount;
	CHeaderCtrl *pHeadCtrl = m_Ctrl_List_Device.GetHeaderCtrl();

	if (pHeadCtrl != NULL)
	{
		iCount = pHeadCtrl->GetItemCount();
		
		for (int i=0; i< iCount; i++)
		{
			m_Ctrl_List_Device.DeleteColumn(0);
		}

		m_Ctrl_List_Device.DeleteAllItems();
	}

	m_Ctrl_List_Device.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT|LVS_SHOWSELALWAYS);
	m_Ctrl_List_Device.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);

	m_Ctrl_List_Device.InsertColumn(0, _T("设备IP")     , LVCFMT_LEFT , 100);
	m_Ctrl_List_Device.InsertColumn(1, _T("设备类型")   , LVCFMT_LEFT , 150);
	m_Ctrl_List_Device.InsertColumn(2, _T("设备名称")   , LVCFMT_LEFT , 150);
	
	m_Ctrl_Label_Searching.SetWindowTextA(_T(""));


	return TRUE; 
}

BOOL CARTSearchIPDlg::ResetListBox()
{
	
	return TRUE;
}

void CARTSearchIPDlg::SetPorgressInfo(LPCTSTR szInfo)
{
	m_Ctrl_Label_Searching.SetWindowText(szInfo);
	
}

void CARTSearchIPDlg::AddFoundDevice(CDevice *pDevice)
{
	CString szScanResult;
	
	ASSERT(pDevice);

	m_Ctrl_List_Device.DeleteAllItems();

	m_Ctrl_List_Device.InsertItem(0,  (LPCTSTR)IP_DW2STR(pDevice->Get_DevIP()));
	m_Ctrl_List_Device.SetItemText(0, 1, (LPCTSTR)pDevice->Get_DevMode());
    m_Ctrl_List_Device.SetItemText(0, 2, (LPCTSTR)pDevice->Get_DevName());

	m_iFoundedNum = 1;

	szScanResult.Format(_T("已发现1台设备"));
	m_Ctrl_Label_SearchResult.SetWindowText((LPCTSTR)szScanResult);
}

void CARTSearchIPDlg::OnClose()
{
    if (!m_bComplete)
	{
	    HANDLE hp = m_pSearchTask->m_hThread;

		if (WaitForSingleObject(hp, 1) != WAIT_OBJECT_0)
        {
            TerminateThread(hp,0);
        }
	}

	CDialog::OnClose();

}

CARTDoc *CARTSearchIPDlg::GetDocument()
{
	CFrameWnd *pFrm = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);

	ASSERT(pFrm);

	CView *pView = pFrm->GetActiveView();

	CARTDoc *pDoc = (CARTDoc *)(pView->GetDocument());

	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CARTDoc)));

	return pDoc;
}


CDevManager *CARTSearchIPDlg::GetDevManger()
{
	CFrameWnd *pFrm = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);

	ASSERT(pFrm);

	CView *pView = pFrm->GetActiveView();

	CARTDoc *pDoc = (CARTDoc *)(pView->GetDocument());

	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CARTDoc)));

	return pDoc->GetDeviceManager();
}


void CARTSearchIPDlg::OnBnClickedOk()
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
			szLog.Format("终止按IP搜索，已搜索到%d台设备!",m_iFoundedNum);
			pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);
        }
	}

	
	CDialog::OnOK();
}


void CARTSearchIPDlg::OnBnClickedCancel()
{
	if (!m_bComplete)
	{
	    HANDLE hp = m_pSearchTask->m_hThread;

		if (WaitForSingleObject(hp, 1) != WAIT_OBJECT_0)
        {
            TerminateThread(hp,0);
        }
	}
	
	CDialog::OnCancel();
}
