/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTBasicPage.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: 设备基本配置对话框类声明
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxdtctl.h"
#include "LABEL.H"


class CARTDoc;
// CARTBasicPage 对话框

class CARTBasicPage : public CDialog
{
	DECLARE_DYNAMIC(CARTBasicPage)

public:
	CARTBasicPage(CWnd* pParent = NULL);   // 标准构造函数
	CARTBasicPage(CWnd* pParent, DWORD dwDevIP);   // 扩展构造函数
	virtual ~CARTBasicPage();

// 对话框数据
	enum { IDD = IDD_DLG_BASIC_PAGE };

public:
	CARTDoc *GetDocument();

public:
	DWORD m_dwDevIPSelected;
	int SaveData();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();

public:

	CComboBox      m_Ctrl_Combo_TimeZone;
	CDateTimeCtrl  m_Ctrl_DTPicker_DevDate;
	CDateTimeCtrl  m_Ctrl_DTPicker_DevTime;
	CIPAddressCtrl m_Ctrl_IP_DevNet1IP;
	CIPAddressCtrl m_Ctrl_IP_DevNet1IPMask;
	CIPAddressCtrl m_Ctrl_IP_DevNet1GateWay;

	CIPAddressCtrl m_Ctrl_IP_DevNet2IP;
	CIPAddressCtrl m_Ctrl_IP_DevNet2IPMask;
	CIPAddressCtrl m_Ctrl_IP_DevNet2GateWay;

public:

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();

public:
	CString m_szDevName;
	DWORD   m_dwDevIP  ;

	BYTE    m_bDevNet1Mode;
	DWORD   m_dwDevNet1IP;
	DWORD   m_dwDevNet1IPMask;
	DWORD   m_dwDevNet1GateWay;

	BYTE    m_bDevNet2Mode;
	DWORD   m_dwDevNet2IP;
	DWORD   m_dwDevNet2IPMask;
	DWORD   m_dwDevNet2GateWay;

	CStatic m_Ctrl_Pic_Product_Image;
	afx_msg void OnBnClickedNet1ModeStatic();
	afx_msg void OnBnClickedNet1Dhcp();
	afx_msg void OnBnClickedNet2ModeStatic();
	afx_msg void OnBnClickedNet2Dhcp();
	CButton m_Ctrl_Radio_Net1Mode;
	CButton m_Ctrl_Radio_Net2Mode;

public:
	void ShowNet1Ctrl(BYTE iNetMode);
	void ShowNet2Ctrl(BYTE iNetMode);

	CStatic m_Ctrl_Label_NET1_IP;
	CStatic m_Ctrl_Label_NET1_GATEWAY;
	CStatic m_Ctrl_Label_NET1_IPMASK;
	CStatic m_Ctrl_Label_NET2_IP;
	CStatic m_Ctrl_Label_NET2_GATEWAY;
	CStatic m_Ctrl_Label_NET2_IPMASK;
	CLabel  m_Ctrl_Label_Dev_Name;
	int m_iNet1Mode;
	int m_iNet2Mode;
};
