/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTCOMPortParaConfigDlg.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: CARTCOMPortParaConfigDlg类接口
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/
#pragma once
#include "afxwin.h"

class CARTDoc;

class CARTCOMPortParaConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CARTCOMPortParaConfigDlg)

public:
	CARTCOMPortParaConfigDlg(CWnd* pParent = NULL);
	CARTCOMPortParaConfigDlg(CWnd* pParent, DWORD dwIP); 
	CARTCOMPortParaConfigDlg(CWnd* pParent, DWORD dwIP, int iComPort); 

	virtual ~CARTCOMPortParaConfigDlg();

// 对话框数据
	enum { IDD = IDD_DLG_PORTPARA_CONFIG };

public:
	CARTDoc *GetDocument();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

public:
	bool m_bForAllPort;
	int SaveDataToOne();
	int SaveDataToAll();

public:

	CComboBox m_Ctrl_Combo_BaudRate;
	CComboBox m_Ctrl_Combo_Parity;

	CComboBox m_Ctrl_Combo_Databits;
	CComboBox m_Ctrl_Combo_StopBits;
	CComboBox m_Ctrl_Combo_Interface;
	CComboBox m_Ctrl_Combo_FlowControl;
	
	DWORD     m_dwDevIPSelected;
	int       m_iPortSelected;
	afx_msg void OnBnClickedOk();
	CString m_szPortName;
	CButton m_Ctrl_Radio_PortSwitch_ON;
	CButton m_Ctrl_Radio_PortSwitch_OFF;
};
