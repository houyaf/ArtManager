#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "LABEL.H"
#include "EnTabCtrl.h"

// CARTDlgPortChannel 对话框
class CARTChannelConfig;
class CARTDoc;
class CARTDlgPortChannel : public CDialog
{
	DECLARE_DYNAMIC(CARTDlgPortChannel)

public:
	CARTDlgPortChannel(CWnd* pParent = NULL);   // 标准构造函数
	CARTDlgPortChannel(CWnd* pParent , DWORD dwIP);   
	CARTDlgPortChannel(CWnd* pParent , DWORD dwIP, int iPort);   
	virtual ~CARTDlgPortChannel();

	CARTDoc *GetDocument();

public:
	DWORD     m_dwDevIPSelected;
	int       m_iPortSelected;


	int   m_iChannelNum ;

	CARTChannelConfig    *m_pChannel1;
	CARTChannelConfig    *m_pChannel2;
	CARTChannelConfig    *m_pChannel3;
	CARTChannelConfig    *m_pChannel4;
	CARTChannelConfig    *m_pChannel5;
	CARTChannelConfig    *m_pChannel6;

	void ShowChild(int iChild);

// 对话框数据
	enum { IDD = IDD_DLG_PORT_CHANNEL };

public:
	void UpdateChannelNum();



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CEnTabCtrl  m_Ctrl_Tab_Channel;
	COLORREF    m_color;
	CImageList  m_ilTabs; 

public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);

	CLabel m_Ctrl_Label_ChannelNum;
};
