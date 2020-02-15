/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTCOMConsole.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: 超级终端工具类声明
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/
#pragma once

#include "resource.h"
#include "afxwin.h"
// CARTCOMConsole 对话框

class CARTDoc ;

class CARTCOMConsole : public CDialog
{
	DECLARE_DYNAMIC(CARTCOMConsole)

public:
	CARTCOMConsole(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CARTCOMConsole();

// 对话框数据
	enum { IDD = IDD_DLG_COM_CONSOLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
