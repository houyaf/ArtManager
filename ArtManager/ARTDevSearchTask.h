/**************************************************************************************************
                                   版本所有(C), 2012-2013, 西安XXXXX公司
***************************************************************************************************
 文 件 名：ARTDevSearchTask.h
 版 本 号: 1.00初版
 作    者: HYF
 生成日期：2013－3－20
 最近修改:
 功能描述: Search Task任务类声明
 函数列表:
 修改历史:
     1.日    期 : 2012-3-20
	   作    者 : HYF
	   修改内容 : 创建文件

**************************************************************************************************/
#pragma once

enum IP_Search_Type
{
	DEVICE_SEARCH_BY_IP = 0,
	DEVICE_SEARCH_BY_IPRANGE,
	DEVICE_SEARCH_BY_IPMASK
};

class CARTSearchDlg;

class CARTDevSearchTask :	public CARTUIThread
{
	DECLARE_DYNCREATE(CARTDevSearchTask)
public:
	CARTDevSearchTask(void);
	~CARTDevSearchTask(void);
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayThread)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

protected:
	int    m_iSearchType ;
	DWORD  m_dwSearchIP  ;
	DWORD  m_dwSearchIP_S;
	DWORD  m_dwSearchIP_E;
	DWORD  m_dwIPMask    ;

public:
	void Set_SearchType(int iSearchType);
	void Set_SearchIP(DWORD dwIP);
	void Set_SearchIPRange(DWORD dwIP_S, DWORD dwIP_E);
	void Set_SearchIPMask(DWORD dwIPMask);
	bool ScanWithWSAEventSelect(DWORD dwIP_S, DWORD dwIP_E);
	bool ScanWithSelect(DWORD dwIP_S, DWORD dwIP_E);
	bool ScanWithConnect(DWORD dwIP_S, DWORD dwIP_E);
	void ProcessHost(SOCKET hSocket);

	bool ProcessScanRequest(DWORD dwIP_S, DWORD dwIP_E);
private:
	void VerfyIPRange();
	afx_msg void OnSearch(WPARAM wParam,LPARAM lParam);
public:
	// Generated message map functions
	//{{AFX_MSG(CCounterThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	
};

