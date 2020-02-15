// ARTDlgPortChannel.cpp : 实现文件
//

#include "stdafx.h"
#include "ARTDlgPortChannel.h"
#include "ARTChannelConfig.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ARTDoc.h"


// CARTDlgPortChannel 对话框

IMPLEMENT_DYNAMIC(CARTDlgPortChannel, CDialog)

CARTDlgPortChannel::CARTDlgPortChannel(CWnd* pParent /*=NULL*/)
	: CDialog(CARTDlgPortChannel::IDD, pParent)
	, m_dwDevIPSelected(0)
	, m_iPortSelected(0)
	, m_iChannelNum(6)
	, m_pChannel1(NULL)
	, m_pChannel2(NULL)
	, m_pChannel3(NULL)
	, m_pChannel4(NULL)
	, m_pChannel5(NULL)
	, m_pChannel6(NULL)
{

}

CARTDlgPortChannel::CARTDlgPortChannel(CWnd* pParent , DWORD dwIP)
	: CDialog(CARTDlgPortChannel::IDD, pParent)
	, m_dwDevIPSelected(dwIP)
	, m_iPortSelected(0)
	, m_iChannelNum(6)
	, m_pChannel1(NULL)
	, m_pChannel2(NULL)
	, m_pChannel3(NULL)
	, m_pChannel4(NULL)
	, m_pChannel5(NULL)
	, m_pChannel6(NULL)
{

}



CARTDlgPortChannel::CARTDlgPortChannel(CWnd* pParent , DWORD dwIP, int iPort)
	: CDialog(CARTDlgPortChannel::IDD, pParent)
	, m_dwDevIPSelected(dwIP)
	, m_iPortSelected(iPort)
	, m_iChannelNum(6)
	, m_pChannel1(NULL)
	, m_pChannel2(NULL)
	, m_pChannel3(NULL)
	, m_pChannel4(NULL)
	, m_pChannel5(NULL)
	, m_pChannel6(NULL)
{

}


CARTDlgPortChannel::~CARTDlgPortChannel()
{
	if (m_pChannel1 != NULL)
	{
		delete m_pChannel1;
		m_pChannel1= NULL;
	}

	if (m_pChannel2 != NULL)
	{
		delete m_pChannel2;
		m_pChannel2= NULL;
	}

	if (m_pChannel3 != NULL)
	{
		delete m_pChannel3;
		m_pChannel3= NULL;
	}

	if (m_pChannel4 != NULL)
	{
		delete m_pChannel4;
		m_pChannel4= NULL;
	}

	if (m_pChannel5 != NULL)
	{
		delete m_pChannel5;
		m_pChannel5= NULL;
	}

	if (m_pChannel6 != NULL)
	{
		delete m_pChannel6;
		m_pChannel6= NULL;
	}
}



void CARTDlgPortChannel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1                   , m_Ctrl_Tab_Channel);
	DDX_Control(pDX, IDC_STATIC_PORT_CHANNEL_NUM, m_Ctrl_Label_ChannelNum);
}


BEGIN_MESSAGE_MAP(CARTDlgPortChannel, CDialog)
	ON_BN_CLICKED(IDOK, &CARTDlgPortChannel::OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CARTDlgPortChannel::OnTcnSelchangeTab1)

END_MESSAGE_MAP()

void CARTDlgPortChannel::ShowChild(int iChild)
{
	if (m_pChannel1 != NULL)
	{
		m_pChannel1->ShowWindow((iChild == 1 )? SW_SHOW : SW_HIDE );
	}

	if (m_pChannel2 != NULL)
	{
		m_pChannel2->ShowWindow((iChild == 2 )? SW_SHOW : SW_HIDE );
	}
	if (m_pChannel3 != NULL)
	{
		m_pChannel3->ShowWindow((iChild == 3 )? SW_SHOW : SW_HIDE );
	}
	if (m_pChannel4 != NULL)
	{
		m_pChannel4->ShowWindow((iChild == 4 )? SW_SHOW : SW_HIDE );
	}
	if (m_pChannel5 != NULL)
	{
		m_pChannel5->ShowWindow((iChild == 5 )? SW_SHOW : SW_HIDE );
	}
	if (m_pChannel6 != NULL)
	{
		m_pChannel6->ShowWindow((iChild == 6 )? SW_SHOW : SW_HIDE );
	}

}

// CARTDlgPortChannel 消息处理程序
/**************************************************************************************************
函 数 名 :GetDocument
功能描述 :获取CDocument指针
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
CARTDoc *CARTDlgPortChannel::GetDocument()
{
	CMainFrame *pFrm = (CMainFrame *)AfxGetMainWnd();

	ASSERT(pFrm);

	CDocument *pDoc = pFrm->GetActiveDocument();

	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CARTDoc)));

	return (CARTDoc *)pDoc;
}


void CARTDlgPortChannel::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bRet ;
	int  iRet = 0 ;

	CString szMsg;
	CString szPortList;
	CString szPort;


	if (m_pChannel1 != NULL)
	{
		bRet = m_pChannel1->SaveChannelData();

		if (bRet != TRUE)
		{
			iRet+=1 ;
		}
		else
		{
			if (m_pChannel1->m_bChannelSwitch == SERIALSERV_CHANNELSWITCH_ON)
			{
				szPort.Format("%d:",m_pChannel1->m_usCOMPort);
				szPortList.Append(szPort);
			}
		}
	}

	if (m_pChannel2 != NULL)
	{
		bRet = m_pChannel2->SaveChannelData();
		if (bRet != TRUE)
		{
			iRet+=1 ;
		}
		else
		{
			if (m_pChannel2->m_bChannelSwitch == SERIALSERV_CHANNELSWITCH_ON)
			{
				szPort.Format("%d:",m_pChannel2->m_usCOMPort);
				if (szPortList.Find((LPCSTR)szPort)>=0)
				{
					szMsg.Format("通道2配置的端口号:%d已被占用!",m_pChannel2->m_usCOMPort);
					MessageBox((LPCTSTR)szMsg, _T("提示"), MB_OK);
					return ;
				}
				szPortList.Append(szPort);
			}
		}
	}
	if (m_pChannel3 != NULL)
	{
		bRet = m_pChannel3->SaveChannelData();
		if (bRet != TRUE)
		{
			iRet+=1 ;
		}
		else
		{
			if (m_pChannel3->m_bChannelSwitch == SERIALSERV_CHANNELSWITCH_ON)
			{
				szPort.Format("%d:",m_pChannel3->m_usCOMPort);
				if (szPortList.Find((LPCSTR)szPort)>=0)
				{
					szMsg.Format("通道3配置的端口号:%d已被占用!",m_pChannel3->m_usCOMPort);
					MessageBox((LPCTSTR)szMsg, _T("提示"), MB_OK);
					return ;
				}
				szPortList.Append(szPort);
			}
		}
	}
	if (m_pChannel4 != NULL)
	{
		bRet = m_pChannel4->SaveChannelData();
		if (bRet != TRUE)
		{
			iRet+=1 ;
		}
		else
		{
			if (m_pChannel4->m_bChannelSwitch == SERIALSERV_CHANNELSWITCH_ON)
			{
				szPort.Format("%d:",m_pChannel4->m_usCOMPort);
				if (szPortList.Find((LPCSTR)szPort)>=0)
				{
					szMsg.Format("通道4配置的端口号:%d已被占用!",m_pChannel4->m_usCOMPort);
					MessageBox((LPCTSTR)szMsg, _T("提示"), MB_OK);
					return ;
				}
				szPortList.Append(szPort);
			}
		}
	}
	if (m_pChannel5 != NULL)
	{
		bRet = m_pChannel5->SaveChannelData();
		if (bRet != TRUE)
		{
			iRet+=1 ;
		}
		else
		{
			if (m_pChannel5->m_bChannelSwitch == SERIALSERV_CHANNELSWITCH_ON)
			{
				szPort.Format("%d:",m_pChannel5->m_usCOMPort);
				if (szPortList.Find((LPCSTR)szPort)>=0)
				{
					szMsg.Format("通道5配置的端口号:%d已被占用!",m_pChannel5->m_usCOMPort);
					MessageBox((LPCTSTR)szMsg, _T("提示"), MB_OK);
					return ;
				}
				szPortList.Append(szPort);
			}
		}
	}


	if (m_pChannel6 != NULL)
	{
		bRet = m_pChannel6->SaveChannelData();
		if (bRet != TRUE)
		{
			iRet+=1 ;
		}
		else
		{
			if (m_pChannel6->m_bChannelSwitch == SERIALSERV_CHANNELSWITCH_ON)
			{
				szPort.Format("%d:",m_pChannel6->m_usCOMPort);
				if (szPortList.Find((LPCSTR)szPort)>=0)
				{
					szMsg.Format("通道3配置的端口号:%d已被占用!",m_pChannel6->m_usCOMPort);
					MessageBox((LPCTSTR)szMsg, _T("提示"), MB_OK);
					return ;
				}
				szPortList.Append(szPort);
			}
		}

	}

	if (iRet > 0)
	{
		return ;
	}
	
	CDevManager  *pDevManager = NULL;
	CDevice      *pDevice     = NULL;
	CPort        *pPort       = NULL;

	//记录日志
	CARTDoc * pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	CLogManager *pLogManager = pDoc->GetLogManager();	
	ASSERT(pLogManager!= NULL);
	CString szLog;
	CString szChannelNum;

	pDevManager = GetDocument()->GetDeviceManager();
	pDevice     = pDevManager->QueryDeviceByIP(m_dwDevIPSelected);
	pPort       =  pDevManager->QueryPortByIPandPortNo(m_dwDevIPSelected, m_iPortSelected);
	if ( pPort != NULL )
	{
		pPort->Set_ChannelNum(m_iChannelNum);

		bRet = pDevice->SavePortWorkModeParaToDev(pPort->Get_Index());
		if (bRet != TRUE)
		{
			//配置到设备失败，要给出提示信息。
			szLog.Format("配置设备%s串口%d通道参数：失败!",IP_DW2STR(m_dwDevIPSelected )
											   , m_iPortSelected);
			pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);
			pDoc->UpdateAllViews(NULL);
			return;
		}
		else
		{
	
			szLog.Format("配置设备%s串口%d通道参数：成功!",IP_DW2STR(m_dwDevIPSelected )
												         , m_iPortSelected);
			pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);
			pDoc->UpdateAllViews(NULL);
		}
	}

	CDialog::OnOK();
}


BOOL CARTDlgPortChannel::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ilTabs.Create(24,24,ILC_COLOR32|ILC_MASK , 2, 2);

	m_ilTabs.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	m_ilTabs.Add(AfxGetApp()->LoadIcon(IDI_ICON2));

	m_Ctrl_Tab_Channel.SetImageList(&m_ilTabs);
	
	COLORREF m_color_ming;
	DWORD dwFlags = 0;
	dwFlags |= ETC_SELECTION;
	dwFlags |= ETC_COLOR;
	dwFlags |= ETC_GRADIENT;
	dwFlags |= ETC_BACKTABS;
	dwFlags |= ETC_FLAT;



	m_color_ming=RGB(242,245,252);

	m_Ctrl_Tab_Channel.SetBkgndColor(m_color_ming);
	m_Ctrl_Tab_Channel.EnableDraw(0 ? BTC_ALL : dwFlags ? BTC_TABS : BTC_NONE); 

	CEnTabCtrl::EnableCustomLook(dwFlags | 0, dwFlags);
	m_Ctrl_Tab_Channel.Invalidate();



	CString szTitle;

	szTitle.Format(_T("设定目标：串口%d"), m_iPortSelected);
	SetWindowText((LPCTSTR)szTitle);


	CRect rect;
	GetDlgItem(IDC_STATIC_TABVIEW)->GetWindowRect(&rect);

	ScreenToClient(&rect);

	

	if (m_iChannelNum >= 1)
	{
		m_Ctrl_Tab_Channel.InsertItem(0, _T("通道1"),1);
		m_pChannel1 = new CARTChannelConfig(this, m_dwDevIPSelected,m_iPortSelected, 1);
		m_pChannel1->Create(CARTChannelConfig::IDD, this);
		m_pChannel1->MoveWindow(rect);
	}

	if (m_iChannelNum >= 2)
	{
		m_Ctrl_Tab_Channel.InsertItem(1, _T("通道2"),1);
		m_pChannel2 = new CARTChannelConfig(this, m_dwDevIPSelected,m_iPortSelected, 2);
		m_pChannel2->Create(CARTChannelConfig::IDD, this);
		m_pChannel2->MoveWindow(rect);
	}

	if (m_iChannelNum >= 3)
	{
		m_Ctrl_Tab_Channel.InsertItem(2, _T("通道3"),1);
		m_pChannel3 = new CARTChannelConfig(this, m_dwDevIPSelected,m_iPortSelected, 3);
		m_pChannel3->Create(CARTChannelConfig::IDD, this);
		m_pChannel3->MoveWindow(rect);
	}

	if (m_iChannelNum >= 4)
	{
		m_Ctrl_Tab_Channel.InsertItem(3, _T("通道4"),1);
		m_pChannel4 = new CARTChannelConfig(this, m_dwDevIPSelected,m_iPortSelected, 4);
		m_pChannel4->Create(CARTChannelConfig::IDD, this);
		m_pChannel4->MoveWindow(rect);
	}

	if (m_iChannelNum >= 5)
	{
		m_Ctrl_Tab_Channel.InsertItem(4, _T("通道5"),1);
		m_pChannel5 = new CARTChannelConfig(this, m_dwDevIPSelected,m_iPortSelected, 5);
		m_pChannel5->Create(CARTChannelConfig::IDD, this);
		m_pChannel5->MoveWindow(rect);
	}

	if (m_iChannelNum >= 6)
	{
		m_Ctrl_Tab_Channel.InsertItem(5, _T("通道6"),1);
		m_pChannel6 = new CARTChannelConfig(this, m_dwDevIPSelected,m_iPortSelected, 6);
		m_pChannel6->Create(CARTChannelConfig::IDD, this);
		m_pChannel6->MoveWindow(rect);

	}

	UpdateChannelNum();

	CString szChannelNum;
	szChannelNum.Format("当前串口打开的网络通道数目：%d",m_iChannelNum);

	m_Ctrl_Label_ChannelNum.SetBkColor(RGB(128,128,128));
	m_Ctrl_Label_ChannelNum.SetFontSize(20);
	m_Ctrl_Label_ChannelNum.SetFontBold(TRUE);
	m_Ctrl_Label_ChannelNum.SetTextColor(RGB(255,255,255));
	m_Ctrl_Label_ChannelNum.SetWindowText((LPCTSTR)szChannelNum);

	ShowChild(1);


	return TRUE;  // return TRUE unless you set the focus to a control
}


void CARTDlgPortChannel::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int id= m_Ctrl_Tab_Channel.GetCurSel();

	ShowChild(id+1);

	*pResult = 0;
}

void  CARTDlgPortChannel::UpdateChannelNum()
{
	int iChannelNum = 0;

	if (m_pChannel1 != NULL)
	{
		if ( m_pChannel1->m_bChannelSwitch == SERIALSERV_CHANNELSWITCH_ON)
		{
			iChannelNum++;
		}
	}

	if (m_pChannel2 != NULL)
	{
		if ( m_pChannel2->m_bChannelSwitch == SERIALSERV_CHANNELSWITCH_ON)
		{
			iChannelNum++;
		}
	}

	if (m_pChannel3 != NULL)
	{
		if ( m_pChannel3->m_bChannelSwitch == SERIALSERV_CHANNELSWITCH_ON)
		{
			iChannelNum++;
		}
	}

	if (m_pChannel4 != NULL)
	{
		if ( m_pChannel4->m_bChannelSwitch == SERIALSERV_CHANNELSWITCH_ON)
		{
			iChannelNum++;
		}
	}

	if (m_pChannel5 != NULL)
	{
		if ( m_pChannel5->m_bChannelSwitch == SERIALSERV_CHANNELSWITCH_ON)
		{
			iChannelNum++;
		}
	}

	if (m_pChannel6 != NULL)
	{
		if ( m_pChannel6->m_bChannelSwitch == SERIALSERV_CHANNELSWITCH_ON)
		{
			iChannelNum++;
		}
	}

	m_iChannelNum = iChannelNum;

	CString szChannelNum;
	szChannelNum.Format("当前串口打开的网络通道数目：%d",m_iChannelNum);

	m_Ctrl_Label_ChannelNum.SetWindowText((LPCTSTR)szChannelNum);

	return ;
}

