/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTCOMPortParaConfigDlg.cpp
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: CARTCOMPortParaConfigDlg��ʵ���ļ�
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/
#include "stdafx.h"
#include "ART.h"
#include "ARTCOMPortParaConfigDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ARTDoc.h"



// CARTCOMPortParaConfigDlg �Ի���

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
�� �� �� :GetDocument
�������� :��ȡCDocumentָ��
������� :��
������� :��
�� �� ֵ :��
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


// CARTCOMPortParaConfigDlg ��Ϣ�������

/**************************************************************************************************
�� �� �� :OnInitDialog
�������� :�Ի����ʼ����Ϣ����
������� :��
������� :��
�� �� ֵ :��
**************************************************************************************************/
BOOL CARTCOMPortParaConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CDevManager  *pDevManager = NULL;
	CPort        *pPort       = NULL;
	CString szTitle ;

	if (m_bForAllPort)
	{
		szTitle.Format(_T("�趨Ŀ�꣺���д���"));
		
	}
	else
	{
		szTitle.Format(_T("�趨Ŀ�꣺����%d"), m_iPortSelected);
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
�� �� �� :SaveDataToOne
�������� :����˿ڲ�����������
������� :��
������� :��
�� �� ֵ :��
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

	//��¼��־
	CARTDoc     *pDoc = GetDocument();
	CLogManager *pLogManager = pDoc->GetLogManager();	
	CString      szLog;

	ASSERT(pLogManager!= NULL);
	ASSERT(pDoc != NULL);

	bRet = pDevice->SavePortParaToDev(pPort->Get_Index());
	if (bRet != TRUE)
	{
		//���õ��豸ʧ�ܣ�Ҫ������ʾ��Ϣ��
		szLog.Format("�����豸%sϵͳ����:ʧ��!",IP_DW2STR(m_dwDevIPSelected));
		pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);

		return 0;
	}
	
	szLog.Format("�����豸%s����%d�������,�ɹ�!",IP_DW2STR(m_dwDevIPSelected)
		                                         , m_iPortSelected);
	pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);
	pDoc->UpdateAllViews(NULL);


	return 1;
}

/**************************************************************************************************
�� �� �� :SaveDataToAll
�������� :����˿ڲ�����������
������� :��
������� :��
�� �� ֵ :��
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
        
		//���ڲ����趨
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
			//���õ��豸ʧ�ܣ�Ҫ������ʾ��Ϣ��
			return 0;
		}

	}

	return 1;
	
}

/**************************************************************************************************
�� �� �� :OnBnClickedOk
�������� :����Button��Ϣ����
������� :��
������� :��
�� �� ֵ :��
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
