#pragma once
#include "afxwin.h"
#include "LABEL.H"


// CARTTaskView 窗体视图

class CARTTaskView : public CFormView
{
	DECLARE_DYNCREATE(CARTTaskView)

protected:
	CARTTaskView();           // 动态创建所使用的受保护的构造函数
	virtual ~CARTTaskView();

public:
	CARTDoc* GetDocument() const;

public:
	enum { IDD = IDD_ARTTASKVIEW };

#ifdef _DEBUG
	virtual void AssertValid() const;

#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	CLabel m_FuncLabel    ;
	CLabel m_AddLabel     ;
	CLabel m_SearchLabel  ;
	CLabel m_SearchIPLabel;
	CLabel m_Ctrl_Lable_IPRange;
	CLabel m_Ctrl_Label_Monitor_Msg;
	CBrush m_BkBrush ;
public:
	void ShowTaskView(int iView) ;

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnClickedStaticSearch();
	afx_msg void OnStnClickedStaticSearchByIp();
	
	afx_msg void OnStnClickedStaticSearchByIprange();
	
};


