#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CARTChannelConfig 对话框
class CARTDoc;
class CARTDlgPortChannel;
class CARTChannelConfig : public CDialog
{
	DECLARE_DYNAMIC(CARTChannelConfig)

public:
	CARTChannelConfig(CWnd* pParent = NULL);   // 标准构造函数
	CARTChannelConfig(CWnd* pParent, DWORD dwIP, int iPort, int iChannelID);   // 标准构造函数
	virtual ~CARTChannelConfig();

	void ShowConfigAreaByChannelMode(int iMode);

// 对话框数据
	enum { IDD = IDD_DLG_CHANNELMODE_PAGE };
public:
	CARTDoc *GetDocument();

public:
	int			m_iChannelID	;
	DWORD		m_dwDevIPSelected;
	int			m_iPortSelected  ;
	BOOL        m_bChannelSwitch ;

	CWnd *m_pParent ;

	void SetFieldsStatus(BOOL bEnabled);
	void SetDefaultValues();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	BOOL SaveChannelData();

	unsigned char  m_ucOpMode;
	unsigned short m_usCOMPort;

public:
	CStatic   m_Ctrl_Static_UDPClient_Host;
	CEdit     m_Ctrl_Edit_UDPClient_Host;
	CStatic   m_Ctrl_Static_UCPClient_Port;
	CEdit     m_Ctrl_Edit_UDPClient_Port;

	CStatic   m_Ctrl_Static_TCPClient_Host;
	CEdit     m_Ctrl_Edit_TCPClient_Host;
	CStatic   m_Ctrl_Static_TCPClient_Port;
	CEdit     m_Ctrl_Edit_TCPClient_Port;

	CStatic   m_Ctrl_Static_UDPServer_Port;
	CEdit     m_Ctrl_Edit_UDPServer_Port;

	CStatic   m_Ctrl_Static_TCPServer_Port;
	CEdit     m_Ctrl_Edit_TCPServer_ListenPort;
	CStatic   m_Ctrl_Static_TCPServer_MaxConn;
	CComboBox m_Ctrl_Combo_TCPServer_MaxConn;


	afx_msg void OnCbnSelchangePortWorkmode();
	CComboBox m_Ctrl_Combo_ChannelMode;
	virtual BOOL OnInitDialog();
	CStatic m_Ctrl_Group_ChannelModeParam;
	afx_msg void OnBnClickedRadioChannelDisable();
	afx_msg void OnBnClickedRadioChannelEnable();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	CButton m_Ctrl_Radio_ChannelSwitch_ON;
	CButton m_Ctrl_Radio_ChannelSwitch_OFF;
	CComboBox m_Ctrl_Combo_TCPServer_MaxConnection;
	CIPAddressCtrl m_Ctrl_IPAddr_TCPClient_Host;
	CIPAddressCtrl m_Ctrl_IPAddr_UDPClient_Host;
};
