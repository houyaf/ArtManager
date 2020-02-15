/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTCOMPortParaConfigDlg.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: CARTCOMPortParaConfigDlg��ӿ�
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

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

// �Ի�������
	enum { IDD = IDD_DLG_PORTPARA_CONFIG };

public:
	CARTDoc *GetDocument();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
