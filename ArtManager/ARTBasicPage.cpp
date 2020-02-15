/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTBasicPage.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: 设备基本配置对话框类实现文件
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#include "stdafx.h"
#include "ART.h"
#include "ARTBasicPage.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ARTDoc.h"
#include "LABEL.H"
#define SecondTimer   1

// CARTBasicPage 对话框

IMPLEMENT_DYNAMIC(CARTBasicPage, CDialog)

CARTBasicPage::CARTBasicPage(CWnd* pParent /*=NULL*/)
	: CDialog(CARTBasicPage::IDD, pParent)
	
	, m_szDevName(_T(""))
	, m_bDevNet1Mode(0)
	, m_dwDevNet1IP(0)
	, m_dwDevNet1IPMask(0)
	, m_dwDevNet1GateWay(0)
	, m_bDevNet2Mode(0)
	, m_dwDevNet2IP(0)
	, m_dwDevNet2IPMask(0)
	, m_dwDevNet2GateWay(0)
	, m_iNet1Mode(0)
	, m_iNet2Mode(0)
{

}

CARTBasicPage::CARTBasicPage(CWnd* pParent ,DWORD dwDevIP)
	: CDialog(CARTBasicPage::IDD, pParent)
	, m_dwDevIPSelected(dwDevIP)
{

}

CARTBasicPage::~CARTBasicPage()
{
}

void CARTBasicPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


	DDX_Text(pDX, IDC_EDIT_SYSNAME, m_szDevName);

	DDX_Control(pDX, IDC_COMBO_TIMEZONE, m_Ctrl_Combo_TimeZone);

	DDX_Control(pDX, IDC_DATETIMEPICKER_DEVDATE, m_Ctrl_DTPicker_DevDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DEVTIME, m_Ctrl_DTPicker_DevTime);
	DDX_Control(pDX, IDC_IPADDRESS1, m_Ctrl_IP_DevNet1IP);
	DDX_Control(pDX, IDC_IPADDRESS2, m_Ctrl_IP_DevNet1IPMask);
	DDX_Control(pDX, IDC_IPADDRESS3, m_Ctrl_IP_DevNet1GateWay);
	DDX_Control(pDX, IDC_IPADDRESS4, m_Ctrl_IP_DevNet2IP);
	DDX_Control(pDX, IDC_IPADDRESS5, m_Ctrl_IP_DevNet2IPMask);
	DDX_Control(pDX, IDC_IPADDRESS6, m_Ctrl_IP_DevNet2GateWay);

	DDX_IPAddress(pDX, IDC_IPADDRESS1, m_dwDevNet1IP);
	DDX_IPAddress(pDX, IDC_IPADDRESS2, m_dwDevNet1IPMask);
	DDX_IPAddress(pDX, IDC_IPADDRESS3, m_dwDevNet1GateWay);
	DDX_IPAddress(pDX, IDC_IPADDRESS4, m_dwDevNet2IP);
	DDX_IPAddress(pDX, IDC_IPADDRESS5, m_dwDevNet2IPMask);
	DDX_IPAddress(pDX, IDC_IPADDRESS6, m_dwDevNet2GateWay);

	DDX_Control(pDX, IDC_NET1_MODE_STATIC, m_Ctrl_Radio_Net1Mode);
	DDX_Control(pDX, IDC_NET2_MODE_STATIC, m_Ctrl_Radio_Net2Mode);
	DDX_Control(pDX, IDC_STATIC_IP_ADDRESS, m_Ctrl_Label_NET1_IP);
	DDX_Control(pDX, IDC_STATIC_IP_GATEWAY, m_Ctrl_Label_NET1_GATEWAY);
	DDX_Control(pDX, IDC_STATIC_IP_ADDRESS2, m_Ctrl_Label_NET1_IPMASK);
	DDX_Control(pDX, IDC_STATIC_IP_ADDRESS5, m_Ctrl_Label_NET2_IP);
	DDX_Control(pDX, IDC_STATIC_IP_GATEWAY2, m_Ctrl_Label_NET2_GATEWAY);
	DDX_Control(pDX, IDC_STATIC_IP_ADDRESS6, m_Ctrl_Label_NET2_IPMASK);
	DDX_Control(pDX, IDC_STATIC_DEV_MODE, m_Ctrl_Label_Dev_Name);
	DDX_Radio(pDX, IDC_NET1_MODE_STATIC, m_iNet1Mode);
	DDX_Radio(pDX, IDC_NET2_MODE_STATIC, m_iNet2Mode);
}


BEGIN_MESSAGE_MAP(CARTBasicPage, CDialog)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_NET1_MODE_STATIC, &CARTBasicPage::OnBnClickedNet1ModeStatic)
	ON_BN_CLICKED(IDC_NET1_DHCP, &CARTBasicPage::OnBnClickedNet1Dhcp)
	ON_BN_CLICKED(IDC_NET2_MODE_STATIC, &CARTBasicPage::OnBnClickedNet2ModeStatic)
	ON_BN_CLICKED(IDC_NET2_DHCP, &CARTBasicPage::OnBnClickedNet2Dhcp)
END_MESSAGE_MAP()


CARTDoc *CARTBasicPage::GetDocument()
{
	CMainFrame *pFrm = (CMainFrame *)AfxGetMainWnd();

	ASSERT(pFrm);

	CDocument *pDoc = pFrm->GetActiveDocument();

	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CARTDoc)));

	return (CARTDoc *)pDoc;
}

BOOL CARTBasicPage::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_Ctrl_DTPicker_DevDate.SetFormat(_T("yyyy-MM-dd"));
	m_Ctrl_DTPicker_DevTime.SetFormat(_T("HH:mm:ss"));

	SetTimer(SecondTimer, 1000, 0);

	for (int i = 0 ; i< ART_TIME_ZONE_MAX ; i++)
	{
		m_Ctrl_Combo_TimeZone.InsertString(i, g_Art_Time_Zone[i].szTimeZone);
	}

	m_Ctrl_Label_Dev_Name.SetTextColor(RGB(128,128,128));
	m_Ctrl_Label_Dev_Name.SetFontBold(TRUE);
	m_Ctrl_Label_Dev_Name.SetFontSize(28);

	/************************************************************************************************
	初始化列表框值
	*************************************************************************************************/
	CDevManager *pDevManager = GetDocument()->GetDeviceManager();
	CDevice     *pDevice     = pDevManager->QueryDeviceByIP(m_dwDevIPSelected);

	ASSERT(pDevice);

//	CBitmap bmp;
//	HBITMAP hBmp;

	if (pDevice != NULL)
	{
		m_szDevName    = pDevice->Get_DevName();
		m_dwDevIP      = pDevice->Get_DevIP();
		m_Ctrl_Label_Dev_Name.SetWindowText(_T("阿尔泰科技"));

		m_bDevNet1Mode         = pDevice->Get_DevNet1Mode();
		
		m_dwDevNet1IP      = pDevice->Get_DevNet1IP();
		m_dwDevNet1IPMask  = pDevice->Get_DevNet1IPMask();
		m_dwDevNet1GateWay = pDevice->Get_DevNet1IPGateWay();

		m_bDevNet2Mode     = pDevice->Get_DevNet2Mode();
		m_dwDevNet2IP      = pDevice->Get_DevNet2IP();
		m_dwDevNet2IPMask  = pDevice->Get_DevNet2IPMask();
		m_dwDevNet2GateWay = pDevice->Get_DevNet2IPGateWay();
		
		m_Ctrl_DTPicker_DevDate.SetTime(pDevice->Get_DevTime());
		m_Ctrl_DTPicker_DevTime.SetTime(pDevice->Get_DevTime());
		m_Ctrl_Combo_TimeZone.SetCurSel(pDevice->Get_DevTimeZone());

		int iDevMode = pDevice->Get_DevModeID();

		switch (iDevMode)
		{
			case SERIALSERV_DEVICEMODEL_SC5083:
				//bmp.LoadBitmap(IDB_SC5083);
				//hBmp = (HBITMAP)bmp.GetSafeHandle();
				//m_Ctrl_Pic_Product_Image.SetBitmap(hBmp);

				break;

			default:

				break;
		}
		
		
	}
	else
	{
		m_Ctrl_Combo_TimeZone.SetCurSel(g_Art_Time_Zone_Default);
	}

	m_iNet1Mode = m_bDevNet1Mode;
	m_iNet2Mode = m_bDevNet2Mode;
	ShowNet1Ctrl(m_bDevNet1Mode);
	ShowNet2Ctrl(m_bDevNet2Mode);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control

}


void CARTBasicPage::OnTimer(UINT_PTR nIDEvent)
{
	CTime timeShow;
	CTimeSpan timeAdd(0,0,0,1);

    m_Ctrl_DTPicker_DevTime.GetTime(timeShow);
	timeShow+=timeAdd;
	m_Ctrl_DTPicker_DevTime.SetTime(&timeShow);

	CDialog::OnTimer(nIDEvent);
}

void CARTBasicPage::OnDestroy()
{
	CDialog::OnDestroy();
	KillTimer(SecondTimer);
}

int  CARTBasicPage::SaveData()
{
	CDevManager  *pDevManager = GetDocument()->GetDeviceManager();
	CDevice      *pDevice       =  pDevManager->QueryDeviceByIP(m_dwDevIPSelected);
	CTime tTimeDate;
	CTime tTimetime;
	BOOL  bRet; 

	ASSERT(pDevice!= NULL);
	if (pDevice == NULL)
	{
		return 0;
	}

	UpdateData(TRUE);

	if ((m_szDevName.IsEmpty())
		||(m_dwDevIP == 0))
	{
		MessageBox(_T("设备名称及设备IP不能为空为0！"),_T("提示信息"), MB_OK);
		return 0;
	}

	pDevice->Set_DevName(m_szDevName);
	pDevice->Set_DevNet1Mode(m_bDevNet1Mode);
	pDevice->Set_DevNet1IP(m_dwDevNet1IP);
	pDevice->Set_DevNet1IPMask(m_dwDevNet1IPMask);
	pDevice->Set_DevNet1IPGateWay(m_dwDevNet1GateWay);

	pDevice->Set_DevNet2Mode(m_bDevNet2Mode);
	pDevice->Set_DevNet2IP(m_dwDevNet2IP);
	pDevice->Set_DevNet2IPMask(m_dwDevNet2IPMask);
	pDevice->Set_DevNet2IPGateWay(m_dwDevNet2GateWay);

	pDevice->Set_DevTimeZone(m_Ctrl_Combo_TimeZone.GetCurSel());

	m_Ctrl_DTPicker_DevDate.GetTime(tTimeDate);
	m_Ctrl_DTPicker_DevTime.GetTime(tTimetime);
	pDevice->Set_DevTime(CTime(tTimeDate.GetYear(),
			                    tTimeDate.GetMonth(),
								tTimeDate.GetDay(),
								tTimetime.GetHour(),
								tTimetime.GetMinute(),
								tTimetime.GetSecond()));
	pDevice->Set_CreateTime(CTime::GetCurrentTime());
     
    //记录日志
	CARTDoc     *pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	CLogManager *pLogManager = pDoc->GetLogManager();
	CString      szLog;
	ASSERT(pLogManager!= NULL);

	bRet = pDevice->SaveSysParaToDev();
	if (bRet != TRUE)
	{
		//此出要给出提示信息
		szLog.Format("配置设备%s系统参数:失败!",IP_DW2STR(m_dwDevIPSelected ));
		pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);
		pDoc->UpdateAllViews(NULL);
		return 0;
	}
	
	szLog.Format("配置设备%s系统参数:成功!",IP_DW2STR(m_dwDevIPSelected ));
	pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);
	pDoc->UpdateAllViews(NULL);

	return 1;
}

void CARTBasicPage::OnBnClickedNet1ModeStatic()
{
	m_bDevNet1Mode = SERIALSERV_DEVICEIPMODE_STATIC;
	ShowNet1Ctrl(m_bDevNet1Mode);
}


void CARTBasicPage::OnBnClickedNet1Dhcp()
{
	m_bDevNet1Mode = SERIALSERV_DEVICEIPMODE_DHCP;
	ShowNet1Ctrl(m_bDevNet1Mode);
}


void CARTBasicPage::OnBnClickedNet2ModeStatic()
{
	m_bDevNet2Mode = SERIALSERV_DEVICEIPMODE_STATIC;
	ShowNet2Ctrl(m_bDevNet2Mode);
}


void CARTBasicPage::OnBnClickedNet2Dhcp()
{
	m_bDevNet2Mode = SERIALSERV_DEVICEIPMODE_DHCP;
	ShowNet2Ctrl(m_bDevNet2Mode);
}

void CARTBasicPage::ShowNet1Ctrl(BYTE iNetMode)
{
	 m_Ctrl_IP_DevNet1IP.ShowWindow(iNetMode == SERIALSERV_DEVICEIPMODE_STATIC);
	 m_Ctrl_IP_DevNet1IPMask.ShowWindow(iNetMode == SERIALSERV_DEVICEIPMODE_STATIC);
	 m_Ctrl_IP_DevNet1GateWay.ShowWindow(iNetMode == SERIALSERV_DEVICEIPMODE_STATIC);
	 m_Ctrl_Label_NET1_IP.ShowWindow(iNetMode == SERIALSERV_DEVICEIPMODE_STATIC);
     m_Ctrl_Label_NET1_GATEWAY.ShowWindow(iNetMode == SERIALSERV_DEVICEIPMODE_STATIC);
     m_Ctrl_Label_NET1_IPMASK.ShowWindow(iNetMode == SERIALSERV_DEVICEIPMODE_STATIC);

}

void CARTBasicPage::ShowNet2Ctrl(BYTE iNetMode)
{
	m_Ctrl_IP_DevNet2IP.ShowWindow(iNetMode == SERIALSERV_DEVICEIPMODE_STATIC);
	m_Ctrl_IP_DevNet2IPMask.ShowWindow(iNetMode == SERIALSERV_DEVICEIPMODE_STATIC);
	m_Ctrl_IP_DevNet2GateWay.ShowWindow(iNetMode == SERIALSERV_DEVICEIPMODE_STATIC);
	m_Ctrl_Label_NET2_IP.ShowWindow(iNetMode == SERIALSERV_DEVICEIPMODE_STATIC);
    m_Ctrl_Label_NET2_GATEWAY.ShowWindow(iNetMode == SERIALSERV_DEVICEIPMODE_STATIC);
    m_Ctrl_Label_NET2_IPMASK.ShowWindow(iNetMode == SERIALSERV_DEVICEIPMODE_STATIC);
}
