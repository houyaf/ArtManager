#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "ARTSearchDlg.h"
#include "LABEL.H"
// CARTSearchIPDlg 对话框
class CARTDoc ;
class CARTSearchIPDlg : public CARTSearchDlg
{
	DECLARE_DYNAMIC(CARTSearchIPDlg)

public:
	CARTSearchIPDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CARTSearchIPDlg();
	//CARTDoc *GetDocument();

// 对话框数据
	enum { IDD = IDD_SEARCH_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSearch();
	afx_msg LRESULT OnTaskComplete(WPARAM wp, LPARAM lp);

	CListCtrl m_Ctrl_List_Device;
	virtual BOOL OnInitDialog();
	CStatic m_Ctrl_Label_SearchResult;

	CARTDoc *GetDocument();
	CDevManager *GetDevManger();
public:
	CMutex m_mutex;
	CARTDevSearchTask *m_pSearchTask;
	int    m_iExit ;
	int    m_iFoundedNum ;
	BOOL   m_bComplete;

public:
	BOOL ResetListBox();


public :
	void SetPorgressInfo(LPCTSTR szInfo); 
	void AddFoundDevice(CDevice *pDevice);
	CButton m_Ctrl_Btn_Search;
	afx_msg void OnClose();
	DWORD m_dwSearchIP;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CLabel  m_Ctrl_Label_Searching;
};
