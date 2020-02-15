
// MainFrm.h : CMainFrame 类的接口
//
#define NUMVIEWS 4
class CARTDoc ;
#pragma once
class CARTConfigView;
class CARTDoc;
class CARTMonitorTask;
class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
protected:
	CSplitterWnd	m_wndFuncSplitter;
	CSplitterWnd	m_wndSplitter;
	BOOL			m_bSplitterCreated;
public:
	
	CARTMonitorTask *m_pMonitorTask ;
	BOOL             m_bRunning     ;

    // Index to current view
    UINT m_nCurView;   

// 操作
public:


// 重写
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();

public: 
	void CreateFuncView(int iFuncMode);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar  ;
	CReBar            m_wndReBar    ;
	CDialogBar        m_wndDlgBar   ;
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateFuncSelect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStatusTime(CCmdUI* pCmdUI);
	afx_msg LRESULT OnTaskComplete(WPARAM wp, LPARAM lp);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CDocument* GetActiveDocument();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnConsole();
};


