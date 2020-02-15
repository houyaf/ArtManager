/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTPortPage.cpp
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: �������öԻ�����ʵ���ļ�
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/


#include "stdafx.h"
#include "ART.h"
#include "ARTPortPage.h"
#include "afxdialogex.h"
#include "ARTDlgPortChannel.h"
#include "ARTCOMPortParaConfigDlg.h"
#include "MainFrm.h"
#include "ARTDoc.h"


#define  SET_CTRL_INIT_VALUE  WM_USER+1001


// CARTPortPage �Ի���

IMPLEMENT_DYNAMIC(CARTPortPage, CDialog)

CARTPortPage::CARTPortPage(CWnd* pParent /*=NULL*/)
	: CDialog(CARTPortPage::IDD, pParent)
	, m_szPortSelectedofPortPara(_T(""))
	, m_szPortSelectedofPortMode(_T(""))
{

}

CARTPortPage::CARTPortPage(CWnd* pParent, DWORD dwDevIP)
	: CDialog(CARTPortPage::IDD, pParent)
	, m_szPortSelectedofPortPara(_T(""))
	, m_szPortSelectedofPortMode(_T(""))
	, m_dwDevIPSelected(dwDevIP)
{
	

}

CARTPortPage::~CARTPortPage()
{
}

void CARTPortPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PORT1, m_Ctrl_List_PortPara);
	DDX_Control(pDX, IDC_LIST_PORT2, m_Ctrl_List_PortMode);

	DDX_Text(pDX, IDC_STATIC_PORTSELECTED_PORTPARA, m_szPortSelectedofPortPara);
	DDX_Text(pDX, IDC_STATIC_PORTSELECTED_PORTMODE, m_szPortSelectedofPortMode);
}


BEGIN_MESSAGE_MAP(CARTPortPage, CDialog)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PORT1, &CARTPortPage::OnLvnItemchangedListPortPara)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PORT2, &CARTPortPage::OnLvnItemchangedListPortMode)
	ON_BN_CLICKED(IDC_BTN_PORTPARA, &CARTPortPage::OnBnClickedBtnPortpara)
	ON_BN_CLICKED(IDC_BTN_PORTMODE, &CARTPortPage::OnBnClickedBtnPortmode)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PORT1, &CARTPortPage::OnNMClickListPortPara)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PORT2, &CARTPortPage::OnNMClickListPortMode)
	ON_BN_CLICKED(IDC_BTN_CONFIG_ALLPORT, &CARTPortPage::OnBnClickedBtnConfigAllport)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PORT1, &CARTPortPage::OnDblclkListPortPara)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PORT2, &CARTPortPage::OnDblclkListPortWorkMode)


END_MESSAGE_MAP()


CARTDoc *CARTPortPage::GetDocument()
{
	CMainFrame *pFrm = (CMainFrame *)AfxGetMainWnd();

	ASSERT(pFrm);

	CDocument *pDoc = pFrm->GetActiveDocument();

	ASSERT(pDoc->IsKindOf(RUNTIME_CLASS(CARTDoc)));

	return (CARTDoc *)pDoc;
}


/**************************************************************************************************
�� �� �� :OnInitDialog
�������� :�˿����öԻ����ʼ����Ϣ����
������� :......
������� :......
�� �� ֵ :......
**************************************************************************************************/
BOOL CARTPortPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	int iRow;
	CString szText;

	/************************************************************************************************
	������������б���ʼ��
	*************************************************************************************************/
	int  iCount;
	CHeaderCtrl *pHeadCtrl = m_Ctrl_List_PortPara.GetHeaderCtrl();

	if (pHeadCtrl != NULL)
	{
		iCount = pHeadCtrl->GetItemCount();
		
		for (int i=0; i< iCount; i++)
		{
			m_Ctrl_List_PortPara.DeleteColumn(0);
		}

		m_Ctrl_List_PortPara.DeleteAllItems();
	}

	m_Ctrl_List_PortPara.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT|LVS_SHOWSELALWAYS);
	m_Ctrl_List_PortPara.SetExtendedStyle(LVS_EX_CHECKBOXES |LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);

	m_Ctrl_List_PortPara.InsertColumn(0, _T("")		    , LVCFMT_LEFT , 20);
	m_Ctrl_List_PortPara.InsertColumn(1, _T("���ں�")   , LVCFMT_CENTER , 50);
	m_Ctrl_List_PortPara.InsertColumn(2, _T("�˿�״̬") , LVCFMT_CENTER , 70);
	m_Ctrl_List_PortPara.InsertColumn(3, _T("����")     , LVCFMT_LEFT , 100);
	m_Ctrl_List_PortPara.InsertColumn(4, _T("������")   , LVCFMT_LEFT , 50);
	m_Ctrl_List_PortPara.InsertColumn(5, _T("����ģʽ") , LVCFMT_LEFT , 80);
	m_Ctrl_List_PortPara.InsertColumn(6, _T("У��λ")   , LVCFMT_LEFT , 50);
	m_Ctrl_List_PortPara.InsertColumn(7, _T("����λ")   , LVCFMT_LEFT , 50);
	m_Ctrl_List_PortPara.InsertColumn(8, _T("ֹͣλ")   , LVCFMT_LEFT , 50);
	m_Ctrl_List_PortPara.InsertColumn(9, _T("����")     , LVCFMT_LEFT , 55);

	/************************************************************************************************
	���ڹ���ģʽ�б���ʼ��
	*************************************************************************************************/
	pHeadCtrl = m_Ctrl_List_PortMode.GetHeaderCtrl();
	
	if (pHeadCtrl != NULL)
	{
		iCount = pHeadCtrl->GetItemCount();
		for (int i=0; i< iCount; i++)
		{
			m_Ctrl_List_PortMode.DeleteColumn(0);
		}

		m_Ctrl_List_PortMode.DeleteAllItems();
	}
	
	m_Ctrl_List_PortMode.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST,LVS_REPORT|LVS_SHOWSELALWAYS);
	m_Ctrl_List_PortMode.SetExtendedStyle(LVS_EX_CHECKBOXES |LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES );

	m_Ctrl_List_PortMode.InsertColumn(0, _T(""), LVCFMT_LEFT , 20);
	m_Ctrl_List_PortMode.InsertColumn(1, _T("���ں�"), LVCFMT_LEFT , 50);
	m_Ctrl_List_PortMode.InsertColumn(2, _T("����ͨ����Ŀ"), LVCFMT_LEFT , 150);
	
	/************************************************************************************************
	��ʼ���б��ֵ
	*************************************************************************************************/
	CDevManager *pDevManager = GetDocument()->GetDeviceManager();
	CDevice     *pDevice     = pDevManager->QueryDeviceByIP(m_dwDevIPSelected);
	
	CPortList   *pPortList = NULL;
	int          iPortNum;
	POSITION     pos;
	CPort       *pPort     = NULL;  
	
	ASSERT(pDevice);

	if (pDevice != NULL)
	{
		iPortNum  = pDevice->Get_PortNum();
		pPortList = pDevice->Get_PortList();

		ASSERT(pPortList);

		pos       = pPortList->GetHeadPosition();
		iRow      = 0;
		while(pos != NULL)
		{
			pPort = pPortList->GetNext(pos);
            /***********************************************************************************************************/
			//���ڲ����б����ֵ
			/***********************************************************************************************************/
			if (pPort != NULL)
			{
				m_Ctrl_List_PortPara.InsertItem(iRow, _T(""));

				//���ں�
				szText.Format("%d", pPort->Get_Index());
				m_Ctrl_List_PortPara.SetItemText(iRow, 1, szText);

				//����״̬
				int iPortSwitch = pPort->Get_PortSwitch();
				if (iPortSwitch == SERIALSERV_SWITCH_OFF)
				{
					szText.Format("�ر�");
				}
				else
				{
					szText.Format("��");
				}
				m_Ctrl_List_PortPara.SetItemText(iRow, 2, szText);

				//����
				szText.Format("%s", pPort->Get_PortName());
				m_Ctrl_List_PortPara.SetItemText(iRow, 3, szText);

				//������
				szText.Format("%s", PORT_Get_BaudRate_Text(pPort->Get_BaudRate()));
				m_Ctrl_List_PortPara.SetItemText(iRow, 4, szText);

				//�ӿ�ģʽ
				szText.Format("%s", PORT_Get_Interface_Text(pPort->Get_Interface()));
				m_Ctrl_List_PortPara.SetItemText(iRow, 5, szText);

				//У��λ
				szText.Format("%s", PORT_Get_Parity_Text(pPort->Get_Parity()));
				m_Ctrl_List_PortPara.SetItemText(iRow, 6, szText);

				//����λ
				//szText.Format("%s", );
				m_Ctrl_List_PortPara.SetItemText(iRow, 7, PORT_Get_DataBits_Text(pPort->Get_DataBits()));

				//ֹͣλ
				//szText.Format("%s", );
				m_Ctrl_List_PortPara.SetItemText(iRow, 8, PORT_Get_StopBits_Text(pPort->Get_StopBits()));

				//����
				szText.Format("%s", PORT_Get_FlowCtrl_Text(pPort->Get_FlowCtrl()));
				m_Ctrl_List_PortPara.SetItemText(iRow, 9, szText);

				/*****************************************************************************************************************/
				//���ڹ���ģʽ�б����ֵ
				/*****************************************************************************************************************/
				m_Ctrl_List_PortMode.InsertItem(iRow, _T(""));

				szText.Format("%d", pPort->Get_Index());
				m_Ctrl_List_PortMode.SetItemText(iRow, 1, szText);

				szText.Format("%d", pPort->Get_ChannelNum());
				m_Ctrl_List_PortMode.SetItemText(iRow, 2, szText);
			}
			iRow++;
		}
	}

	//PostMessage(SET_CTRL_INIT_VALUE, 0, 0); 
	return TRUE;  // return TRUE unless you set the focus to a control
}

/**************************************************************************************************
�� �� �� :SetListCtrlSelectedState
�������� :�б����ѡ��ѡ��״̬����
������� :......
������� :......
�� �� ֵ :......
**************************************************************************************************/
void  CARTPortPage::SetListCtrlSelectedState(CListCtrl& ListCtrl, int iRow, UINT ulState, UINT ulMask, UINT iCtrlIndex)
{
	for (int i=0 ; i<ListCtrl.GetItemCount(); i++)
	{
		if (i == iRow)
		{
			ListCtrl.SetCheck( i, TRUE);
			ListCtrl.SetItemState(i, ulState, ulMask);
			if (iCtrlIndex == 1)
			{
				m_szPortSelectedofPortPara = ListCtrl.GetItemText(iRow, 1);
				UpdateData(FALSE);
			}
			else
			{
				m_szPortSelectedofPortMode =  ListCtrl.GetItemText(iRow, 1) ;
				UpdateData(FALSE);
			}
		}
		else
		{
			ListCtrl.SetCheck( i, FALSE);
			ListCtrl.SetItemState(i, 0, ulMask);
		}
	}
};

/**************************************************************************************************
�� �� �� :OnLvnItemchangedListPortPara
�������� :�������������б����Ϣ����
������� :......
������� :......
�� �� ֵ :......
**************************************************************************************************/
void CARTPortPage::OnLvnItemchangedListPortPara(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	CPoint pt;

	GetCursorPos(&pt);
	m_Ctrl_List_PortPara.ScreenToClient(&pt);
	
	int iHitRow;
	
	iHitRow = m_Ctrl_List_PortPara.HitTest(pt);
	SetListCtrlSelectedState(m_Ctrl_List_PortPara, iHitRow, LVNI_SELECTED | LVNI_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED, 1);
	

	*pResult = 0;
}

/**************************************************************************************************
�� �� �� :OnLvnItemchangedListPortMode
�������� :����ģʽ�����б����Ϣ����
������� :......
������� :......
�� �� ֵ :......
**************************************************************************************************/
void CARTPortPage::OnLvnItemchangedListPortMode(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	CPoint pt;

	GetCursorPos(&pt);
	m_Ctrl_List_PortMode.ScreenToClient(&pt);
	
	int iHitRow;
	
	iHitRow = m_Ctrl_List_PortMode.HitTest(pt);
	SetListCtrlSelectedState(m_Ctrl_List_PortMode, iHitRow, LVNI_SELECTED | LVNI_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED, 2);

	*pResult = 0;
}

/**************************************************************************************************
�� �� �� :OnBnClickedBtnPortpara
�������� :���ڲ����������趨�� click��Ϣ����
������� :......
������� :......
�� �� ֵ :......
**************************************************************************************************/
void CARTPortPage::OnBnClickedBtnPortpara()
{

	if (m_szPortSelectedofPortPara == "")
	{
		MessageBox(_T("�����ڴ��ڲ����б���ѡ��Ҫ�趨�Ķ˿ڣ�"),_T("��ʾ��Ϣ"), MB_OK);
	}
	else
	{
		int iPortSelected;
		iPortSelected = atoi(m_szPortSelectedofPortPara.GetBuffer(0));

		CARTCOMPortParaConfigDlg ComParaDlg(this, m_dwDevIPSelected, iPortSelected);
		if (ComParaDlg.DoModal() == IDOK)
		{
			OnInitDialog();
		}
	}
}

/**************************************************************************************************
�� �� �� :OnBnClickedBtnPortmode
�������� :����ģʽ�������趨�� click��Ϣ����
������� :......
������� :......
�� �� ֵ :......
**************************************************************************************************/
void CARTPortPage::OnBnClickedBtnPortmode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	

	if (m_szPortSelectedofPortMode == "")
	{
		MessageBox(_T("�����ڴ��ڹ���ģʽ�б���ѡ��Ҫ�趨�Ķ˿ڣ�"),_T("��ʾ��Ϣ"), MB_OK);
	}
	else
	{   
		int iPortSelected;
		iPortSelected = atoi(m_szPortSelectedofPortMode.GetBuffer(0));

		//CARTCOMPortModeConfigDlg ComModeDlg(this, m_dwDevIPSelected, iPortSelected);

		CARTDlgPortChannel dlg(this, m_dwDevIPSelected, iPortSelected);
		if (dlg.DoModal() == IDOK)
		{
			OnInitDialog();
		}
	}
}

/**************************************************************************************************
�� �� �� :OnNMClickListPortPara
�������� :���ڲ����б����checkbox��������
������� :......
������� :......
�� �� ֵ :......
**************************************************************************************************/
void CARTPortPage::OnNMClickListPortPara(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CPoint pt;
	int  iHitRow;
	UINT ulFlag;
	BOOL bChecked;

	GetCursorPos(&pt);
	m_Ctrl_List_PortPara.ScreenToClient(&pt);
	
	iHitRow = m_Ctrl_List_PortPara.HitTest(pt, &ulFlag);
	if (iHitRow == -1)
	{
		m_szPortSelectedofPortPara = "" ;
		UpdateData(FALSE);
		return ;
	}

	if (ulFlag == LVHT_ONITEMSTATEICON)
	{
		bChecked = m_Ctrl_List_PortPara.GetCheck(iHitRow);

		if (!bChecked)
		{
			SetListCtrlSelectedState(m_Ctrl_List_PortPara, iHitRow, LVNI_SELECTED | LVNI_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED, 1);
		}
	}

	*pResult = 0;
}

/**************************************************************************************************
�� �� �� :OnNMClickListPortMode
�������� :���ڹ���ģʽ�б����checkbox��������
������� :......
������� :......
�� �� ֵ :......
**************************************************************************************************/
void CARTPortPage::OnNMClickListPortMode(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CPoint pt;
	int  iHitRow;
	UINT ulFlag;
	BOOL bChecked;

	GetCursorPos(&pt);
	m_Ctrl_List_PortMode.ScreenToClient(&pt);
	
	iHitRow = m_Ctrl_List_PortMode.HitTest(pt, &ulFlag);
	if (iHitRow == -1)
	{
		m_szPortSelectedofPortMode = "" ;
		UpdateData(FALSE);
		return ;
	}

	if (ulFlag == LVHT_ONITEMSTATEICON)
	{
		bChecked = m_Ctrl_List_PortMode.GetCheck(iHitRow);

		if (!bChecked)
		{
			SetListCtrlSelectedState(m_Ctrl_List_PortMode, iHitRow, LVNI_SELECTED | LVNI_FOCUSED, LVNI_SELECTED | LVNI_FOCUSED, 2);
		}
	}
	
	*pResult = 0;
}


void CARTPortPage::OnBnClickedBtnConfigAllport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CARTCOMPortParaConfigDlg ComParaDlg(this, m_dwDevIPSelected);
	if (ComParaDlg.DoModal() == IDOK)
	{
		OnInitDialog();
	}
}


void CARTPortPage::OnDblclkListPortPara(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickListPortPara(pNMHDR,pResult);
	OnBnClickedBtnPortpara();

	*pResult = 0;
}


void CARTPortPage::OnDblclkListPortWorkMode(NMHDR *pNMHDR, LRESULT *pResult)
{
	OnNMClickListPortMode(pNMHDR,pResult);
	OnBnClickedBtnPortmode();
	*pResult = 0;
}
