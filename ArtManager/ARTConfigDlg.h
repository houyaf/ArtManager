/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTConfigDlg.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: 设备配置对话框类 声明
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/


#pragma once
#include "afxcmn.h"

#include "EntabCtrl.h"


class CARTBasicPage;
class CARTPortPage;
class CARTDoc ;
// CARTConfigDlg 对话框

class CARTConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CARTConfigDlg)

public:
	CARTConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	CARTConfigDlg(CWnd* pParent, DWORD dwDevIP);   // 标准构造函数
	virtual ~CARTConfigDlg();

// 对话框数据
	enum { IDD = IDD_DLG_CONFIG };

public:
	CARTDoc *GetDocument();

public:
	CARTBasicPage    *m_pDlgBasicPage;
	CARTPortPage     *m_pDlgPortPage;

	void ShowChild(int iChild);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
	DECLARE_MESSAGE_MAP()

public:
	CEnTabCtrl  m_TabCtrl_Config;
	COLORREF    m_color;
	CImageList  m_ilTabs; 
public:
	DWORD    m_dwDevIPSelected ;
	
	CString  m_szDevMode;
	int      m_iDevPortNum;
	CString  m_szSWVersion;
	CString  m_szUpTime;
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTcnSelchangeTabConfig(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnReboot();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnNcDestroy();
	afx_msg void OnBnClickedBtnDevSavedata();
};
