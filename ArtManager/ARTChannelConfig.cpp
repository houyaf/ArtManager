// ARTChannelConfig.cpp : 实现文件
//

#include "stdafx.h"
#include "ARTChannelConfig.h"
#include "ARTDlgPortChannel.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ARTDoc.h"


// CARTChannelConfig 对话框
IMPLEMENT_DYNAMIC(CARTChannelConfig, CDialog)

CARTChannelConfig::CARTChannelConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CARTChannelConfig::IDD, pParent)
	,m_pParent(pParent)
	,m_iChannelID(1)
{

}

//	DWORD     m_dwDevIPSelected;
//	int       m_iPortSelected  ;
CARTChannelConfig::CARTChannelConfig(CWnd* pParent ,DWORD dwIP,int iPort, int iChannel)
	: CDialog(CARTChannelConfig::IDD, pParent)
	,m_pParent(pParent)
	,m_dwDevIPSelected(dwIP)
	,m_iPortSelected(iPort)
	,m_iChannelID(iChannel)
{

}

CARTChannelConfig::~CARTChannelConfig()
{
}

void CARTChannelConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_UDPCLIENT_HOST, m_Ctrl_Static_UDPClient_Host);
	DDX_Control(pDX, IDC_STATIC_UDPCLIENT_PORT, m_Ctrl_Static_UCPClient_Port);
	DDX_Control(pDX, IDC_EDIT_UDPCLIENT_PORT, m_Ctrl_Edit_UDPClient_Port);
	DDX_Control(pDX, IDC_STATIC_TCPCLIENT_HOST, m_Ctrl_Static_TCPClient_Host);
	DDX_Control(pDX, IDC_STATIC_TCPCLIENT_PORT, m_Ctrl_Static_TCPClient_Port);
	DDX_Control(pDX, IDC_EDIT_TARGET_HOST_PORT1, m_Ctrl_Edit_TCPClient_Port);
	DDX_Control(pDX, IDC_STATIC_UDP_PORT, m_Ctrl_Static_UDPServer_Port);
	DDX_Control(pDX, IDC_EDIT_UDP_PORT, m_Ctrl_Edit_UDPServer_Port);
	DDX_Control(pDX, IDC_STATIC_TCPSERVER_PORT, m_Ctrl_Static_TCPServer_Port);
	DDX_Control(pDX, IDC_EDIT_TCP_LISTENPORT1, m_Ctrl_Edit_TCPServer_ListenPort);
	DDX_Control(pDX, IDC_STATIC_TCPSERVER_MAXCONN, m_Ctrl_Static_TCPServer_MaxConn);
	DDX_Control(pDX, IDC_PORT_WORKMODE, m_Ctrl_Combo_ChannelMode);
	DDX_Control(pDX, IDC_GROUP_WORKMODE_PARAM, m_Ctrl_Group_ChannelModeParam);
	DDX_Control(pDX, IDC_RADIO_CHANNEL_ENABLE, m_Ctrl_Radio_ChannelSwitch_ON);
	DDX_Control(pDX, IDC_RADIO_CHANNEL_DISABLE, m_Ctrl_Radio_ChannelSwitch_OFF);

	//CButton m_Ctrl_Radio_PortSwitch_ON;
	//CButton m_Ctrl_Radio_PortSwitch_OFF;

	DDX_Control(pDX, IDC_COMBO_TCPSERVER_MAXCONN, m_Ctrl_Combo_TCPServer_MaxConnection);
	DDX_Control(pDX, IDC_IPADDRESS_TCPCLIENT_HOST, m_Ctrl_IPAddr_TCPClient_Host);
	DDX_Control(pDX, IDC_IPADDRESS_UDPCLIENT_HOST, m_Ctrl_IPAddr_UDPClient_Host);
}


BEGIN_MESSAGE_MAP(CARTChannelConfig, CDialog)
	ON_CBN_SELCHANGE(IDC_PORT_WORKMODE, &CARTChannelConfig::OnCbnSelchangePortWorkmode)
	ON_BN_CLICKED(IDC_RADIO_CHANNEL_DISABLE, &CARTChannelConfig::OnBnClickedRadioChannelDisable)
	ON_BN_CLICKED(IDC_RADIO_CHANNEL_ENABLE, &CARTChannelConfig::OnBnClickedRadioChannelEnable)
END_MESSAGE_MAP()


// CARTChannelConfig 消息处理程序


void CARTChannelConfig::OnCbnSelchangePortWorkmode()
{
	// TODO: 在此添加控件通知处理程序代码
	int iPortModeIndex;

	iPortModeIndex = m_Ctrl_Combo_ChannelMode.GetCurSel();
	ShowConfigAreaByChannelMode(iPortModeIndex);
}


BOOL CARTChannelConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rectCtrl ;
	CRect rect1;
	GetDlgItem(IDC_STATIC_POS1)->GetWindowRect(&rect1);
	ScreenToClient(&rect1);

	CRect rect2;
	GetDlgItem(IDC_STATIC_POS2)->GetWindowRect(&rect2);
	ScreenToClient(&rect2);

	CRect rect3;
	GetDlgItem(IDC_STATIC_POS3)->GetWindowRect(&rect3);
	ScreenToClient(&rect3);

	CRect rect4;
	GetDlgItem(IDC_STATIC_POS4)->GetWindowRect(&rect4);
	ScreenToClient(&rect4);

	m_Ctrl_Static_UDPClient_Host.MoveWindow(&rect1);
	m_Ctrl_IPAddr_UDPClient_Host.GetWindowRect(&rectCtrl);
	m_Ctrl_IPAddr_UDPClient_Host.MoveWindow(rect2.left ,rect2.top, rectCtrl.Width(), rectCtrl.Height());

	m_Ctrl_Static_UCPClient_Port.MoveWindow(&rect3);
	m_Ctrl_Edit_UDPClient_Port.GetWindowRect(&rectCtrl);
	m_Ctrl_Edit_UDPClient_Port.MoveWindow(rect4.left ,rect4.top ,rectCtrl.Width(), rectCtrl.Height());

	//CStatic   m_Ctrl_Static_TCPClient_Host;
	//CEdit     m_Ctrl_Edit_TCPClient_Host;
	//CStatic   m_Ctrl_Static_TCPClient_Port;
	//CEdit     m_Ctrl_Edit_TCPClient_Port;
	m_Ctrl_Static_TCPClient_Host.MoveWindow(&rect1);
	m_Ctrl_IPAddr_TCPClient_Host.GetWindowRect(&rectCtrl);
	m_Ctrl_IPAddr_TCPClient_Host.MoveWindow(rect2.left ,rect2.top , rectCtrl.Width(), rectCtrl.Height());

	m_Ctrl_Static_TCPClient_Port.MoveWindow(&rect3);
	m_Ctrl_Edit_TCPClient_Port.GetWindowRect(&rectCtrl);
	m_Ctrl_Edit_TCPClient_Port.MoveWindow(rect4.left ,rect4.top ,rectCtrl.Width(), rectCtrl.Height());

	//CStatic   m_Ctrl_Static_UDPServer_Port;
	//CEdit     m_Ctrl_Edit_UDPServer_Port;
	m_Ctrl_Static_UDPServer_Port.MoveWindow(&rect1);
	m_Ctrl_Edit_UDPServer_Port.GetWindowRect(&rectCtrl);
	m_Ctrl_Edit_UDPServer_Port.MoveWindow(rect2.left ,rect2.top ,rectCtrl.Width(),rectCtrl.Height());

	//CStatic   m_Ctrl_Static_TCPServer_Port;
	//CEdit     m_Ctrl_Edit_TCPServer_ListenPort;
	//CStatic   m_Ctrl_Static_TCPServer_MaxConn;
	//CComboBox m_Ctrl_Combo_TCPServer_MaxConn;
	m_Ctrl_Static_TCPServer_Port.MoveWindow(&rect1);
	m_Ctrl_Edit_TCPServer_ListenPort.GetWindowRect(&rectCtrl);
	m_Ctrl_Edit_TCPServer_ListenPort.MoveWindow(rect2.left ,rect2.top , rectCtrl.Width(), rectCtrl.Height());

	m_Ctrl_Static_TCPServer_MaxConn.MoveWindow(&rect3);
	m_Ctrl_Combo_TCPServer_MaxConnection.GetWindowRect(&rectCtrl);
	m_Ctrl_Combo_TCPServer_MaxConnection.MoveWindow(rect4.left, rect4.top , rectCtrl.Width(), rectCtrl.Height());



	// TODO:  在此添加额外的初始化
	for (int i = 0 ; i < PORT_MODE_MAX ; i++)
	{
		m_Ctrl_Combo_ChannelMode.InsertString(i, g_Port_Mode[i].szPortMode);
	}

	CString szMaxConn;
	for (int i = 0 ; i <  6 ; i++)
	{
		szMaxConn.Format("%d", i+1);
		m_Ctrl_Combo_TCPServer_MaxConnection.InsertString(i,(LPCTSTR)szMaxConn );
	}

	m_Ctrl_Edit_TCPServer_ListenPort.SetLimitText(5);
	m_Ctrl_Edit_UDPServer_Port.SetLimitText(5);
	m_Ctrl_Edit_TCPClient_Port.SetLimitText(5);
	m_Ctrl_Edit_UDPClient_Port.SetLimitText(5);

	
	CDevManager  *pDevManager = NULL;
	CPort        *pPort       = NULL;

	unsigned char  ucOPMODE;
	unsigned long  ulCOMIP;
	unsigned short usCOMPORT;
	unsigned long  ulCONNECTNUM;
	unsigned char  ucCHANNELSWITCH;

	pDevManager = GetDocument()->GetDeviceManager();
	pPort       =  pDevManager->QueryPortByIPandPortNo(m_dwDevIPSelected, m_iPortSelected);
	if ( pPort != NULL )
	{
		switch (m_iChannelID)
		{
			case 1:
				ucOPMODE		= pPort->Get_OPMODE1();
				ulCOMIP			= pPort->Get_COMIP1();
				usCOMPORT		= pPort->Get_COMPORT1();
				ulCONNECTNUM	= pPort->Get_CONNECTNUM1();
			    ucCHANNELSWITCH	= pPort->Get_CHANNELSWITCH1();
				break;

			case 2:
				ucOPMODE		= pPort->Get_OPMODE2();
				ulCOMIP			= pPort->Get_COMIP2();
				usCOMPORT		= pPort->Get_COMPORT2();
				ulCONNECTNUM	= pPort->Get_CONNECTNUM2();
			    ucCHANNELSWITCH	= pPort->Get_CHANNELSWITCH2();
				break;

			case 3:
				ucOPMODE		= pPort->Get_OPMODE3();
				ulCOMIP			= pPort->Get_COMIP3();
				usCOMPORT		= pPort->Get_COMPORT3();
				ulCONNECTNUM	= pPort->Get_CONNECTNUM3();
			    ucCHANNELSWITCH	= pPort->Get_CHANNELSWITCH3();
				break;

			case 4:
				ucOPMODE		= pPort->Get_OPMODE4();
				ulCOMIP			= pPort->Get_COMIP4();
				usCOMPORT		= pPort->Get_COMPORT4();
				ulCONNECTNUM	= pPort->Get_CONNECTNUM4();
			    ucCHANNELSWITCH	= pPort->Get_CHANNELSWITCH4();
				break;

			case 5:
				ucOPMODE		= pPort->Get_OPMODE5();
				ulCOMIP			= pPort->Get_COMIP5();
				usCOMPORT		= pPort->Get_COMPORT5();
				ulCONNECTNUM	= pPort->Get_CONNECTNUM5();
			    ucCHANNELSWITCH	= pPort->Get_CHANNELSWITCH5();
				break;

			case 6:
				ucOPMODE		= pPort->Get_OPMODE6();
				ulCOMIP			= pPort->Get_COMIP6();
				usCOMPORT		= pPort->Get_COMPORT6();
				ulCONNECTNUM	= pPort->Get_CONNECTNUM6();
			    ucCHANNELSWITCH	= pPort->Get_CHANNELSWITCH6();
				break;

			default:

				break;
		}

		//合法性处理
		if (ulCONNECTNUM > 6)
		{
			ulCONNECTNUM = 6;
		}

		if (ucCHANNELSWITCH > 0)
		{
			m_bChannelSwitch = SERIALSERV_CHANNELSWITCH_ON;
		}
		else
		{
			m_bChannelSwitch = SERIALSERV_CHANNELSWITCH_OFF;
		}

		if (ucOPMODE >= SERIALSERV_OPMODE_MAX)
		{

			ucOPMODE= SERIALSERV_OPMODE_TCPSERVER ;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////
		CString szValue;

		szValue.Format("%d", usCOMPORT);

		m_Ctrl_Radio_ChannelSwitch_ON.SetCheck(ucCHANNELSWITCH);
		m_Ctrl_Radio_ChannelSwitch_OFF.SetCheck(!ucCHANNELSWITCH);

		m_Ctrl_Combo_TCPServer_MaxConnection.SetCurSel(ulCONNECTNUM-1);
		m_Ctrl_Edit_TCPServer_ListenPort.SetWindowText((LPCTSTR)szValue);
		m_Ctrl_IPAddr_TCPClient_Host.SetAddress(DWORD(ulCOMIP));


		m_Ctrl_IPAddr_UDPClient_Host.SetAddress((DWORD)ulCOMIP);

		m_Ctrl_Edit_UDPClient_Port.SetWindowText((LPCTSTR)szValue);

		m_Ctrl_Edit_UDPServer_Port.SetWindowText((LPCTSTR)szValue);

		m_Ctrl_Combo_ChannelMode.SetCurSel(ucOPMODE);

		ShowConfigAreaByChannelMode(ucOPMODE);

		SetFieldsStatus(m_bChannelSwitch);
		
	}


	//SetDefaultValues();

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CARTChannelConfig::SetDefaultValues()
{

	CString szValue;

	m_Ctrl_Combo_ChannelMode.SetCurSel(PORT_MODE_TCP_SERVER);

	unsigned short usTcpServerListenPort;
	
    usTcpServerListenPort = 50000+ m_iPortSelected*100+ m_iChannelID;

	szValue.Format("%d", usTcpServerListenPort);
	m_Ctrl_Edit_TCPServer_ListenPort.SetWindowText(szValue);

	m_Ctrl_Combo_TCPServer_MaxConn.SetCurSel(5);

	ShowConfigAreaByChannelMode(PORT_MODE_TCP_SERVER);
}


void CARTChannelConfig::ShowConfigAreaByChannelMode(int iPortMode)
{
	//顯示配置區的模式提示
	//m_Ctrl_Group_ChannelModeParam.SetWindowText(PORT_Get_PortMode_Text(iPortMode));

	//Real COM Mode没有配置参数，不显示配置区
	//m_Ctrl_Group_ChannelModeParam.ShowWindow((iPortMode == PORT_MODE_REAL_COM) ?SW_HIDE : SW_SHOW);

	//TCP Server Mode配置参数显示
	m_Ctrl_Static_TCPServer_Port.ShowWindow((iPortMode == PORT_MODE_TCP_SERVER)? SW_SHOW : SW_HIDE);
	m_Ctrl_Edit_TCPServer_ListenPort.ShowWindow((iPortMode == PORT_MODE_TCP_SERVER)? SW_SHOW : SW_HIDE);
	m_Ctrl_Static_TCPServer_MaxConn.ShowWindow((iPortMode == PORT_MODE_TCP_SERVER)? SW_SHOW : SW_HIDE);
	m_Ctrl_Combo_TCPServer_MaxConnection.ShowWindow((iPortMode == PORT_MODE_TCP_SERVER)? SW_SHOW : SW_HIDE);
	
	//TCP Client Mode配置参数显示


	m_Ctrl_Static_TCPClient_Host.ShowWindow((iPortMode == PORT_MODE_TCP_CLIENT)? SW_SHOW:SW_HIDE);
	m_Ctrl_IPAddr_TCPClient_Host.ShowWindow((iPortMode == PORT_MODE_TCP_CLIENT)? SW_SHOW:SW_HIDE);
	m_Ctrl_Static_TCPClient_Port.ShowWindow((iPortMode == PORT_MODE_TCP_CLIENT)? SW_SHOW:SW_HIDE);
	m_Ctrl_Edit_TCPClient_Port.ShowWindow((iPortMode == PORT_MODE_TCP_CLIENT)? SW_SHOW:SW_HIDE);
	
	
	//UDP Server Mode配置参数显示
	m_Ctrl_Static_UDPServer_Port.ShowWindow((iPortMode == PORT_MODE_UDP_SERVER)? SW_SHOW:SW_HIDE);
	m_Ctrl_Edit_UDPServer_Port.ShowWindow((iPortMode == PORT_MODE_UDP_SERVER)? SW_SHOW:SW_HIDE);
	
	//UDP Client Mode配置参数显示
	m_Ctrl_Static_UDPClient_Host.ShowWindow((iPortMode == PORT_MODE_UDP_CLIENT)? SW_SHOW:SW_HIDE);
	m_Ctrl_IPAddr_UDPClient_Host.ShowWindow((iPortMode == PORT_MODE_UDP_CLIENT)? SW_SHOW:SW_HIDE);
	m_Ctrl_Static_UCPClient_Port.ShowWindow((iPortMode == PORT_MODE_UDP_CLIENT)? SW_SHOW:SW_HIDE);
	m_Ctrl_Edit_UDPClient_Port.ShowWindow((iPortMode == PORT_MODE_UDP_CLIENT)? SW_SHOW:SW_HIDE);
	return ;
}

void CARTChannelConfig::SetFieldsStatus(BOOL bEnabled)
{
	m_Ctrl_Combo_ChannelMode.EnableWindow(bEnabled);

	//TCP Server Mode配置参数显示
	m_Ctrl_Static_TCPServer_Port.EnableWindow(bEnabled);
	m_Ctrl_Edit_TCPServer_ListenPort.EnableWindow(bEnabled);
	m_Ctrl_Static_TCPServer_MaxConn.EnableWindow(bEnabled);
	m_Ctrl_Combo_TCPServer_MaxConnection.EnableWindow(bEnabled);
	
	//TCP Client Mode配置参数显示


	m_Ctrl_Static_TCPClient_Host.EnableWindow(bEnabled);
	m_Ctrl_IPAddr_TCPClient_Host.EnableWindow(bEnabled);
	m_Ctrl_Static_TCPClient_Port.EnableWindow(bEnabled);
	m_Ctrl_Edit_TCPClient_Port.EnableWindow(bEnabled);
	
	
	//UDP Server Mode配置参数显示
	m_Ctrl_Static_UDPServer_Port.EnableWindow(bEnabled);
	m_Ctrl_Edit_UDPServer_Port.EnableWindow(bEnabled);
	
	//UDP Client Mode配置参数显示
	m_Ctrl_Static_UDPClient_Host.EnableWindow(bEnabled);
	m_Ctrl_IPAddr_UDPClient_Host.EnableWindow(bEnabled);
	m_Ctrl_Static_UCPClient_Port.EnableWindow(bEnabled);
	m_Ctrl_Edit_UDPClient_Port.EnableWindow(bEnabled);

}

void CARTChannelConfig::OnBnClickedRadioChannelDisable()
{
	CARTDlgPortChannel *pDlgChannel = NULL;

	m_bChannelSwitch = SERIALSERV_CHANNELSWITCH_OFF;
	SetFieldsStatus(FALSE);

	//ASSERT(m_pParent->isKindof(CARTDlgPortChannel));

	pDlgChannel = (CARTDlgPortChannel *)m_pParent;

	pDlgChannel->UpdateChannelNum();

}


void CARTChannelConfig::OnBnClickedRadioChannelEnable()
{
	CARTDlgPortChannel *pDlgChannel = NULL;

	m_bChannelSwitch = SERIALSERV_CHANNELSWITCH_ON;
	SetFieldsStatus(TRUE);

	//ASSERT(m_pParent->isKindof(CARTDlgPortChannel));

	pDlgChannel = (CARTDlgPortChannel *)m_pParent;

	pDlgChannel->UpdateChannelNum();
}


/**************************************************************************************************
函 数 名 :GetDocument
功能描述 :获取CDocument指针
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
CARTDoc *CARTChannelConfig::GetDocument()
{
	CMainFrame *pFrm = (CMainFrame *)AfxGetMainWnd();

	ASSERT(pFrm);

	CDocument *pDoc = pFrm->GetActiveDocument();

	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CARTDoc)));

	return (CARTDoc *)pDoc;
}

BOOL CARTChannelConfig::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	cs.cx = 200;
	cs.cy = 180;
	return CDialog::PreCreateWindow(cs);
}

///////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************
函 数 名 :SaveChannelData
功能描述 :保存数据到内存端口数据
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
///////////////////////////////////////////////////////////////////////////////
BOOL CARTChannelConfig::SaveChannelData()
{

	CDevManager  *pDevManager = NULL;
	CPort        *pPort       = NULL;

	unsigned char  ucOPMODE;//
	unsigned long  ulCOMIP;
	unsigned short usCOMPORT;
	unsigned long  ulCONNECTNUM;
	unsigned char  ucCHANNELSWITCH;//

	CString szCOMPort;
	CString szCOMMNECTNUM;
	DWORD dwIP;
	CString szErrMsg;
	int iPort;

	ucOPMODE= m_Ctrl_Combo_ChannelMode.GetCurSel();

	m_ucOpMode = ucOPMODE ;

	pDevManager = GetDocument()->GetDeviceManager();
	pPort       =  pDevManager->QueryPortByIPandPortNo(m_dwDevIPSelected, m_iPortSelected);
	if ( pPort != NULL )
	{
		
        ucCHANNELSWITCH = m_bChannelSwitch;
		
		switch (ucOPMODE)
		{
			///////////////////////////////////////////////////////////////////
			case PORT_MODE_TCP_SERVER:

				m_Ctrl_Edit_TCPServer_ListenPort.GetWindowText(szCOMPort);

				iPort = atoi((LPSTR)(LPCTSTR)szCOMPort);
				usCOMPORT = atoi((LPSTR)(LPCTSTR)szCOMPort);
				
				m_Ctrl_Combo_TCPServer_MaxConnection.GetWindowText(szCOMMNECTNUM);
				ulCONNECTNUM = atoi((LPSTR)(LPCTSTR)szCOMMNECTNUM);

				if ((usCOMPORT == 0)||(iPort > 65535))
				{
					szErrMsg.Format("通道%d TCP Server模式监听端口设置只能>0,并且<=65535！",m_iChannelID);
					MessageBox((LPCTSTR)szErrMsg ,_T("提示"),MB_OK);
					return FALSE;
				}

				if (m_iChannelID == 1)
				{
					pPort->Set_OPMODE1(ucOPMODE);
					pPort->Set_CHANNELSWITCH1(ucCHANNELSWITCH);
					pPort->Set_COMPORT1(usCOMPORT);
					pPort->Set_CONNECTNUM1(ulCONNECTNUM);
				}
				else if (m_iChannelID == 2)
				{
					pPort->Set_OPMODE2(ucOPMODE);
					pPort->Set_CHANNELSWITCH2(ucCHANNELSWITCH);
					pPort->Set_COMPORT2(usCOMPORT);
					pPort->Set_CONNECTNUM2(ulCONNECTNUM);
				}
				else if (m_iChannelID == 3)
				{
					pPort->Set_OPMODE3(ucOPMODE);
					pPort->Set_CHANNELSWITCH3(ucCHANNELSWITCH);
					pPort->Set_COMPORT3(usCOMPORT);
					pPort->Set_CONNECTNUM3(ulCONNECTNUM);
				}
				else if (m_iChannelID == 4)
				{
					pPort->Set_OPMODE4(ucOPMODE);
					pPort->Set_CHANNELSWITCH4(ucCHANNELSWITCH);
					pPort->Set_COMPORT4(usCOMPORT);
					pPort->Set_CONNECTNUM4(ulCONNECTNUM);
				}
				else if (m_iChannelID == 5)
				{
					pPort->Set_OPMODE5(ucOPMODE);
					pPort->Set_CHANNELSWITCH5(ucCHANNELSWITCH);
					pPort->Set_COMPORT5(usCOMPORT);
					pPort->Set_CONNECTNUM5(ulCONNECTNUM);
				}
				else if (m_iChannelID == 6)
				{
					pPort->Set_OPMODE6(ucOPMODE);
					pPort->Set_CHANNELSWITCH6(ucCHANNELSWITCH);
					pPort->Set_COMPORT6(usCOMPORT);
					pPort->Set_CONNECTNUM6(ulCONNECTNUM);
				}

				break;
            ///////////////////////////////////////////////////////////////////
			case PORT_MODE_TCP_CLIENT:
				m_Ctrl_IPAddr_TCPClient_Host.GetAddress(dwIP);
				ulCOMIP = (unsigned long)dwIP;

				m_Ctrl_Edit_TCPClient_Port.GetWindowText(szCOMPort);
				usCOMPORT = atoi((LPSTR)(LPCTSTR)szCOMPort);
				iPort = atoi((LPSTR)(LPCTSTR)szCOMPort);

				if ((usCOMPORT == 0)||(iPort>65535))
				{
					szErrMsg.Format("通道%d TCP Client模式目标主机端口设置只能>0,并且<=65535！",m_iChannelID);
					MessageBox((LPCTSTR)szErrMsg ,_T("提示"),MB_OK);
					return FALSE;
				}

				if (m_iChannelID == 1)
				{
					pPort->Set_OPMODE1(ucOPMODE);
					pPort->Set_CHANNELSWITCH1(ucCHANNELSWITCH);
					pPort->Set_COMIP1(ulCOMIP);
					pPort->Set_COMPORT1(usCOMPORT);
				}
				else if (m_iChannelID == 2)
				{
					pPort->Set_OPMODE2(ucOPMODE);
					pPort->Set_CHANNELSWITCH2(ucCHANNELSWITCH);
					pPort->Set_COMIP2(ulCOMIP);
					pPort->Set_COMPORT2(usCOMPORT);
				}
				else if (m_iChannelID == 3)
				{
					pPort->Set_OPMODE3(ucOPMODE);
					pPort->Set_CHANNELSWITCH3(ucCHANNELSWITCH);
					pPort->Set_COMIP3(ulCOMIP);
					pPort->Set_COMPORT3(usCOMPORT);
				}
				else if (m_iChannelID == 4)
				{
					pPort->Set_OPMODE4(ucOPMODE);
					pPort->Set_CHANNELSWITCH4(ucCHANNELSWITCH);
					pPort->Set_COMIP4(ulCOMIP);
					pPort->Set_COMPORT4(usCOMPORT);
				}
				else if (m_iChannelID == 5)
				{
					pPort->Set_OPMODE5(ucOPMODE);
					pPort->Set_CHANNELSWITCH5(ucCHANNELSWITCH);
					pPort->Set_COMIP5(ulCOMIP);
					pPort->Set_COMPORT5(usCOMPORT);
				}
				else if (m_iChannelID == 6)
				{
					pPort->Set_OPMODE6(ucOPMODE);
					pPort->Set_CHANNELSWITCH6(ucCHANNELSWITCH);
					pPort->Set_COMIP6(ulCOMIP);
					pPort->Set_COMPORT6(usCOMPORT);
				}
				break;
			///////////////////////////////////////////////////////////////////////////////
			case PORT_MODE_UDP_SERVER:
				m_Ctrl_Edit_UDPServer_Port.GetWindowText(szCOMPort);
				usCOMPORT = atoi((LPSTR)(LPCTSTR)szCOMPort);
				iPort = atoi((LPSTR)(LPCTSTR)szCOMPort);

				if ((usCOMPORT == 0)||(iPort>65535))
				{
					szErrMsg.Format("通道%d UDP Server模式监听端口设置只能>0,并且<=65535！",m_iChannelID);
					MessageBox((LPCTSTR)szErrMsg ,_T("提示"),MB_OK);
					return FALSE;
				}

				if (m_iChannelID == 1)
				{
					pPort->Set_OPMODE1(ucOPMODE);
					pPort->Set_CHANNELSWITCH1(ucCHANNELSWITCH);
					pPort->Set_COMPORT1(usCOMPORT);
				}
				else if (m_iChannelID == 2)
				{
					pPort->Set_OPMODE2(ucOPMODE);
					pPort->Set_CHANNELSWITCH2(ucCHANNELSWITCH);
					pPort->Set_COMPORT2(usCOMPORT);
				}
				else if (m_iChannelID == 3)
				{
					pPort->Set_OPMODE3(ucOPMODE);
					pPort->Set_CHANNELSWITCH3(ucCHANNELSWITCH);
					pPort->Set_COMPORT3(usCOMPORT);
				}
				else if (m_iChannelID == 4)
				{
					pPort->Set_OPMODE4(ucOPMODE);
					pPort->Set_CHANNELSWITCH4(ucCHANNELSWITCH);
					pPort->Set_COMPORT4(usCOMPORT);
				}
				else if (m_iChannelID == 5)
				{
					pPort->Set_OPMODE5(ucOPMODE);
					pPort->Set_CHANNELSWITCH5(ucCHANNELSWITCH);
					pPort->Set_COMPORT5(usCOMPORT);
				}
				else if (m_iChannelID == 6)
				{
					pPort->Set_OPMODE6(ucOPMODE);
					pPort->Set_CHANNELSWITCH6(ucCHANNELSWITCH);
					pPort->Set_COMPORT6(usCOMPORT);
				}
				break;
			////////////////////////////////////////////////////////////////////////////
			case PORT_MODE_UDP_CLIENT:
				m_Ctrl_IPAddr_UDPClient_Host.GetAddress(dwIP);
				ulCOMIP = (unsigned long)dwIP;

				m_Ctrl_Edit_UDPClient_Port.GetWindowText(szCOMPort);
				usCOMPORT = atoi((LPSTR)(LPCTSTR)szCOMPort);
				iPort = atoi((LPSTR)(LPCTSTR)szCOMPort);

				if ((usCOMPORT == 0)||(iPort>65535))
				{
					szErrMsg.Format("通道%d UDP Client模式目标主机端口设置只能>0,并且<=65535！",m_iChannelID);
					MessageBox((LPCTSTR)szErrMsg ,_T("提示"),MB_OK);
					return FALSE;
				}

				if (m_iChannelID == 1)
				{
					pPort->Set_OPMODE1(ucOPMODE);
					pPort->Set_CHANNELSWITCH1(ucCHANNELSWITCH);
					pPort->Set_COMIP1(ulCOMIP);
					pPort->Set_COMPORT1(usCOMPORT);
				}
				else if (m_iChannelID == 2)
				{
					pPort->Set_OPMODE2(ucOPMODE);
					pPort->Set_CHANNELSWITCH2(ucCHANNELSWITCH);
					pPort->Set_COMIP2(ulCOMIP);
					pPort->Set_COMPORT2(usCOMPORT);
				}
				else if (m_iChannelID == 3)
				{
					pPort->Set_OPMODE3(ucOPMODE);
					pPort->Set_CHANNELSWITCH3(ucCHANNELSWITCH);
					pPort->Set_COMIP3(ulCOMIP);
					pPort->Set_COMPORT3(usCOMPORT);
				}
				else if (m_iChannelID == 4)
				{
					pPort->Set_OPMODE4(ucOPMODE);
					pPort->Set_CHANNELSWITCH4(ucCHANNELSWITCH);
					pPort->Set_COMIP4(ulCOMIP);
					pPort->Set_COMPORT4(usCOMPORT);
				}
				else if (m_iChannelID == 5)
				{
					pPort->Set_OPMODE5(ucOPMODE);
					pPort->Set_CHANNELSWITCH5(ucCHANNELSWITCH);
					pPort->Set_COMIP5(ulCOMIP);
					pPort->Set_COMPORT5(usCOMPORT);
				}
				else if (m_iChannelID == 6)
				{
					pPort->Set_OPMODE6(ucOPMODE);
					pPort->Set_CHANNELSWITCH6(ucCHANNELSWITCH);
					pPort->Set_COMIP6(ulCOMIP);
					pPort->Set_COMPORT6(usCOMPORT);
				}
				break;
			//case PORT_MODE_REAL_COM:

			//	break;
			default:
				break;

		}
	}

	m_usCOMPort = usCOMPORT;

	return TRUE;

}