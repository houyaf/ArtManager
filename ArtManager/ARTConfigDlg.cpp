/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTConfigDlg.cpp
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: �豸���öԻ����� ʵ���ļ�
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/
#include "stdafx.h"
#include "ART.h"
#include "ARTConfigView.h"
#include "resource.h"
#include "ARTDoc.h"
#include "ARTConfigDlg.h"
#include "afxdialogex.h"
#include "ARTBasicPage.h"
#include "ARTPortPage.h"
#include "MainFrm.h"


// CARTConfigDlg �Ի���
IMPLEMENT_DYNAMIC(CARTConfigDlg, CDialog)

CARTConfigDlg::CARTConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CARTConfigDlg::IDD, pParent)
	, m_szDevMode(_T(""))
	, m_iDevPortNum(0)
	, m_szSWVersion(_T(""))
	, m_szUpTime(_T(""))
{

}

CARTConfigDlg::CARTConfigDlg(CWnd* pParent , DWORD dwHostIp)
	: CDialog(CARTConfigDlg::IDD, pParent)
	, m_dwDevIPSelected(dwHostIp)
	, m_szDevMode(_T(""))
	, m_iDevPortNum(0)
	, m_szSWVersion(_T(""))
	, m_szUpTime(_T(""))
{
	

}

CARTConfigDlg::~CARTConfigDlg()
{
}

void CARTConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_CONFIG   , m_TabCtrl_Config);
	DDX_Text(pDX, IDC_DLG_DEV_TYPE    , m_szDevMode);
	DDX_Text(pDX, IDC_DLG_DEV_PORTNUM , m_iDevPortNum);
	DDX_Text(pDX, IDC_DLG_DEV_VERSION , m_szSWVersion);
	DDX_Text(pDX, IDC_DLG_DEV_UPTIME  , m_szUpTime);
}


BEGIN_MESSAGE_MAP(CARTConfigDlg, CDialog)
	ON_WM_DESTROY()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONFIG, &CARTConfigDlg::OnTcnSelchangeTabConfig)
	ON_BN_CLICKED(IDOK, &CARTConfigDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_REBOOT, &CARTConfigDlg::OnBnClickedBtnReboot)
	ON_BN_CLICKED(IDCANCEL, &CARTConfigDlg::OnBnClickedCancel)
	ON_WM_NCDESTROY()
	ON_BN_CLICKED(IDC_BTN_DEV_SAVEDATA, &CARTConfigDlg::OnBnClickedBtnDevSavedata)
END_MESSAGE_MAP()

CARTDoc *CARTConfigDlg::GetDocument()
{
	CMainFrame *pFrm = (CMainFrame *)AfxGetMainWnd();

	ASSERT(pFrm);

	CDocument *pDoc = pFrm->GetActiveDocument();

	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CARTDoc)));

	return (CARTDoc *)pDoc;

}

// CARTConfigDlg ��Ϣ�������


BOOL CARTConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
   

	m_ilTabs.Create(24,24,ILC_COLOR32|ILC_MASK , 2, 2);

	m_ilTabs.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	m_ilTabs.Add(AfxGetApp()->LoadIcon(IDI_ICON2));

	m_TabCtrl_Config.SetImageList(&m_ilTabs);
	
	COLORREF m_color_ming;
	DWORD dwFlags = 0;
	dwFlags |= ETC_SELECTION;
	dwFlags |= ETC_COLOR;
	dwFlags |= ETC_GRADIENT;
	dwFlags |= ETC_BACKTABS;
	dwFlags |= ETC_FLAT;



	m_color_ming=RGB(242,245,252);

	m_TabCtrl_Config.SetBkgndColor(m_color_ming);
	m_TabCtrl_Config.EnableDraw(0 ? BTC_ALL : dwFlags ? BTC_TABS : BTC_NONE); 

	CEnTabCtrl::EnableCustomLook(dwFlags | 0, dwFlags);
	m_TabCtrl_Config.Invalidate();


	CDevManager    *pDevManager = GetDocument()->GetDeviceManager();
	CDevice        *pDevice     = pDevManager->QueryDeviceByIP(m_dwDevIPSelected);
	CTime          *pTime       = NULL;   
	
	if (pDevice != NULL)
	{
		m_szDevMode    = pDevice->Get_DevMode();
		m_iDevPortNum  = pDevice->Get_PortNum();
		pTime          = pDevice->Get_DevUpTime();
		m_szUpTime     = pTime->Format("%Y-%m-%d %H:%M:%S");
		m_szSWVersion  = pDevice->Get_DevSWVersion();

		UpdateData(FALSE);
	}

	CString szTitle;

	ASSERT(m_dwDevIPSelected != 0);
	ASSERT(!m_szDevMode.IsEmpty());

	szTitle.Format(_T("�趨Ŀ�꣺%s(%s)"), m_szDevMode, IP_DW2STR(m_dwDevIPSelected));
	SetWindowText((LPCTSTR)szTitle);

	m_TabCtrl_Config.InsertItem(0, _T("�豸����"), 0);
	m_TabCtrl_Config.InsertItem(1, _T("�˿�����"), 1);
	
	m_pDlgBasicPage = new CARTBasicPage(this, m_dwDevIPSelected);
	m_pDlgBasicPage->Create(CARTBasicPage::IDD, this);

	m_pDlgPortPage  = new CARTPortPage(this, m_dwDevIPSelected) ;
	m_pDlgPortPage->Create(CARTPortPage::IDD, this);

	
	CRect rect;
	GetDlgItem(IDC_STATIC_DUMMY)->GetWindowRect(&rect);

	ScreenToClient(&rect);

	m_pDlgBasicPage->MoveWindow(rect);
	m_pDlgPortPage->MoveWindow(rect);

	ShowChild(0);

	return TRUE;  

}

void CARTConfigDlg::ShowChild(int iChild)
{
	m_pDlgBasicPage->ShowWindow((iChild == 0 )? SW_SHOW : SW_HIDE );
	m_pDlgPortPage->ShowWindow((iChild == 1 )? SW_SHOW : SW_HIDE );
}

void CARTConfigDlg::OnDestroy()
{
	CDialog::OnDestroy();
	// TODO: �ڴ˴������Ϣ����������
}


void CARTConfigDlg::OnTcnSelchangeTabConfig(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int id= m_TabCtrl_Config.GetCurSel();

	ShowChild(id);

	*pResult = 0;
}


void CARTConfigDlg::OnBnClickedOk()
{
	int iRet;
    
	iRet = m_pDlgBasicPage->SaveData();
	if (iRet != 1)
		return ;

	OnOK();
}

void CARTConfigDlg::OnBnClickedBtnReboot()
{

	int iRet ;
			    //��¼��־
	CARTDoc     *pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	CLogManager *pLogManager = pDoc->GetLogManager();
	CString      szLog;
	ASSERT(pLogManager!= NULL);

	if (MessageBox(_T("ȷ��Ҫ�������豸��"),_T("��ʾ��Ϣ"),MB_YESNO) == IDYES)
	{
		CDevManager    *pDevManager = GetDocument()->GetDeviceManager();
		CDevice        *pDevice     = pDevManager->QueryDeviceByIP(m_dwDevIPSelected);
		iRet = pDevice->Reboot();

		if (iRet <=0 )
		{
			//�˳�Ҫ������ʾ��Ϣ
			szLog.Format("���������豸%s����ָ��:ʧ��!",IP_DW2STR(m_dwDevIPSelected ));
			pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);
			pDoc->UpdateAllViews(NULL);
			
		}
		else
		{
			//�˳�Ҫ������ʾ��Ϣ
			szLog.Format("���������豸%s����ָ��:�ɹ�!",IP_DW2STR(m_dwDevIPSelected ));
			pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);

			pDoc->UpdateAllViews(NULL);
			OnCancel();
		}

	}
	

}

void CARTConfigDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}


void CARTConfigDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();
	
	m_pDlgBasicPage->DestroyWindow();
	delete m_pDlgBasicPage ;
	m_pDlgBasicPage = NULL ;

	m_pDlgPortPage->DestroyWindow();
	delete m_pDlgPortPage ;
	m_pDlgPortPage = NULL ;

}



void CARTConfigDlg::OnBnClickedBtnDevSavedata()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iRet ;
			    //��¼��־
	CARTDoc     *pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	CLogManager *pLogManager = pDoc->GetLogManager();
	CString      szLog;
	ASSERT(pLogManager!= NULL);

	
	CDevManager    *pDevManager = GetDocument()->GetDeviceManager();
	CDevice        *pDevice     = pDevManager->QueryDeviceByIP(m_dwDevIPSelected);
	iRet = pDevice->SaveData();

	if (iRet <=0 )
	{
		//�˳�Ҫ������ʾ��Ϣ
		szLog.Format("�����豸%s��������:ʧ��!",IP_DW2STR(m_dwDevIPSelected ));
		pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);
		pDoc->UpdateAllViews(NULL);
			
	}
	else
	{
		//�˳�Ҫ������ʾ��Ϣ
		szLog.Format("�����豸%s��������:�ɹ�!",IP_DW2STR(m_dwDevIPSelected ));
		pLogManager->AddLog(LOG_MSG,(LPCTSTR)szLog);
			
		pDoc->UpdateAllViews(NULL);
	}

	

}
