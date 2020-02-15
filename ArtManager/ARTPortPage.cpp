/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTPortPage.cpp
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: 串口配置对话框类实现文件
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

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


// CARTPortPage 对话框

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
函 数 名 :OnInitDialog
功能描述 :端口配置对话框初始化消息处理
输入参数 :......
输出参数 :......
返 回 值 :......
**************************************************************************************************/
BOOL CARTPortPage::OnInitDialog()
{
	CDialog::OnInitDialog();

	int iRow;
	CString szText;

	/************************************************************************************************
	串口物理参数列表框初始化
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
	m_Ctrl_List_PortPara.InsertColumn(1, _T("串口号")   , LVCFMT_CENTER , 50);
	m_Ctrl_List_PortPara.InsertColumn(2, _T("端口状态") , LVCFMT_CENTER , 70);
	m_Ctrl_List_PortPara.InsertColumn(3, _T("别名")     , LVCFMT_LEFT , 100);
	m_Ctrl_List_PortPara.InsertColumn(4, _T("波特率")   , LVCFMT_LEFT , 50);
	m_Ctrl_List_PortPara.InsertColumn(5, _T("工作模式") , LVCFMT_LEFT , 80);
	m_Ctrl_List_PortPara.InsertColumn(6, _T("校验位")   , LVCFMT_LEFT , 50);
	m_Ctrl_List_PortPara.InsertColumn(7, _T("数据位")   , LVCFMT_LEFT , 50);
	m_Ctrl_List_PortPara.InsertColumn(8, _T("停止位")   , LVCFMT_LEFT , 50);
	m_Ctrl_List_PortPara.InsertColumn(9, _T("流控")     , LVCFMT_LEFT , 55);

	/************************************************************************************************
	串口工作模式列表框初始化
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
	m_Ctrl_List_PortMode.InsertColumn(1, _T("串口号"), LVCFMT_LEFT , 50);
	m_Ctrl_List_PortMode.InsertColumn(2, _T("网络通道数目"), LVCFMT_LEFT , 150);
	
	/************************************************************************************************
	初始化列表框值
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
			//串口参数列表框填值
			/***********************************************************************************************************/
			if (pPort != NULL)
			{
				m_Ctrl_List_PortPara.InsertItem(iRow, _T(""));

				//串口号
				szText.Format("%d", pPort->Get_Index());
				m_Ctrl_List_PortPara.SetItemText(iRow, 1, szText);

				//串口状态
				int iPortSwitch = pPort->Get_PortSwitch();
				if (iPortSwitch == SERIALSERV_SWITCH_OFF)
				{
					szText.Format("关闭");
				}
				else
				{
					szText.Format("打开");
				}
				m_Ctrl_List_PortPara.SetItemText(iRow, 2, szText);

				//别名
				szText.Format("%s", pPort->Get_PortName());
				m_Ctrl_List_PortPara.SetItemText(iRow, 3, szText);

				//波特率
				szText.Format("%s", PORT_Get_BaudRate_Text(pPort->Get_BaudRate()));
				m_Ctrl_List_PortPara.SetItemText(iRow, 4, szText);

				//接口模式
				szText.Format("%s", PORT_Get_Interface_Text(pPort->Get_Interface()));
				m_Ctrl_List_PortPara.SetItemText(iRow, 5, szText);

				//校验位
				szText.Format("%s", PORT_Get_Parity_Text(pPort->Get_Parity()));
				m_Ctrl_List_PortPara.SetItemText(iRow, 6, szText);

				//数据位
				//szText.Format("%s", );
				m_Ctrl_List_PortPara.SetItemText(iRow, 7, PORT_Get_DataBits_Text(pPort->Get_DataBits()));

				//停止位
				//szText.Format("%s", );
				m_Ctrl_List_PortPara.SetItemText(iRow, 8, PORT_Get_StopBits_Text(pPort->Get_StopBits()));

				//流控
				szText.Format("%s", PORT_Get_FlowCtrl_Text(pPort->Get_FlowCtrl()));
				m_Ctrl_List_PortPara.SetItemText(iRow, 9, szText);

				/*****************************************************************************************************************/
				//串口工作模式列表框填值
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
函 数 名 :SetListCtrlSelectedState
功能描述 :列表框单条选项选中状态设置
输入参数 :......
输出参数 :......
返 回 值 :......
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
函 数 名 :OnLvnItemchangedListPortPara
功能描述 :串口物理特性列表框消息处理
输入参数 :......
输出参数 :......
返 回 值 :......
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
函 数 名 :OnLvnItemchangedListPortMode
功能描述 :串口模式特性列表框消息处理
输入参数 :......
输出参数 :......
返 回 值 :......
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
函 数 名 :OnBnClickedBtnPortpara
功能描述 :串口参数“重新设定” click消息处理
输入参数 :......
输出参数 :......
返 回 值 :......
**************************************************************************************************/
void CARTPortPage::OnBnClickedBtnPortpara()
{

	if (m_szPortSelectedofPortPara == "")
	{
		MessageBox(_T("请先在串口参数列表中选定要设定的端口！"),_T("提示信息"), MB_OK);
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
函 数 名 :OnBnClickedBtnPortmode
功能描述 :串口模式“重新设定” click消息处理
输入参数 :......
输出参数 :......
返 回 值 :......
**************************************************************************************************/
void CARTPortPage::OnBnClickedBtnPortmode()
{
	// TODO: 在此添加控件通知处理程序代码
	

	if (m_szPortSelectedofPortMode == "")
	{
		MessageBox(_T("请先在串口工作模式列表中选定要设定的端口！"),_T("提示信息"), MB_OK);
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
函 数 名 :OnNMClickListPortPara
功能描述 :串口参数列表框中checkbox单击处理
输入参数 :......
输出参数 :......
返 回 值 :......
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
函 数 名 :OnNMClickListPortMode
功能描述 :串口工作模式列表框中checkbox单击处理
输入参数 :......
输出参数 :......
返 回 值 :......
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
	// TODO: 在此添加控件通知处理程序代码
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
