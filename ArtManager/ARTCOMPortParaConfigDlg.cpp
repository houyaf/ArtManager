/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTCOMPortParaConfigDlg.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: CARTCOMPortParaConfigDlg类实现文件
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/
#include "stdafx.h"
#include "ART.h"
#include "ARTCOMPortParaConfigDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ARTDoc.h"



// CARTCOMPortParaConfigDlg 对话框

IMPLEMENT_DYNAMIC(CARTCOMPortParaConfigDlg, CDialog)

CARTCOMPortParaConfigDlg::CARTCOMPortParaConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CARTCOMPortParaConfigDlg::IDD, pParent)

	, m_szPortName(_T(""))
{
}

CARTCOMPortParaConfigDlg::CARTCOMPortParaConfigDlg(CWnd* pParent,DWORD dwIP)
	: CDialog(CARTCOMPortParaConfigDlg::IDD, pParent)
	, m_dwDevIPSelected(dwIP)
	, m_bForAllPort(true)
{
	
}


CARTCOMPortParaConfigDlg::CARTCOMPortParaConfigDlg(CWnd* pParent,DWORD dwIP, int iComPort)
	: CDialog(CARTCOMPortParaConfigDlg::IDD, pParent)
	, m_dwDevIPSelected(dwIP)
	, m_iPortSelected(iComPort)
	, m_bForAllPort(false)
{
	
}

CARTCOMPortParaConfigDlg::~CARTCOMPortParaConfigDlg()
{
}

/**************************************************************************************************
函 数 名 :GetDocument
功能描述 :获取CDocument指针
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
CARTDoc *CARTCOMPortParaConfigDlg::GetDocument()
{
	CMainFrame *pFrm = (CMainFrame *)AfxGetMainWnd();

	ASSERT(pFrm);

	CDocument *pDoc = pFrm->GetActiveDocument();

	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CARTDoc)));

	return (CARTDoc *)pDoc;
}

void CARTCOMPortParaConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_BAUD_RATE		, m_Ctrl_Combo_BaudRate);
	DDX_Control(pDX, IDC_COMBO_PARITY			, m_Ctrl_Combo_Parity);
	DDX_Control(pDX, IDC_COMBO_DATA_BITES		, m_Ctrl_Combo_Databits);
	DDX_Control(pDX, IDC_COMBO_STOP_BITS		, m_Ctrl_Combo_StopBits);
	DDX_Control(pDX, IDC_COMBO_INTERFACE		, m_Ctrl_Combo_Interface);
	DDX_Control(pDX, IDC_COMBO_FLOWCONTROL		, m_Ctrl_Combo_FlowControl);
	DDX_Text(pDX, IDC_EDIT1, m_szPortName);
	DDX_Control(pDX, IDC_RADIO_PORTSWITCH_ON , m_Ctrl_Radio_PortSwitch_ON);
	DDX_Control(pDX, IDC_RADIO_PORTSWITCH_OFF, m_Ctrl_Radio_PortSwitch_OFF);
}


BEGIN_MESSAGE_MAP(CARTCOMPortParaConfigDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CARTCOMPortParaConfigDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CARTCOMPortParaConfigDlg 消息处理程序

/**************************************************************************************************
函 数 名 :OnInitDialog
功能描述 :对话框初始化消息处理
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
BOOL CARTCOMPortParaConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CDevManager  *pDevManager = NULL;
	CPort        *pPort       = NULL;
	CString szTitle ;

	if (m_bForAllPort)
	{
		szTitle.Format(_T("设定目标：所有串口"));
		
	}
	else
	{
		szTitle.Format(_T("设定目标：串口%d"), m_iPortSelected);
	}
	SetWindowText((LPCTSTR)szTitle);

	for (int i = 0 ; i < Port_BaudRate_Max ; i++)
	{
		m_Ctrl_Combo_BaudRate.InsertString(i, g_Port_BaudRate[i].szBaudRate);
	}

	for (int i = 0 ; i< PORT_PARITY_MAX ; i++)
	{
		m_Ctrl_Combo_Parity.InsertString(i, g_Port_Parity[i].szPortParity);
	}

	for (int i = 0 ; i< Port_DataBits_Max ; i++)
	{
		m_Ctrl_Combo_Databits.InsertString(i, g_Port_DataBits[i].szDataBits);
	}

	for (int i = 0 ; i< Port_StopBits_Max ; i++)
	{
		m_Ctrl_Combo_StopBits.InsertString(i, g_Port_StopBits[i].szStopBits);
	}

	for (int i = 0 ; i< FLOW_CTRL_MAX ; i++)
	{
		m_Ctrl_Combo_FlowControl.InsertString(i, g_Port_FlowCtrl[i].szFlowCtrl);
	}

	for (int i = 0 ; i< INTERFACE_MAX ; i++)
	{
		m_Ctrl_Combo_Interface.InsertString(i, g_Port_Interface[i].szInterface);
	}
	
	if (m_bForAllPort)
	{
		m_Ctrl_Combo_BaudRate.SetCurSel(g_Port_BaudRate_Default);
		m_Ctrl_Combo_Parity.SetCurSel(g_Port_Parity_Default);
		m_Ctrl_Combo_Databits.SetCurSel(g_Port_DataBits_Default);
		m_Ctrl_Combo_StopBits.SetCurSel(g_Port_StopBits_Default);
		m_Ctrl_Combo_FlowControl.SetCurSel(g_Port_FlowCtrl_Default);
		m_Ctrl_Combo_Interface.SetCurSel(g_Port_Interface_Default);
	}
	else
	{
		pDevManager = GetDocument()->GetDeviceManager();
		pPort       =  pDevManager->QueryPortByIPandPortNo(m_dwDevIPSelected, m_iPortSelected);
		if ( pPort != NULL )
		{
			int iPortSwitch = pPort->Get_PortSwitch();
			if (iPortSwitch != SERIALSERV_SWITCH_OFF)
			{
				m_Ctrl_Radio_PortSwitch_ON.SetCheck(TRUE);
				m_Ctrl_Radio_PortSwitch_OFF.SetCheck(FALSE);
			}
			else
			{
				m_Ctrl_Radio_PortSwitch_ON.SetCheck(FALSE);
				m_Ctrl_Radio_PortSwitch_OFF.SetCheck(TRUE);
			}
			
			m_Ctrl_Combo_BaudRate.SetCurSel(pPort->Get_BaudRate());
			m_Ctrl_Combo_Parity.SetCurSel(pPort->Get_Parity());
			m_Ctrl_Combo_Databits.SetCurSel(pPort->Get_DataBits());
			m_Ctrl_Combo_StopBits.SetCurSel(pPort->Get_StopBits());
			m_Ctrl_Combo_FlowControl.SetCurSel(pPort->Get_FlowCtrl());
			m_Ctrl_Combo_Interface.SetCurSel(pPort->Get_Interface());
			m_szPortName   =  pPort->Get_PortName();
		}
	}

	UpdateData(FALSE);

	return TRUE;
}

/**************************************************************************************************
函 数 名 :SaveDataToOne
功能描述 :保存端口参数配置数据
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
int CARTCOMPortParaConfigDlg::SaveDataToOne()
{
	CDevManager  *pDevManager = GetDocument()->GetDeviceManager();
	CDevice      *pDevice     = pDevManager->QueryDeviceByIP(m_dwDevIPSelected);
	CPort        *pPort       = pDevManager->QueryPortByIPandPortNo(m_dwDevIPSelected, m_iPortSelected);
	BOOL          bRet ;

	ASSERT(pPort != NULL);
	if (pPort == NULL)
	{
		return 0;
	}

	UpdateData(TRUE);

    if (m_Ctrl_Radio_PortSwitch_ON.GetCheck())
	{
		pPort->Set_PortSwitch(SERIALSERV_SWITCH_ON);
	}
	else
	{
		pPort->Set_PortSwitch(SERIALSERV_SWITCH_OFF);
	}

	pPort->Set_PortName((LPCTSTR)m_szPortName);
	
	pPort->Set_BaudRate(m_Ctrl_Combo_BaudRate.GetCurSel());
	pPort->Set_Parity(m_Ctrl_Combo_Parity.GetCurSel());
	pPort->Set_DataBits(m_Ctrl_Combo_Databits.GetCurSel());
	pPort->Set_StopBits(m_Ctrl_Combo_StopBits.GetCurSel());
	pPort->Set_FlowCtrl(m_Ctrl_Combo_FlowControl.GetCurSel());
	pPort->Set_Interface(m_Ctrl_Combo_Interface.GetCurSel());

	//记录日志
	CARTDoc     *pDoc = GetDocument();
	CLogManager *pLogManager = pDoc->GetLogManager();	
	CString      szLog;

	ASSERT(pLogManager!= NULL);
	ASSERT(pDoc != NULL);

	bRet = pDevice->SavePortParaToDev(pPort->Get_Index());
	if (bRet != TRUE)
	{
		//配置到设备失败，要给出提示信息。
		szLog.Format("配置设备%s系统参数:失败!",IP_DW2STR(m_dwDevIPSelected));
		pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);

		return 0;
	}
	
	szLog.Format("配置设备%s串口%d物理参数,成功!",IP_DW2STR(m_dwDevIPSelected)
		                                         , m_iPortSelected);
	pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);
	pDoc->UpdateAllViews(NULL);


	return 1;
}

/**************************************************************************************************
函 数 名 :SaveDataToAll
功能描述 :保存端口参数配置数据
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
int CARTCOMPortParaConfigDlg::SaveDataToAll()
{
	CDevManager  *pDevManager = GetDocument()->GetDeviceManager();
	CDevice      *pDevice     = pDevManager->QueryDeviceByIP(m_dwDevIPSelected);
	CPortList    *pPortList;
	POSITION      pos      ;
	CPort        *pPort      = NULL;
	BOOL          bRet ;

	if (pDevice == NULL)
	{
		return 0;
	}
	
	UpdateData(TRUE);
	pPortList = pDevice->Get_PortList();

	ASSERT(pPortList);

	pos       = pPortList->GetHeadPosition();
	while(pos != NULL)
	{
		pPort = pPortList->GetNext(pos);
        
		//串口参数设定
		if (pPort != NULL)
		{
			if (m_Ctrl_Radio_PortSwitch_ON.GetCheck())
			{
				pPort->Set_PortSwitch(SERIALSERV_SWITCH_ON);
			}
			else
			{
				pPort->Set_PortSwitch(SERIALSERV_SWITCH_OFF);
			}

			pPort->Set_PortName((LPCTSTR)m_szPortName);
		    pPort->Set_BaudRate(m_Ctrl_Combo_BaudRate.GetCurSel());
			pPort->Set_Parity(m_Ctrl_Combo_Parity.GetCurSel());
			pPort->Set_DataBits(m_Ctrl_Combo_Databits.GetCurSel());
			pPort->Set_StopBits(m_Ctrl_Combo_StopBits.GetCurSel());
			pPort->Set_FlowCtrl(m_Ctrl_Combo_FlowControl.GetCurSel());
			pPort->Set_Interface(m_Ctrl_Combo_Interface.GetCurSel());
		}

		bRet = pDevice->SavePortParaToDev(pPort->Get_Index());
		if (bRet != TRUE)
		{
			//配置到设备失败，要给出提示信息。
			return 0;
		}

	}

	return 1;
	
}

/**************************************************************************************************
函 数 名 :OnBnClickedOk
功能描述 :保存Button消息处理
输入参数 :无
输出参数 :无
返 回 值 :无
**************************************************************************************************/
void CARTCOMPortParaConfigDlg::OnBnClickedOk()
{
	int iRet;
	
	if  (m_bForAllPort)
	{
		iRet = SaveDataToAll();
	}
	else
	{
		iRet = SaveDataToOne();
	}

	if (iRet != 1)
		return ;

	OnOK();
}
