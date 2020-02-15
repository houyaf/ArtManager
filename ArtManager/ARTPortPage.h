/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTPortPage.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: 串口配置对话框类接口
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/
#pragma once
#include "LABEL.H"
#include "afxcmn.h"

class CARTDoc;
// CARTPortPage 对话框

class CARTPortPage : public CDialog
{
	DECLARE_DYNAMIC(CARTPortPage)

public:
	CARTPortPage(CWnd* pParent = NULL);   // 标准构造函数
	CARTPortPage(CWnd* pParent, DWORD dwDevIP);   // 扩展构造函数
	virtual ~CARTPortPage();

// 对话框数据
	enum { IDD = IDD_DLG_PORT_PAGE };

public:
	CARTDoc *GetDocument();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Ctrl_List_PortPara;
	CListCtrl m_Ctrl_List_PortMode;
	void SetListCtrlSelectedState(CListCtrl& ListCtrl, int iRow, UINT ulState, UINT ulMask, UINT iCtrlIndex);

	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedListPortPara(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListPortMode(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnPortpara();
	afx_msg void OnBnClickedBtnPortmode();
	afx_msg void OnNMClickListPortPara(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListPortMode(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg LRESULT SetCtrlInitValue(WPARAM wParam, LPARAM lParam);

	CString m_szPortSelectedofPortPara;
	CString m_szPortSelectedofPortMode;
	DWORD   m_dwDevIPSelected ;
	afx_msg void OnBnClickedBtnConfigAllport();
	afx_msg void OnDblclkListPortPara(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListPortWorkMode(NMHDR *pNMHDR, LRESULT *pResult);
};
