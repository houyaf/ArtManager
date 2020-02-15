/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTCOMConsole.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: 超级终端工具类实现代码
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#include "stdafx.h"
#include "ARTCOMConsole.h"
#include "afxdialogex.h"
#include "resource.h"
#include "ARTDoc.h"
#include "MainFrm.h"

// CARTCOMConsole 对话框

IMPLEMENT_DYNAMIC(CARTCOMConsole, CDialog)

CARTCOMConsole::CARTCOMConsole(CWnd* pParent /*=NULL*/)
	: CDialog(CARTCOMConsole::IDD, pParent)
	, m_bASCIIORHex(FALSE)
	, m_bAutoWrap(TRUE)
	, m_bShowSentMsg(TRUE)
	, m_bShowTime(TRUE)
	, m_szMSGSend(_T(""))
	, m_bConnected(FALSE)
	, m_pCOMM(NULL)
	, m_szMSG(_T(""))
{

}

CARTCOMConsole::~CARTCOMConsole()
{

}

void CARTCOMConsole::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Radio(   pDX, IDC_RADIO1,            m_bASCIIORHex      );
	DDX_Check(   pDX, IDC_CHECK_AUTOWRAP,    m_bAutoWrap        );
	DDX_Check(   pDX, IDC_CHECK_SHOWSENDMSG, m_bShowSentMsg     );
	DDX_Check(   pDX, IDC_CHECK_SHOWTIME,    m_bShowTime        );
	DDX_Control( pDX, IDC_COMBO_DEVICE,      m_Ctrl_Combo_Device);
	DDX_Control( pDX, IDC_COMBO_PORT,        m_Ctrl_Combo_Port  );
	DDX_Control( pDX, IDC_EDIT_MSG  ,        m_Ctrl_Edit_MSG    );
	DDX_Text(    pDX, IDC_EDIT_SENDMSG,      m_szMSGSend        );
	DDV_MaxChars(pDX, m_szMSGSend, 512);
	DDX_Control( pDX, IDC_BTN_CONNECT,       m_Ctrl_BTN_Connect );
	DDX_Text(    pDX, IDC_EDIT_MSG,          m_szMSG            );
	DDV_MaxChars(pDX, m_szMSG, 8096);
	DDX_Control( pDX, IDC_EDIT_SENDMSG,      m_Ctrl_Edit_SendMsg);

}

BEGIN_MESSAGE_MAP(CARTCOMConsole, CDialog)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CARTCOMConsole::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_SEND, &CARTCOMConsole::OnBnClickedBtnSend)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE, &CARTCOMConsole::OnCbnSelchangeComboDevice)
	ON_BN_CLICKED(IDC_RADIO1, &CARTCOMConsole::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CARTCOMConsole::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_CHECK_AUTOWRAP, &CARTCOMConsole::OnBnClickedCheckAutowrap)
	ON_BN_CLICKED(IDC_CHECK_SHOWSENDMSG, &CARTCOMConsole::OnBnClickedCheckShowsendmsg)
	ON_BN_CLICKED(IDC_CHECK_SHOWTIME, &CARTCOMConsole::OnBnClickedCheckShowtime)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CARTCOMConsole::OnBnClickedBtnConnect)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CARTCOMConsole 消息处理程序

CARTDoc *CARTCOMConsole::GetDocument()
{
	CMainFrame *pFrm = (CMainFrame *)AfxGetMainWnd();

	ASSERT(pFrm);

	CDocument *pDoc = pFrm->GetActiveDocument();

	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CARTDoc)));

	return (CARTDoc *)pDoc;
}

void CARTCOMConsole::OnBnClickedBtnClear()
{
	m_szMSG.Empty();

	UpdateData(FALSE);
}

BOOL CARTCOMConsole::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Ctrl_Edit_MSG.SetReadOnly(TRUE);

	CDevManager *pDevManager = GetDocument()->GetDeviceManager();
	CDeviceList *pDevList = NULL;

	pDevList = pDevManager->Get_DevList();

	CDevice  *pDevice = NULL;
	int i = 0;
	int iPort = 0;

	POSITION pos;
	CString szDevip;
	
	m_Ctrl_Combo_Device.Clear();
	m_Ctrl_Combo_Port.Clear();

	pos = pDevList->GetHeadPosition();

	m_Ctrl_Combo_Device.InsertString(i, _T(""));
	i++;

	while(pos != NULL)
	{
		pDevice = pDevList->GetNext(pos);

		szDevip  = IP_DW2STR(pDevice->Get_DevIP());
		m_Ctrl_Combo_Device.InsertString(i, (LPCTSTR)szDevip);

		i++;
	}

	m_Ctrl_Combo_Port.SetCurSel(0);
	
   
	m_Ctrl_Combo_Port.InsertString(0, _T(""));
	m_Ctrl_Combo_Port.SetCurSel(0);
	
	m_Ctrl_Edit_SendMsg.SetFocus();

	return FALSE; 

}


void CARTCOMConsole::OnCbnSelchangeComboDevice()
{
	CString szIP;
	m_Ctrl_Combo_Device.GetWindowText(szIP);

	if (szIP.IsEmpty())
	{
		return ;
	}


	m_Ctrl_Combo_Port.ResetContent();
	
	CDevManager *pDevManager = GetDocument()->GetDeviceManager();
	CDevice     *pDevice = NULL;
	CPortList *pPortList  = NULL;
	CPort *pPort = NULL;

	pDevice = pDevManager->QueryDeviceByIP(IP_STR2DW(szIP));

	POSITION posofPort;
	int iPort = 0;

	CString szPort;

	m_Ctrl_Combo_Port.ResetContent();

	pPortList = pDevice->Get_PortList();

	posofPort = pPortList->GetHeadPosition();
   
	while(posofPort != NULL)
	{
		pPort = pPortList->GetNext(posofPort);
		szPort.Format("COM%d", pPort->Get_Index());
		m_Ctrl_Combo_Port.InsertString(iPort, szPort);
		iPort++;
	}
	
	m_Ctrl_Combo_Port.SetCurSel(0);

}


void CARTCOMConsole::OnBnClickedRadio1()
{
	UpdateShowMsg();
}


void CARTCOMConsole::OnBnClickedRadio2()
{
	UpdateShowMsg();
}


void CARTCOMConsole::OnBnClickedCheckAutowrap()
{
	UpdateShowMsg();
}


void CARTCOMConsole::OnBnClickedCheckShowsendmsg()
{
	UpdateShowMsg();
}


void CARTCOMConsole::OnBnClickedCheckShowtime()
{
	UpdateShowMsg();
}

void CARTCOMConsole::UpdateShowMsg()
{
	UpdateData(TRUE);
}

void CARTCOMConsole::OnBnClickedBtnConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	CString  szIP  ;
	CString  szPort;
	BOOL     bRet  ;
	int      iPort ;

	if (m_bConnected)
	{
		delete m_pCOMM;
		m_pCOMM = NULL; 
		m_Ctrl_BTN_Connect.SetWindowText("连接");
		m_bConnected = FALSE;
	}
	else
	{
	
		UpdateData(TRUE);

		m_Ctrl_Combo_Device.GetWindowText(szIP);
		m_Ctrl_Combo_Port.GetWindowText(szPort);

		if (szIP.IsEmpty() || szPort.IsEmpty())
		{
			return ;
		}


		iPort =atoi(szPort.Left(szPort.GetLength()-3));

		CDevManager *pDevManager = GetDocument()->GetDeviceManager();
		CPort  *pPort = NULL;

		pPort = pDevManager->QueryPortByIPandPortNo(IP_STR2DW(szIP), iPort );

		if (pPort != NULL)
		{

		}
		
		if (m_pCOMM!= NULL)
		{
			delete m_pCOMM ;
			m_pCOMM = NULL ;
		}

		m_pCOMM = new CCOMM(IP_STR2DW(_T("127.0.0.1")), 5555);

		bRet = m_pCOMM->VerifyHost();

		if (bRet != 1)
		{
			m_bConnected = FALSE ;
			MessageBox(_T("连接失败！"),_T("提示信息"), MB_OK);
		}
		else
		{
			m_bConnected = TRUE  ;
			m_Ctrl_BTN_Connect.SetWindowText("断开连接");
		}
	}
}


void CARTCOMConsole::OnDestroy()
{
	CDialog::OnDestroy();

	if (m_pCOMM!= NULL)
	{
		delete m_pCOMM ;
		m_pCOMM = NULL ;
	}
}




void CARTCOMConsole::OnBnClickedBtnSend()
{
	//int iDataSentSize;
	int iDataRecvSize;
	char szRecvBuf[2048] ;

	CString szRecvLog    ;
	CString szRecvTLog    ;
	CString szSendLog    ;
	CString szShowDateTime;
	CTime   tNow ;
	CString szAutoWrap  ;
	int     iRet;
	CString szHexChar   ;
	char    cChar;

	UpdateData(TRUE);

	memset(szRecvBuf, 0, 2048) ;

	if (!m_bConnected )
	{
		MessageBox(_T("请先连通串口!"),_T("提示信息"), MB_OK);
		return ;
	}

	if (m_szMSGSend.IsEmpty())
	{
		return ;
	}

	if ( m_pCOMM != NULL)
	{
		iRet = m_pCOMM->SendMsgAndGetResponse((LPSTR)((LPCTSTR)m_szMSGSend), m_szMSGSend.GetLength(), szRecvBuf, 2048, &iDataRecvSize);
		if (iRet !=0)
		{
			if (iDataRecvSize > 0)
			{

				if (m_bShowTime)
				{
					tNow = CTime::GetCurrentTime();
					szShowDateTime.Format("(%02d:%02d:%02d)-----------------------------", tNow.GetHour(), tNow.GetMinute(), tNow.GetSecond());
				}
				else
				{
					szShowDateTime.Format("");
				}

				if (m_bShowSentMsg)
				{
					szSendLog.Format("\r\n     发送:  %s\r\n", m_szMSGSend);
				}
				else
				{
					szSendLog.Format("");
				}
                
				m_szMSG += szShowDateTime + szSendLog + " ";

				if (m_bASCIIORHex)
				{//十六进制
					for (int i = 0; i < iDataRecvSize; i++)
					{
						cChar = szRecvBuf[i];
						szHexChar.Format("%x", cChar);
						szRecvTLog+= szHexChar ;
					}
					
					szRecvLog.Format("    接收:  0x%s\r\n", (LPCTSTR)szRecvTLog);
				}
				else
				{//ASCII
					szRecvLog.Format("    接收:  %s\r\n", (LPCTSTR)szRecvBuf);
				}

				m_szMSG += szRecvLog+ " ";

				UpdateData(FALSE);
			}
		}
	}

}
