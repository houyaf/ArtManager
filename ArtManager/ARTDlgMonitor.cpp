// ARTDlgMonitor.cpp : 实现文件
//

#include "stdafx.h"
#include "ARTDlgMonitor.h"
#include "afxdialogex.h"
#include "resource.h"
#include "MainFrm.h"
#include "ARTDoc.h"

#define TIME_CHANNELMONITOR   1

// CARTDlgMonitor 对话框
IMPLEMENT_DYNAMIC(CARTDlgMonitor, CDialog)

CARTDlgMonitor::CARTDlgMonitor(CWnd* pParent /*=NULL*/)
	: CDialog(CARTDlgMonitor::IDD, pParent)
{

}

CARTDlgMonitor::CARTDlgMonitor(CWnd* pParent , DWORD dwIP)
	: CDialog(CARTDlgMonitor::IDD, pParent)
	,m_dwDevIPSelected(dwIP)
	,m_iPortSelected(0)
{

}

CARTDlgMonitor::CARTDlgMonitor(CWnd* pParent , DWORD dwIP, int iPort)
	: CDialog(CARTDlgMonitor::IDD, pParent)
	,m_dwDevIPSelected(dwIP)
	,m_iPortSelected(iPort)
{

}


CARTDlgMonitor::~CARTDlgMonitor()
{

}

void CARTDlgMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHANNEL_STATIC, m_Ctrl_List_ChannelStatic);
}


BEGIN_MESSAGE_MAP(CARTDlgMonitor, CDialog)
	ON_BN_CLICKED(IDC_BTN_OK, &CARTDlgMonitor::OnBnClickedBtnOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CARTDlgMonitor 消息处理程序


void CARTDlgMonitor::OnBnClickedBtnOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}



/**************************************************************************************************
函 数 名 :GetDocument
功能描述 :获取CDocument指针
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
CARTDoc *CARTDlgMonitor::GetDocument()
{
	CMainFrame *pFrm = (CMainFrame *)AfxGetMainWnd();

	ASSERT(pFrm);

	CDocument *pDoc = pFrm->GetActiveDocument();

	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CARTDoc)));

	return (CARTDoc *)pDoc;
}


BOOL CARTDlgMonitor::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString szTitle;

	szTitle.Format(_T("统计：设备：%s－串口%d"),(LPCTSTR)IP_DW2STR(m_dwDevIPSelected), m_iPortSelected);
	SetWindowText((LPCTSTR)szTitle);


	int  iCount;
	CHeaderCtrl *pHeadCtrl = m_Ctrl_List_ChannelStatic.GetHeaderCtrl();

	if (pHeadCtrl != NULL)
	{
		iCount = pHeadCtrl->GetItemCount();
		
		for (int i=0; i< iCount; i++)
		{
			m_Ctrl_List_ChannelStatic.DeleteColumn(0);
		}

		m_Ctrl_List_ChannelStatic.DeleteAllItems();
	}

	m_Ctrl_List_ChannelStatic.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT|LVS_SHOWSELALWAYS);
	m_Ctrl_List_ChannelStatic.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);

	m_Ctrl_List_ChannelStatic.InsertColumn(0, _T("No.")				, LVCFMT_CENTER , 50);
	m_Ctrl_List_ChannelStatic.InsertColumn(1, _T("通道")				, LVCFMT_CENTER , 100);
	m_Ctrl_List_ChannelStatic.InsertColumn(2, _T("发送报文数目")		, LVCFMT_CENTER , 100);
	m_Ctrl_List_ChannelStatic.InsertColumn(3, _T("发送报文长度")     , LVCFMT_CENTER , 100);
	m_Ctrl_List_ChannelStatic.InsertColumn(4, _T("接收报文数目")		, LVCFMT_CENTER , 100);
	m_Ctrl_List_ChannelStatic.InsertColumn(5, _T("接收报文长度")		, LVCFMT_CENTER , 100);
	m_Ctrl_List_ChannelStatic.InsertColumn(6, _T("通道状态")			, LVCFMT_CENTER , 100);

	SetChannelStatic();

	SetTimer(TIME_CHANNELMONITOR, TIME_INTERVAL_MONITOR, NULL);

	return TRUE;  
}

void CARTDlgMonitor::SetChannelStaticData(int iRow, CChannelStatistics *pChannelStatic, unsigned char ucStatus)
{
	CString szNo;
	CString szChannelNo;
	CString szSendNum;
	CString szSendSize;
	CString szRecNum;
	CString szRecSize;
	CString szChannelStatus;
	int iItem;

	if (pChannelStatic == NULL)
	{
		return ;
	}

	szNo.Format("%d", iRow);
	iItem = m_Ctrl_List_ChannelStatic.InsertItem(iRow, (LPCTSTR)szNo);

	szChannelNo.Format("通道%d",pChannelStatic->Get_ChannelNO());
	m_Ctrl_List_ChannelStatic.SetItemText(iItem, 1, (LPCTSTR)szChannelNo);

	szSendNum.Format("%d", pChannelStatic->Get_SendNum());
	m_Ctrl_List_ChannelStatic.SetItemText(iItem, 2, (LPCTSTR)szSendNum);

	szSendSize.Format("%d", pChannelStatic->Get_SendSize());
	m_Ctrl_List_ChannelStatic.SetItemText(iItem, 3, (LPCTSTR)szSendSize);

	szRecNum.Format("%d", pChannelStatic->Get_RecNum());
	m_Ctrl_List_ChannelStatic.SetItemText(iItem, 4, (LPCTSTR)szRecNum);

	szRecSize.Format("%d", pChannelStatic->Get_RecSize());
	m_Ctrl_List_ChannelStatic.SetItemText(iItem, 5, (LPCTSTR)szRecSize);

	szRecSize.Format("%d", pChannelStatic->Get_RecSize());
	m_Ctrl_List_ChannelStatic.SetItemText(iItem, 5, (LPCTSTR)szRecSize);

	if (ucStatus == SERIALSERV_CHANNELSWITCH_ON)
	{
		m_Ctrl_List_ChannelStatic.SetItemText(iItem, 6, _T("打开"));
	}
	else
	{
		m_Ctrl_List_ChannelStatic.SetItemText(iItem, 6, _T("关闭"));
	}

	return ;
}

void CARTDlgMonitor::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	SetChannelStatic();

	CDialog::OnTimer(nIDEvent);
}


void CARTDlgMonitor::SetChannelStatic()
{
	CChannelStatistics *pChannelStatic = NULL;
	CDevManager  *pDevManager = NULL;
	CPort        *pPort       = NULL;

	m_Ctrl_List_ChannelStatic.DeleteAllItems();

	pDevManager = GetDocument()->GetDeviceManager();
	pPort       =  pDevManager->QueryPortByIPandPortNo(m_dwDevIPSelected, m_iPortSelected);
	if ( pPort != NULL )
	{
		SetChannelStaticData(1, pPort->m_pChannelStatic1, pPort->Get_CHANNELSWITCH1());
        SetChannelStaticData(2, pPort->m_pChannelStatic2, pPort->Get_CHANNELSWITCH2());
		SetChannelStaticData(3, pPort->m_pChannelStatic3, pPort->Get_CHANNELSWITCH3());
		SetChannelStaticData(4, pPort->m_pChannelStatic4, pPort->Get_CHANNELSWITCH4());
		SetChannelStaticData(5, pPort->m_pChannelStatic5, pPort->Get_CHANNELSWITCH5());
		SetChannelStaticData(6, pPort->m_pChannelStatic6, pPort->Get_CHANNELSWITCH6());
	}

}