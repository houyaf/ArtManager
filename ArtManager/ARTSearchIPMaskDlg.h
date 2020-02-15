#pragma once
#include "afxwin.h"
#include "ARTSearchDlg.h"
#include "LABEL.H"
// CARTSearchIPMaskDlg 对话框
class CARTDoc ;
class CARTSearchIPMaskDlg : public CARTSearchDlg
{
	DECLARE_DYNAMIC(CARTSearchIPMaskDlg)

public:
	CARTSearchIPMaskDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CARTSearchIPMaskDlg();
	//CARTDoc *GetDocument();
// 对话框数据
	enum { IDD = IDD_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedBtnSearch();
	afx_msg LRESULT OnTaskComplete(WPARAM wp, LPARAM lp);

	CListCtrl m_Ctrl_List_Device;
	virtual BOOL OnInitDialog();
	CStatic m_Ctrl_Label_SearchResult;

public:
	void SetPorgressInfo(LPCTSTR szInfo); 
	void AddFoundDevice(CDevice *pDevice);
	CARTDoc *GetDocument();
    CDevManager *GetDevManger();
public:
	CMutex m_mutex;
	CARTDevSearchTask *m_pSearchTask;
	int   m_iExit ;
	int    m_iFoundedNum ;
	BOOL   m_bComplete   ;
	CButton m_Ctrl_Btn_Search;
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDestroy();

	CLabel m_Ctrl_Label_Searching;
};
