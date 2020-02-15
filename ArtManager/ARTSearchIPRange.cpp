// ARTSearchIPRange.cpp : 实现文件
//

#include "stdafx.h"
#include "ART.h"
#include "ARTSearchIPRange.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ARTDoc.h"


IMPLEMENT_DYNAMIC(CARTSearchIPRange, CARTSearchDlg)

CARTSearchIPRange::CARTSearchIPRange(CWnd* pParent /*=NULL*/)
	: CARTSearchDlg(CARTSearchIPRange::IDD, pParent)
	, m_iFoundedNum(0)
	, m_dwSearchIPS(0xC0A85B01)
	, m_dwSearchIPE(0xC0A85BFE)
	, m_bComplete(TRUE)
	, m_iExit(0)
{

}

CARTSearchIPRange::~CARTSearchIPRange()
{
	if (m_pSearchTask!= NULL)
	{
		delete m_pSearchTask;
	}
	m_pSearchTask = NULL;
}

void CARTSearchIPRange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEVICE, m_Ctrl_List_Device);
	DDX_Control(pDX, IDC_STATIC_SEARCH_RESULT, m_Ctrl_Label_SearchResult);
	DDX_Control(pDX, IDC_BTN_SEARCH, m_Ctrl_Btn_Search);
	DDX_IPAddress(pDX, IDC_IPADDRESS1, m_dwSearchIPS);
	DDX_IPAddress(pDX, IDC_IPADDRESS2, m_dwSearchIPE);
	DDX_Control(pDX, IDC_SEARCHING_STATIC, m_Ctrl_Label_Searching);
}


BEGIN_MESSAGE_MAP(CARTSearchIPRange, CDialog)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CARTSearchIPRange::OnBnClickedBtnSearch)
	ON_MESSAGE(WM_COMPLETE, OnTaskComplete)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CARTSearchIPRange::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CARTSearchIPRange::OnBnClickedCancel)
END_MESSAGE_MAP()


// CARTSearchIPRange 消息处理程序


void CARTSearchIPRange::OnBnClickedBtnSearch()
{
	UpdateData(TRUE);
	m_Ctrl_Label_Searching.SetWindowText(_T(""));
	m_Ctrl_Label_SearchResult.SetWindowText(_T(""));

	m_Ctrl_List_Device.DeleteAllItems();

	if ((m_dwSearchIPE == 0) || (m_dwSearchIPS == 0))
	{
		MessageBox(_T("IP地址不能为0！"),_T("提示信息"), MB_OK);
		return ;
	}

	if (m_dwSearchIPE < m_dwSearchIPS )
	{
		MessageBox(_T("结速IP应该大于等于开始IP！"),_T("提示信息"), MB_OK);
		return ;
	}

	if ((m_dwSearchIPE - m_dwSearchIPS) > 1024 )
	{
		MessageBox(_T("IP地址范围不能大于1024！"),_T("提示信息"), MB_OK);
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
	    m_pSearchTask->Set_SearchType(DEVICE_SEARCH_BY_IPRANGE);
		m_pSearchTask->Set_SearchIPRange(m_dwSearchIPS, m_dwSearchIPE);
		m_pSearchTask->ResumeThread();
		m_pSearchTask->PostThreadMessage(WM_SEARCH, NULL,NULL);
		m_Ctrl_Btn_Search.SetWindowText(_T("停止搜索")); 
		m_bComplete = FALSE;
	}
	else
	{
		m_Ctrl_Btn_Search.EnableWindow(FALSE);
		m_pSearchTask->m_bDone = TRUE;
		m_Ctrl_Btn_Search.SetWindowText(_T("重新搜索"));
	}
}

LRESULT CARTSearchIPRange::OnTaskComplete(WPARAM wp, LPARAM lp)
{
	CString szSearchResult;

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

	m_iFoundedNum = 0;

	m_Ctrl_Label_SearchResult.SetWindowText((LPCTSTR)szSearchResult);
	m_bComplete = TRUE;
    
	HANDLE hp = m_pSearchTask->m_hThread;

	if (WaitForSingleObject(hp, 1) != WAIT_OBJECT_0)
    {
        TerminateThread(hp,0);
    }
	if (m_pSearchTask!= NULL)
	{
		delete m_pSearchTask;
	}

	m_pSearchTask = NULL;
	
	CARTDoc     *pDoc        = GetDocument();
	ASSERT(pDoc != NULL);
	CLogManager *pLogManager = pDoc->GetLogManager();
	ASSERT(pLogManager!= NULL);
	CString      szLog;
	
	szLog.Format("%s:%s","搜索计算机区域网设备:",(LPCTSTR)szSearchResult);
	pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);
	pDoc->UpdateAllViews(NULL);

	return 0;
}


BOOL CARTSearchIPRange::OnInitDialog()
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

	m_Ctrl_List_Device.InsertColumn(0, _T("设备IP")   , LVCFMT_LEFT , 100);
	m_Ctrl_List_Device.InsertColumn(1, _T("设备类型")   , LVCFMT_LEFT , 150);
	m_Ctrl_List_Device.InsertColumn(2, _T("设备名称")   , LVCFMT_LEFT , 150);
	
	m_Ctrl_Label_Searching.SetWindowTextA(_T(""));

	return TRUE;  

}


void CARTSearchIPRange::SetPorgressInfo(LPCTSTR szInfo)
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

void CARTSearchIPRange::AddFoundDevice(CDevice *pDevice)
{
	CString szScanResult ;

	ASSERT(pDevice);

	m_Ctrl_List_Device.InsertItem(m_iFoundedNum,  (LPCTSTR)IP_DW2STR(pDevice->Get_DevIP()));
	m_Ctrl_List_Device.SetItemText(m_iFoundedNum, 1, (LPCTSTR)pDevice->Get_DevMode());
    m_Ctrl_List_Device.SetItemText(m_iFoundedNum, 2, (LPCTSTR)pDevice->Get_DevName());
	m_iFoundedNum++;

	szScanResult.Format(_T("已发现%d台设备"), m_iFoundedNum);
	m_Ctrl_Label_SearchResult.SetWindowText((LPCTSTR)szScanResult);
}

void CARTSearchIPRange::OnClose()
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
	CDialog::OnClose();

}

CDevManager *CARTSearchIPRange::GetDevManger()
{
	CFrameWnd *pFrm = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);

	ASSERT(pFrm);

	CView *pView = pFrm->GetActiveView();

	CARTDoc *pDoc = (CARTDoc *)(pView->GetDocument());

	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CARTDoc)));

	return pDoc->GetDeviceManager();
}


CARTDoc *CARTSearchIPRange::GetDocument()
{
	CFrameWnd *pFrm = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);

	ASSERT(pFrm);

	CView *pView = pFrm->GetActiveView();

	CARTDoc *pDoc = (CARTDoc *)(pView->GetDocument());

	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CARTDoc)));

	return pDoc;
}



void CARTSearchIPRange::OnBnClickedOk()
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
			szLog.Format("终止按IP范围搜索，已搜索到%d台设备!",m_iFoundedNum);
			pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);

        }
	}

	
	
	pDoc->UpdateAllViews(NULL);
	CDialog::OnOK();
}


void CARTSearchIPRange::OnBnClickedCancel()
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
			szLog.Format("终止按IP范围搜索，已搜索到%d台设备!",m_iFoundedNum);
			pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);
        }
	}


	pDoc->UpdateAllViews(NULL);
	CDialog::OnCancel();
}
