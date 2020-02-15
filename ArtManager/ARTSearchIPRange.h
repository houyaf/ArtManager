#pragma once
#include "afxwin.h"
#include "ARTSearchDlg.h"
#include "LABEL.H"
// CARTSearchIPRange 对话框
class CARTDoc ;
class CARTSearchIPRange : public CARTSearchDlg
{
	DECLARE_DYNAMIC(CARTSearchIPRange)

public:
	CARTSearchIPRange(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CARTSearchIPRange();
	//CARTDoc *GetDocument();
// 对话框数据
	enum { IDD = IDD_SEARCH_IPRANGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CMutex m_mutex;
	CARTDevSearchTask *m_pSearchTask;
	BOOL   m_bComplete;
	int    m_iFoundedNum ;
	int    m_iExit ;

public:
	afx_msg void OnBnClickedBtnSearch();
	afx_msg LRESULT OnTaskComplete(WPARAM wp, LPARAM lp);
	CListCtrl m_Ctrl_List_Device;
	virtual BOOL OnInitDialog();
	CStatic m_Ctrl_Label_SearchResult;

public:
	void SetPorgressInfo(LPCTSTR szInfo); 
	void AddFoundDevice(CDevice *pDevice);
    CDevManager *GetDevManger();
	CARTDoc *GetDocument();
	CButton m_Ctrl_Btn_Search;
	afx_msg void OnClose();
	DWORD m_dwSearchIPS;
	DWORD m_dwSearchIPE;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CLabel m_Ctrl_Label_Searching;
};
