#pragma once


// CARTDlgMonitor �Ի���
#include "resource.h"
#include "afxcmn.h"
class CARTDoc;
class CARTDlgMonitor : public CDialog
{
	DECLARE_DYNAMIC(CARTDlgMonitor)

public:
	CARTDlgMonitor(CWnd* pParent = NULL);   // ��׼���캯��
	CARTDlgMonitor(CWnd* pParent , DWORD dwIP);   // ��׼���캯��
	CARTDlgMonitor(CWnd* pParent , DWORD dwIP, int iPort);   // ��׼���캯��

	virtual ~CARTDlgMonitor();

// �Ի�������
	enum { IDD = IDD_DLG_MONITOR };

public:
	CARTDoc *GetDocument();

public:

	DWORD m_dwDevIPSelected;
	int	  m_iPortSelected  ;

public:

	void SetChannelStaticData(int iRow, CChannelStatistics *pChannelStatic, unsigned char ucStatus);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOk();
	virtual BOOL OnInitDialog();
	CListCtrl m_Ctrl_List_ChannelStatic;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void SetChannelStatic();
};
