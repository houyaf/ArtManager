/**************************************************************************************************
                                   �汾����(C), 2012-2013, ����XXXXX��˾
***************************************************************************************************
 �� �� ����ARTCOMConsole.h
 �� �� ��: 1.00����
 ��    ��: HYF
 �������ڣ�2013��3��20
 ����޸�:
 ��������: �����ն˹���������
 �����б�:
 �޸���ʷ:
     1.��    �� : 2012-3-20
	   ��    �� : HYF
	   �޸����� : �����ļ�

**************************************************************************************************/
#pragma once

#include "resource.h"
#include "afxwin.h"
// CARTCOMConsole �Ի���

class CARTDoc ;

class CARTCOMConsole : public CDialog
{
	DECLARE_DYNAMIC(CARTCOMConsole)

public:
	CARTCOMConsole(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CARTCOMConsole();

// �Ի�������
	enum { IDD = IDD_DLG_COM_CONSOLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	DWORD         m_dwIP   ;
	unsigned int  m_ulPort ;
	BOOL          m_bConnected;
	CCOMM         *m_pCOMM;
public:
	BOOL m_bASCIIORHex;
	BOOL m_bAutoWrap;
	BOOL m_bShowSentMsg;
	BOOL m_bShowTime;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedBtnSend();

	void UpdateShowMsg();

	CARTDoc *GetDocument();
	CComboBox m_Ctrl_Combo_Device;
	CComboBox m_Ctrl_Combo_Port;
	CEdit m_Ctrl_Edit_MSG;
	CString m_szMSGSend;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboDevice();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedCheckAutowrap();
	afx_msg void OnBnClickedCheckShowsendmsg();
	afx_msg void OnBnClickedCheckShowtime();
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnDestroy();
	CButton m_Ctrl_BTN_Connect;
	CString m_szMSG;
	CEdit m_Ctrl_Edit_SendMsg;
};
